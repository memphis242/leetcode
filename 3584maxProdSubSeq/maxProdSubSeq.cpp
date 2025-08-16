#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <functional>
#include <cstdlib>

using namespace std;

struct ValIdx {
    long long val;
    int idx;

    bool operator<(const ValIdx& other) const {
        return val < other.val;
    }

    bool operator>(const ValIdx& other) const {
        return val > other.val;
    }
};

// Heap that keeps track of the top k elements
template <typename Comp, typename T>
concept Comparator = requires(Comp comp, const T& a, const T& b) {
    { comp(a,b) } -> convertible_to<bool>;
};

template <typename T, Comparator<T> Compare = greater<T>>
class TopKHeap {
public:
    TopKHeap(size_t cap, Compare comp = Compare{})
        : m_capacity(cap), m_comp(comp) {}

    void push(const T& val) {
        if ( m_data.size() < m_capacity) {
            m_data.push_back(val);
            push_heap(m_data.begin(), m_data.end(), m_comp);
        }
        // Does the new value come after the top (min) value in heap ordering?
        // If so, swap them and heapify.
        else if ( m_comp(val, m_data.front()) ) {
            m_data.front() = val;
            make_heap(m_data.begin(), m_data.end(), m_comp);
        }
    }

    T pop(void) {
        T retVal = m_data[0];
        m_data.erase(m_data.begin());
        make_heap(m_data.begin(), m_data.end(), m_comp);
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

    size_t size() const {
        return m_data.size();
    }

    bool empty() const {
        return m_data.empty();
    }

    vector<T>& data() {
        return m_data;
    }

private:
    size_t m_capacity;
    Compare m_comp;
    vector<T> m_data;
};

class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        long long maxProd = numeric_limits<long long>::min();

        // Track the top m positive and top m negative numbers.
        TopKHeap<struct ValIdx, greater<struct ValIdx>> pos_heap(2);
        TopKHeap<struct ValIdx, less<struct ValIdx>>    neg_heap(2);
        for ( int i = 0; i < nums.size(); ++i ) {
            if ( nums[i] >= 0 && (pos_heap.size() <= 1 || (i - pos_heap.max().idx) >= m) )
                pos_heap.push( (struct ValIdx){ .val = nums[i], .idx = i } );
            if ( nums[i] < 0  && (neg_heap.size() <= 1 || (i - neg_heap.max().idx) >= m) )
                neg_heap.push( (struct ValIdx){ .val = nums[i], .idx = i } );
        }

        // See which of the two largest pairs produces the larger max
        vector<long long> pos_data;
        for ( int i = 0; !pos_heap.empty(); ++i )
            pos_data.push_back(pos_heap.pop().val);
        vector<long long> neg_data;
        for ( int i = 0; !neg_heap.empty(); ++i )
            neg_data.push_back(neg_heap.pop().val);

        if ( m == 1 )
            maxProd = max( pos_data[1] * pos_data[1],
                           neg_data[1] * neg_data[1] );
        else if ( m == 2 && pos_data.size() == 1 && pos_data.size() == 1 )
            maxProd = pos_data.front() * neg_data.front();
        else
            maxProd = max( pos_data[1] * pos_data[0],
                           neg_data[1] * neg_data[0] );

        return maxProd;
    }
};
