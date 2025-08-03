struct ListNode {
   int val;
   ListNode *next;

   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if ( !l1 && !l2 )
            return nullptr;
        else if ( l1 && !l2 )
            return copyList(l1);
        else if ( !l1 && l2 )
            return copyList(l2);

        // Ziperate through the two lists, creating a new node that
        // is the sum of the two current list nodes, and account for
        // the potential carry that may occur for the next addition.
        ListNode* sum = new ListNode();
        ListNode* curr = sum;
        bool carry = false;
        int valsum, next_sum_val, val1, val2;
        while ( l1 || l2 ) {
            val1 = l1 ? l1->val : 0;
            val2 = l2 ? l2->val : 0;
            valsum = val1 + val2 + carry;
            if ( valsum > 9 ) {
                next_sum_val = valsum % 10;
                carry = true;
            }
            else {
                next_sum_val = valsum;
                carry = false;
            }

            curr->val = next_sum_val;

            if ( l1 ) l1 = l1->next;
            if ( l2 ) l2 = l2->next;

            // if there will be a next...
            if ( l1 || l2 ) {
                curr->next = new ListNode();
                curr = curr->next;
            }

        }

        // If there is a carry left over at the end, create a final node,
        // that will be a 1.
        if ( carry )
            curr->next = new ListNode(1);

        return sum;
    }

    ListNode* copyList(ListNode * l) {
        ListNode* cpy_list = new ListNode(l->val);
        ListNode* curr = cpy_list;
        while ( (l = l->next) ) {
            ListNode* next_item = new ListNode(l->val);
            curr->next = next_item;
            curr = curr->next;
        }
        return cpy_list;
    }
};
