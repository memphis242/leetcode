#include <iostream>
#include <vector>

//#include "addTwoNumbers.cpp"
#include "addtwo.cpp"

void printList(ListNode* node) {
   while (node) {
      std::cout << node->val;
      if (node->next) std::cout << " -> ";
      node = node->next;
   }
   std::cout << std::endl;
}

ListNode* createList(const std::vector<int>& vals) {
   ListNode dummy;
   ListNode* tail = &dummy;
   for (int v : vals) {
      tail->next = new ListNode(v);
      tail = tail->next;
   }
   return dummy.next;
}

void test_addTwoNumbers(const std::vector<int>& l1_vals, const std::vector<int>& l2_vals, const std::vector<int>& expected) {
   Solution sol;
   ListNode* l1 = createList(l1_vals);
   ListNode* l2 = createList(l2_vals);
   ListNode* result = sol.addTwoNumbers(l1, l2);

   std::cout << "Input: ";
   printList(l1);
   std::cout << " + ";
   printList(l2);
   std::cout << "Output: ";
   printList(result);
   std::cout << "Expected: ";
   printList(createList(expected));
   std::cout << std::endl;
}

int main() {
   // Test case 1: 342 + 465 = 807
   test_addTwoNumbers({2,4,3}, {5,6,4}, {7,0,8});

   // Test case 2: 0 + 0 = 0
   test_addTwoNumbers({0}, {0}, {0});

   // Test case 3: 999 + 1 = 1000
   test_addTwoNumbers({9,9,9}, {1}, {0,0,0,1});

   // Test case 4: 123 + 456 = 579
   test_addTwoNumbers({3,2,1}, {6,5,4}, {9,7,5});

   // Test case 5: Empty lists
   test_addTwoNumbers({}, {}, {});

   // Test case 6: Different lengths
   test_addTwoNumbers({1,8}, {0}, {1,8});
}
