#include "ListNodeType.hpp"

ListNode::ListNode() {
    val = 0;
    next = nullptr;
}

ListNode::ListNode(int x) {
    val = x;
    next = nullptr;
}

ListNode::ListNode(int x, struct ListNode* next) {
    val = x;
    next = next;
}
