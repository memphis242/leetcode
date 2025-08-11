#include <cassert>

struct ListNode {
   int val;
   ListNode *next;

   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if ( !l1 && !l2 )
            return new ListNode(0);
        else if ( l1 && !l2 )
           return copyList(l1);
        else if ( !l1 && l2 )
           return copyList(l2);

        ListNode* sumList = new ListNode();
        ListNode* curr = sumList;
        bool carry = false;
        int sum = 0;

        while ( l1 || l2 ) {
           // Determine next sum value (and save time by advancing list ptrs now)
            sum = carry;
            if ( l1 ) {
                sum += l1->val;
                l1 = l1->next;
            }
            if ( l2 ) {
                sum += l2->val;
                l2 = l2->next;
            }
            carry = (sum > 9);
            sum -= carry * 10;

            // Assign next sum value
            curr->val = sum;

            // See if there'll be a next round and create a new ListNode if so
            if ( carry || l1 || l2 ) {
                curr->next = new ListNode();
                curr = curr->next;
            }
        }

        // Account for carry on the way out
        if ( carry )
            curr->val = 1;

        return sumList;
    }

    ListNode* copyList(ListNode* l) {
      assert(l);

      ListNode* lc = new ListNode();
      ListNode* curr = lc;
      while ( l ) {
         curr->val = l->val;
         if ( l->next )
            curr->next = new ListNode();
         curr = curr->next;
         l = l->next;
      }

      return lc;
    }

    ListNode* reverseListInPlace(ListNode* l) {
      assert(l);

      if ( !l->next )
         return l;

      ListNode* curr = l;
      ListNode* prev = nullptr;
      ListNode* next;
      while ( curr ) {
         next = curr->next;
         curr->next = prev;
         prev = curr;
         curr = next;
      }

      return prev;
    }

    ListNode* reverseListCpy(ListNode* l) {
      assert(l);

      if ( !l->next )
         return new ListNode(l->val);

      ListNode* prev = nullptr;
      while ( l ) {
         ListNode* curr = new ListNode(l->val);
         curr->next = prev;
         prev = curr;
         l = l->next;
      }

      return prev;
    }
};
