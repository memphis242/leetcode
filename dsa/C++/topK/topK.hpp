/**
 * @file topK.hpp
 * @brief Top-K element tracking data structure
 * @author Abdulla Almosalami (@memphis242)
 * @date Aug 24, 2025
 */
#pragma once

#include <concepts>
#include <initializer_list>
#include <optional>
#include <array>
#include <functional>
#include <utility>

template <typename Comp, typename T>
concept Comparator = requires(Comp comp, const T& a, const T& b) {
    { comp(a,b) } -> std::convertible_to<bool>;
};

/**
 * @brief A data structure for tracking the top K elements from a data stream.
 *
 * When the measure of "top K elements" is the typical "max K elements", you'll
 * want the comparator to be something that returns true if the first argument
 * is _greater_ than the second argument. If instead you want "min K elements",
 * you'll simply reverse that and provide a "less than" predicate.
 *
 * @tparam T The type of elements to store
 * @tparam K The maximum number of elements to track
 * @tparam Compare The comparator type for determining element ordering
 */
template <typename T, std::size_t K, Comparator<T> Compare = std::greater<T>>
class TopK {
public:
    // Either construct an empty container or initialize off of a container or
    // an initializer list and get the top K elements off the bat.
    TopK( Compare comp = Compare{} )
        : m_comp(comp) {}

    TopK( const Container& container, Compare comp = Compare{} )
        : m_comp(comp)
    {
        for ( auto v : container )
            push(v);
    }

    TopK( std::initializer_list<T> init_list, Compare comp = Compare{} );
    {
        for ( auto v : init_list )
            push(v);
    }

    ~TopK() = default;

    void push(const T& val)
    {
        if ( n_elements < m_data.size() )
        {
            m_data[n_elements - 1].emplace(val);
            n_elements++;
            sort();
        }
        else if ( m_comp(val, m_data[0]) )
        {
            m_data[0].emplace(val);
            n_elements++;
            sort();
        }
    }

    T pop(void) // Removes top element
    {
        T top_val = m_data[n_elements - 1];
        m_data[n_elements - 1].reset();
        sort();
        n_elements--;
        return top_val;
    }

    void clear(void)
    {
        for ( auto v : m_data )
            v.reset();
        n_elements = 0;
    }

    std::array<std::optional<T>, K> topK() const
    {
        return m_data;
    }

    std::optional<T> top() const
    {
        return m_data[n_elements - 1];
    }

    std::size_t size() const
    {
        return n_elements;
    }

    std::size_t capacity() const
    {
        return m_data.size();
    }

    bool empty() const
    {
        return n_elements == 0;
    }

private:
    Compare m_comp;
    std::array<std::optional<T>, K> m_data[];
    std::size_t n_elements = 0;

    void sort(void) // Sort m_data
    {
        // std::sort will likely do insertion sort on smaller container sizes and
        // merge/heap sort on larger container sizes. We don't that flexibility here
        // with a "TopK" data structure that in practice where K will at most be in
        // the 10s. So, I'll simply do the best sorting algorithm right here.

    #ifdef USE_BUBBLE_SORT

    #elif defined(USE_MERGE_SORT)

    #elif defined(USE_SELECTION_SORT)

    #elif defined(USE_NETWORK_SORT)

    #else
        // We'll try insertion sort
        for ( ptrdiff_t i = 1, j = 1; i < static_cast<ptrdiff_t>(m_data.size()); ++i, j = i )
        {
            while ( m_comp(m_data[j-1], m_data[j]) && j > 0 )
            {
                std::swap( m_data[j-1], m_data[j] );
                --j;
            }
        }
    #endif
    }
};
