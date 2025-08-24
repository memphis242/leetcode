/**
 * @file topK_priority_queue.hpp
 * @brief Top-K implementation using std::priority_queue
 * @author Abdulla Almosalami (@memphis242)
 * @date Aug 24, 2025
 */

#include <queue>
#include <vector>
#include <functional>
#include <optional>

template <typename T, typename Compare = std::greater<T>>
class TopKPriorityQueue {
public:
    TopKPriorityQueue(std::size_t k, Compare comp = Compare{}) 
        : m_k(k), m_comp(comp) {
        // For top-K with std::greater, we need a min-heap (opposite comparator)
        // so we can easily remove the smallest when we exceed K elements
    }

    void push(const T& val) {
        if (m_pq.size() < m_k) {
            m_pq.push(val);
        } else if (m_comp(val, m_pq.top())) {
            m_pq.pop();
            m_pq.push(val);
        }
    }

    std::optional<T> top() const {
        if (m_pq.empty()) return std::nullopt;
        
        // We need to find the actual top element since our internal queue
        // is a min-heap for efficiency
        auto temp_pq = m_pq;
        T result = temp_pq.top();
        temp_pq.pop();
        
        while (!temp_pq.empty()) {
            if (m_comp(temp_pq.top(), result)) {
                result = temp_pq.top();
            }
            temp_pq.pop();
        }
        return result;
    }

    std::vector<T> topK() const {
        std::vector<T> result;
        auto temp_pq = m_pq;
        
        while (!temp_pq.empty()) {
            result.push_back(temp_pq.top());
            temp_pq.pop();
        }
        
        std::sort(result.begin(), result.end(), m_comp);
        return result;
    }

    T pop() {
        auto result = top();
        if (result) {
            // Find and remove the top element
            std::vector<T> temp_vec;
            T to_remove = *result;
            bool removed = false;
            
            while (!m_pq.empty()) {
                T curr = m_pq.top();
                m_pq.pop();
                if (!removed && curr == to_remove) {
                    removed = true;
                } else {
                    temp_vec.push_back(curr);
                }
            }
            
            for (const auto& val : temp_vec) {
                m_pq.push(val);
            }
            
            return to_remove;
        }
        throw std::runtime_error("pop() called on empty container");
    }

    void clear() { 
        while (!m_pq.empty()) m_pq.pop(); 
    }
    
    std::size_t size() const { return m_pq.size(); }
    std::size_t capacity() const { return m_k; }
    bool empty() const { return m_pq.empty(); }

private:
    std::size_t m_k;
    Compare m_comp;
    // Use opposite comparator for internal min-heap to efficiently maintain top-K
    std::priority_queue<T, std::vector<T>, std::function<bool(const T&, const T&)>> m_pq{
        [this](const T& a, const T& b) { return m_comp(a, b); }
    };
};