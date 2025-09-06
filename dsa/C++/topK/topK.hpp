/**
 * @file topK.hpp
 * @brief Top-K element tracking data structure
 * @author Abdulla Almosalami (@memphis242)
 * @date Aug 24, 2025
 */
#pragma once

#include <concepts>
#include <ranges>
#include <optional>
#include <array>
#include <functional>
#include <utility>
#include <cassert>

// Enforce that the comparator is a predicate that compares two objects of type T.
template <typename Comp, typename T>
concept ComparatorFor = std::predicate<Comp, T, T>;

// Enforce that a range passed in to initialize the TopK structure with is
// 1) a range, and 
// 2) a range over the type T
template <typename R, typename T>
concept RangeOver = std::ranges::range<R>  // is a range object
                    && std::same_as<std::ranges::range_value_t<R>, T>;  // is a range over type T

/**
 * @brief A data structure for tracking the top K elements of data pass through.
 *
 * How this Works:
 * --------------
 * A sorted data structure is maintained where the first index has the "bottom"
 * element and the last index has the "top" element. Once the K elements of this
 * structure are filled, any new value that comes in is compared with the bottom
 * element - if the new value is measured "greater" by the comparator of this TopK
 * object, the new value is swapped in for the bottom index, and then the structure
 * is re-sorted. This way, the structure effectively maintains the top K elements
 * that have been passed through it. See the below visual example:
 *
 * Top 2 Structure /w std::greater:
 * -------------------------------
 * TopK: [5, 9] (pre-populated)
 * New Value: 3 → Top2 → no change          (5 is > 3, and the array is sorted, so we
 *                                           can conclude that 3 is also less than every
 *                                           other element in the TopK structure)
 *
 * New Value: 6 → Top2 → [6, 9] → [6, 9]    (6 is > 5, so it is swapped in for 5; the
 *                                           sequbsequent sort doesn't change anything)
 *
 * New Value: 10 → Top2 → [10, 9] → [9, 10] (10 is > 6, so it is swapped in for 6; the
 *                                           subsequent sort places 10 after the 9)
 * 
 * Notice that at each step, the structure has maintained the Top 2 elements
 * that have been passed through it.
 *
 * @note When the measure of "top K elements" is the typical "max K elements", you'll
 * want the comparator to be something that returns true if the first argument
 * is _greater_ than the second argument. If instead you want "min K elements",
 * you'll simply reverse that and provide a "less than" predicate.
 *
 * @tparam Underlying value types T
 * @tparam K The maximum number of elements to track
 * @tparam Compare The comparator type for determining element ordering
 */
template <typename T, std::size_t K, ComparatorFor<T> Compare = std::greater<>>
class TopK {
public:

    /* ---------------------------- CONSTRUCTORS ---------------------------- */

    // TODO: [[nodiscard]], explicit, and = delete?
    /**
     * @brief Construct with no initial data
     * @param comp The > predicate function
     */
    TopK( Compare comp = Compare{} ) : m_comp(comp) {}

    /**
     * @brief Construct with a range, passing each element of the container
     *        through the data structure and obtaining the top K elements off
     *        the bat.
     * @tparam data The data to initially pass through the TopK structure
     *              (a RangeOver<T> object, such as a vector, list, ...)
     * @param comp The > predicate function
     */
    TopK( const RangeOver<T> auto& data, Compare comp = Compare{} )
        : m_comp(comp)
    {
        for ( const auto& v : data )
            pass(v);
    }

    /**
     * @brief Default destructor only
     */
    ~TopK() = default;

    // TODO: Copy and move constructors

    /* ------------------------------ METHODS ------------------------------- */

