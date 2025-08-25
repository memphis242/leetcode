/**
 * @file topK.hpp
 * @brief Top-K element tracking data structure
 * @author Abdulla Almosalami (@memphis242)
 * @date Aug 24, 2025
 */
#pragma once

#include <concepts>
#include <ranges>
#include <initializer_list>
#include <optional>
#include <array>
#include <functional>
#include <utility>
#include <cassert>

template <typename Comp, typename T>
concept ComparatorFor = std::predicate<Comp, T, T>;

template <typename R, typename T>
concept RangeOver = std::ranges::range<R>
                    && std::same_as<std::ranges::range_value_t<R>, T>;

/**
 * @brief A data structure for tracking the top K elements of data pass through.
 *
 * When the measure of "top K elements" is the typical "max K elements", you'll
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

    /**
     * @brief Construct with no initial data
     * @param comp The > predicate function
     */
    TopK( Compare comp = Compare{} ) : m_comp(comp) {}

    /**
     * @brief Construct with a range, passing each element of the container
     *        through the data structure and obtaining the top K elements off
     *        the bat.
     * @param container The container object (e.g., vector, list, ...)
     * @param comp The > predicate function
     */
    TopK( const RangeOver<T> auto& data, Compare comp = Compare{} )
        : m_comp(comp)
    {
        for ( const auto& v : data )
            pass(v);
    }

    /* ---------------------------- CONSTRUCTORS ---------------------------- */

    /**
     * @brief Default destructor only
     */
    ~TopK() = default;

    /* ------------------------------ METHODS ------------------------------- */

    /**
     * @brief Pass a value through the TopK data structure.
     */
    void pass(const T& val)
    {
        assert(n_elements >= 0);
        assert(n_elements <= m_data.size());
        assert( (n_elements > 0 && m_data[0].has_value()) || n_elements == 0 );

        if ( n_elements < K )
        {
            m_data[n_elements] = val;
            n_elements++;
            sort();
        }
        else if ( m_comp(val, *m_data[0]) ) // Note: m_data[0] always contains "bottom" element
        {
            m_data[0] = val;
            sort();
        }

        assert(n_elements >= 0);
        assert(n_elements <= m_data.size());
    }

    /**
     * @brief Pass a container through the TopK data structure.
     * @note The term "pass" is used instead of "push" because I prefer to imagine
     *       this topK data structure as a small vector "passing over" another,
     *       as if convolving with it.
     */
    void pass(const RangeOver<T> auto& data)
    {
        for ( const auto& val : data )
            pass(val);
    }

    /**
     * @brief Remove and return the top element
     */
    std::optional<T> pop(void)
    {
        assert(n_elements >= 0);
        assert(n_elements <= m_data.size());

        if ( n_elements == 0 )
            return std::nullopt;

        std::optional<T> top_val = m_data[n_elements - 1];
        m_data[n_elements - 1].reset();
        n_elements--;

        assert(n_elements >= 0);
        assert(n_elements <= m_data.size());

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
        if ( n_elements == 0 )
            return std::nullopt;

        assert(n_elements > 0);
        assert(n_elements <= m_data.size());

        return m_data[n_elements - 1];
    }

    /**
     * @brief Return the number of elements within the data structure
     */
    std::size_t size() const
    {
        assert(n_elements >= 0);
        assert(n_elements <= m_data.size());

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
    bool empty() const
    {
        return n_elements == 0;
    }

private:
    Compare m_comp;
    std::array<std::optional<T>, K> m_data;
    std::size_t n_elements = 0;

    /**
     * @brief Every pass of value through ends with a sorting of the top K thus far
     */
    void sort(void) // Sort m_data
    {
        assert(n_elements >= 0);
        assert(n_elements <= m_data.size());
#       ifndef NDEBUG
        for ( size_t i = 0; i < n_elements; ++i )
        {
            assert(m_data[i].has_value());
        }
#       endif

        // std::sort will likely do insertion sort on smaller container sizes and
        // merge/heap sort on larger container sizes. We don't that flexibility here
        // with a "TopK" data structure that in practice where K will at most be in
        // the 10s. So, I'll simply do the best sorting algorithm right here.

#       ifdef USE_BUBBLE_SORT

#       elif defined(USE_MERGE_SORT)

#       elif defined(USE_SELECTION_SORT)

#       elif defined(USE_NETWORK_SORT)

#       else
        // Insertion Sort
        for ( ptrdiff_t i = 1, j = 1; i < n_elements; ++i, j = i )
        {
            while ( j > 0 && m_comp(*m_data[j-1], *m_data[j]) )
            {
                std::swap( m_data[j-1], m_data[j] );
                --j;
            }
        }
    #endif
    }
};
