#include <algorithm>

// Heap that keeps track of the top k elements
template <typename Comp, typename T>
concept Comparator = requires(Comp comp, const T& a, const T& b) {
    { comp(a,b) } -> convertible_to<bool>;
};

template <typename T, Comparator<T> Compare = std::greater<T>>
class TopKHeap {
public:
    TopKHeap(std::ptrdiff_t cap, Compare comp = Compare{})
        : m_capacity(cap), m_comp(comp) {}

    void push(const T& val) {
        if ( m_data.size() < m_capacity) {
            m_data.push_back(val);
            std::push_heap(m_data.begin(), m_data.end(), m_comp);
        }
        // Does the new value come after the top (min) value in heap ordering?
        // If so, swap them and heapify.
        else if ( m_comp(val, m_data.front()) ) {
            m_data.front() = val;
            std::make_heap(m_data.begin(), m_data.end(), m_comp);
        }
    }

    T pop(void) {
        T retVal = m_data[0];
        m_data.erase(m_data.begin());
        std::make_heap(m_data.begin(), m_data.end(), m_comp);
        return retVal;
    }

    const T max() const {
        // TODO: Throw exception if vector is empty
        if ( m_data.size() == 1 )
            return m_data[0];

        T maxVal = m_data[1];
        for ( ptrdiff_t i = 2; i < m_data.size(); ++i ) {
            maxVal = m_comp( maxVal, m_data[i] ) ? maxVal : m_data[i];
        }
        return maxVal;
    }

    const T& top() const {
        return m_data.front();
    }

    std::ptrdiff_t size() const {
        return static_cast<std::ptrdiff_t>( m_data.size() );
    }

    bool empty() const {
        return m_data.empty();
    }

    std::vector<T>& data() {
        return m_data;
    }

private:
    std::ptrdiff_t m_capacity;
    Compare m_comp;
    std::vector<T> m_data;
};
