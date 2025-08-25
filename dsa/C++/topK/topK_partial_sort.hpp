/**
 * @file topK_partial_sort.hpp
 * @brief Top-K implementation using std::partial_sort
 * @author Abdulla Almosalami (@memphis242)
 * @date Aug 24, 2025
 */

#include <vector>
#include <algorithm>
#include <functional>
#include <optional>

template <typename T, typename Compare = std::greater<T>>
class TopKPartialSort {
public:
    TopKPartialSort(std::size_t k, Compare comp = Compare{}) 
        : m_k(k), m_comp(comp) {}

    void push(const T& val) {
        m_data.push_back(val);
    }

    std::optional<T> top() const {
        if (m_data.empty()) return std::nullopt;
        
        auto temp_data = m_data;
        auto end_iter = temp_data.size() < m_k ? temp_data.end() : temp_data.begin() + m_k;
        std::partial_sort(temp_data.begin(), end_iter, temp_data.end(), m_comp);
        return temp_data[0];
    }

    std::vector<T> topK() const {
        if (m_data.empty()) return {};
        
        auto temp_data = m_data;
        auto end_iter = temp_data.size() < m_k ? temp_data.end() : temp_data.begin() + m_k;
        std::partial_sort(temp_data.begin(), end_iter, temp_data.end(), m_comp);
        
        std::size_t result_size = std::min(m_k, temp_data.size());
        return std::vector<T>(temp_data.begin(), temp_data.begin() + result_size);
    }

    T pop() {
        auto result = top();
        if (result) {
            auto temp_data = m_data;
            std::partial_sort(temp_data.begin(), temp_data.begin() + 1, temp_data.end(), m_comp);
            auto to_remove = temp_data[0];
            m_data.erase(std::find(m_data.begin(), m_data.end(), to_remove));
            return to_remove;
        }
        throw std::runtime_error("pop() called on empty container");
    }

    void clear() { m_data.clear(); }
    std::size_t size() const { return m_data.size(); }
    std::size_t capacity() const { return m_k; }
    bool empty() const { return m_data.empty(); }

private:
    std::size_t m_k;
    Compare m_comp;
    std::vector<T> m_data;
};