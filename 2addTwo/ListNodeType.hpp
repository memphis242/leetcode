#pragma once

struct ListNode {
   int val;
   ListNode *next;

   ListNode();
   ListNode(int);
   ListNode(int, ListNode*);
};
