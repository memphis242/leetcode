#include <vector>
#include <cmath>
#include <limits>
#include <queue>
#include <functional>
#include <cstdlib>

using namespace std;

template <size_t M>
struct ValIdx {
    long long val;
    int idx;

    // FIXME: This won't work for >... Because the abs(idx - other.idx) condition
    //        will cause false positives on >.
    bool operator<(const ValIdx<M>& other) const {
        return (val < other.val) && (abs(idx - other.idx) >= M);
    }
};

// Heap that keeps track of the top k elements
template <typename Comp, typename T>
concept CompareFor = requires(Comp comp, const T& a, const T& b) {
    { comp(a,b) } -> std::convertible_to<bool>;
};

template <typename T, CompareFor<T> Compare = std::greater<T>>
class TopKHeap {
public:
    TopKHeap(size_t cap, Compare comp = Compare{})
        : m_capacity(cap), m_comp(comp) {}

    // TODO: Redo this using <algorithm>'s std::push_heap and make_heap
    //       operations on a std::vector instead of a priority_queue to
    //       support faster top swaps.
    void push(const T& val) {
        if ( m_heap.size() < m_capacity)
            m_heap.push(val);
        else if ( m_comp(m_heap.top(), val) ) {
            (void)m_heap.pop();
            m_heap.push(val);
        }
    }

    T pop(void) {
        T retVal = m_heap.top();
        m_heap.pop();
        return retVal;
    }

    const T& top() const {
        return m_heap.top();
    }

    size_t size() const {
        return m_heap.size();
    }

    bool empty() const {
        return m_heap.empty();
    }

    std::vector<T>& data() {
        // TODO: data() method on TopKHeap
    }

private:
    size_t m_capacity;
    Compare m_comp;
    priority_queue<T, std::vector<T>, Compare> m_heap; // min heap
};

class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        long long max = numeric_limits<long long>::min();

        // Track the top 2 positive and top 2 negative numbers.
        TopKHeap<struct ValIdx<m>, std::less<struct ValIdx<m>>>    pos_heap(2);
        TopKHeap<struct ValIdx<m>, std::greater<struct ValIdx<m>>> neg_heap(2);
        for ( int i = 0; i < nums.size(); ++i ) {
            pos_heap.push( (struct ValIdx<m>){ nums[i], i } );
            neg_heap.push( (struct ValIdx<m>){ nums[i], i } );
        }

        // See whether the product of the two max positives or the two max negatives
        // produce the greater max.
        std::vector<struct ValIdx<m>> pos_data = pos_heap.data();
        std::vector<struct ValIdx<m>> neg_data = neg_heap.data();
        max = pos_data[0] * pos_data[1];
        max = (neg_data[0] * neg_data[1]) > max ? (neg_data[0] * neg_data[1]) : max;

        return max;
    }
};