    /**
     * @brief Pass a value through the TopK data structure.
     * @note The term "pass" is used instead of "push" because I prefer to imagine
     *       this topK data structure as a small vector "passing over" another,
     *       as if convolving with it, keeping track of the top K elements.
     */
    void pass(const T& val)
    {
        assert(n_elements >= 0);
        assert(n_elements <= capacity());
        assert( (n_elements > 0 && m_data[0].has_value())
                || (n_elements == 0 && !m_data[0].has_value()) );

        if ( n_elements < K )
        {
            m_data[n_elements++] = val;
            sort();
        }
        else if ( m_comp(val, *m_data[0]) ) // Note: m_data[0] always contains "bottom" element
        {
            m_data[0] = val; // Swap-in the new value
            sort();
        }

        assert(n_elements >= 0);
        assert(n_elements <= capacity());
    }

    /**
     * @brief Pass a container through the TopK data structure.
     */
    void pass(const RangeOver<T> auto& data)
    {
        for ( const auto& val : data )
            pass(val);
    }

    /**
     * @brief Remove and return the top element
     * @note std::optional instead of std::expected because I don't think making
     *       and error type is necessary here. The lack of an object is self
     *       explanatory and I wouldn't say is an error.
     */
    std::optional<T> pop(void)
    {
        assert(n_elements >= 0);
        assert(n_elements <= capacity());
        assert( (n_elements > 0 && m_data[n_elements - 1].has_value())
                || (n_elements == 0 && !m_data[0].has_value()) );

        if ( n_elements == 0 )
            return std::nullopt;

        std::optional<T> top_val = m_data[n_elements - 1];
        m_data[n_elements - 1].reset();
        n_elements--;

        assert(n_elements >= 0);
        assert(n_elements <= capacity());
        assert( (n_elements > 0 && m_data[n_elements - 1].has_value())
                || (n_elements == 0 && !m_data[0].has_value()) );

        return top_val;
    }

    /**
     * @brief Clear all the elements (assign std::nullopt), effectively resetting the data structure
     */
    void clear(void)
    {
        for ( auto& v : m_data )
            v.reset();
        n_elements = 0;
    }

    /**
     * @brief Return the underlying top K elements found thus far
     */
    std::array<std::optional<T>, K> topK() const
    {
        return m_data;
    }

    /**
     * @brief Return, by value, the top element, /wo mutating the object
     */
    std::optional<T> top() const
    {
        assert(n_elements >= 0);
        assert(n_elements <= capacity());
        assert( (n_elements > 0 && m_data[n_elements - 1].has_value())
                || (n_elements == 0 && !m_data[0].has_value()) );

        if ( n_elements == 0 )
            return std::nullopt;

        assert(n_elements > 0);
        assert(n_elements <= capacity());

        return m_data[n_elements - 1];
    }

    /**
     * @brief Return the number of elements within the data structure
     */
    std::size_t size() const
    {
        assert(n_elements >= 0);
        assert(n_elements <= capacity());

        return n_elements;
    }

    /**
     * @brief Return K, the capacity of the data structure
     */
    std::size_t capacity() const
    {
        return m_data.size();
    }

    /**
     * @brief Return whether or not the data structure is empty
     */
    bool is_empty() const noexcept
    {
        return n_elements == 0;
    }

private:
    const Compare m_comp;
    std::array<std::optional<T>, K> m_data;
    std::size_t n_elements = 0;

    /**
     * @brief Every pass of value through ends with a sorting of the top K thus far
     */
    void sort(void) // Sort m_data
    {
        assert(n_elements >= 0);
        assert(n_elements <= capacity());
#ifndef NDEBUG
        for ( size_t i = 0; i < n_elements; ++i )
        {
            assert(m_data[i].has_value());
        }
#endif

        // std::sort will likely do insertion sort on smaller container sizes and
        // merge/heap sort on larger container sizes. We don't need that flexibility
        // here with a "TopK" data structure that in practice will at most have 10s
        // of elements. So, I'll simply do the best sorting algorithm right here.

        // Insertion Sort
        for ( std::ptrdiff_t i = 1; i < static_cast<std::ptrdiff_t>(n_elements); ++i )
        {
            auto key = m_data[i];
            j = i - 1;
            while ( j >= 0 && m_comp(*m_data[j], key) )
            {
                m_data[j+1] = m_data[j];
                --j;
            }
            m_data[j+1] = key;
        }
    }
};
