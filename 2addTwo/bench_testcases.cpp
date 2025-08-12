#include <vector>

#include "ListNodeType.hpp"

// Basic test cases
static ListNode l1_6 = { 0, nullptr };
static ListNode l1_5 = { 3, &l1_6     };
static ListNode l1_4 = { 1, &l1_5     };
static ListNode l1_3 = { 0, &l1_4     };
static ListNode l1_2 = { 9, &l1_2     };
static ListNode l1_1 = { 5, &l1_1     };
static ListNode l1 = l1_1;

// Simple numbers: 342 (243 reversed)
static ListNode l2_3 = { 2, nullptr };
static ListNode l2_2 = { 4, &l2_3 };
static ListNode l2_1 = { 3, &l2_2 };
static ListNode l2 = l2_1;

// Longer number: 9081726354 (4536271809 reversed)
static ListNode l3_10 = { 9, nullptr };
static ListNode l3_9 = { 0, &l3_10 };
static ListNode l3_8 = { 8, &l3_9 };
static ListNode l3_7 = { 1, &l3_8 };
static ListNode l3_6 = { 7, &l3_7 };
static ListNode l3_5 = { 2, &l3_6 };
static ListNode l3_4 = { 6, &l3_5 };
static ListNode l3_3 = { 3, &l3_4 };
static ListNode l3_2 = { 5, &l3_3 };
static ListNode l3_1 = { 4, &l3_2 };
static ListNode l3 = l3_1;

// Single digit: 7
static ListNode l4_1 = { 7, nullptr };
static ListNode l4 = l4_1;

// Zero
static ListNode l5_1 = { 0, nullptr };
static ListNode l5 = l5_1;

// Number with 9s for carry: 999
static ListNode l6_3 = { 9, nullptr };
static ListNode l6_2 = { 9, &l6_3 };
static ListNode l6_1 = { 9, &l6_2 };
static ListNode l6 = l6_1;

// Number that needs many carries: 9999999
static ListNode l7_7 = { 9, nullptr };
static ListNode l7_6 = { 9, &l7_7 };
static ListNode l7_5 = { 9, &l7_6 };
static ListNode l7_4 = { 9, &l7_5 };
static ListNode l7_3 = { 9, &l7_4 };
static ListNode l7_2 = { 9, &l7_3 };
static ListNode l7_1 = { 9, &l7_2 };
static ListNode l7 = l7_1;

// Medium size: 12345 (54321 reversed)
static ListNode l8_5 = { 1, nullptr };
static ListNode l8_4 = { 2, &l8_5 };
static ListNode l8_3 = { 3, &l8_4 };
static ListNode l8_2 = { 4, &l8_3 };
static ListNode l8_1 = { 5, &l8_2 };
static ListNode l8 = l8_1;

// Two digits: 42
static ListNode l9_2 = { 4, nullptr };
static ListNode l9_1 = { 2, &l9_2 };
static ListNode l9 = l9_1;

// Alternating digits: 1010101
static ListNode l10_7 = { 1, nullptr };
static ListNode l10_6 = { 0, &l10_7 };
static ListNode l10_5 = { 1, &l10_6 };
static ListNode l10_4 = { 0, &l10_5 };
static ListNode l10_3 = { 1, &l10_4 };
static ListNode l10_2 = { 0, &l10_3 };
static ListNode l10_1 = { 1, &l10_2 };
static ListNode l10 = l10_1;

// All same digits: 5555
static ListNode l11_4 = { 5, nullptr };
static ListNode l11_3 = { 5, &l11_4 };
static ListNode l11_2 = { 5, &l11_3 };
static ListNode l11_1 = { 5, &l11_2 };
static ListNode l11 = l11_1;

// Large number: 123456789
static ListNode l12_9 = { 1, nullptr };
static ListNode l12_8 = { 2, &l12_9 };
static ListNode l12_7 = { 3, &l12_8 };
static ListNode l12_6 = { 4, &l12_7 };
static ListNode l12_5 = { 5, &l12_6 };
static ListNode l12_4 = { 6, &l12_5 };
static ListNode l12_3 = { 7, &l12_4 };
static ListNode l12_2 = { 8, &l12_3 };
static ListNode l12_1 = { 9, &l12_2 };
static ListNode l12 = l12_1;

// Leading zeros: 00123
static ListNode l13_5 = { 0, nullptr };
static ListNode l13_4 = { 0, &l13_5 };
static ListNode l13_3 = { 1, &l13_4 };
static ListNode l13_2 = { 2, &l13_3 };
static ListNode l13_1 = { 3, &l13_2 };
static ListNode l13 = l13_1;

// Descending: 9876543210
static ListNode l14_10 = { 9, nullptr };
static ListNode l14_9 = { 8, &l14_10 };
static ListNode l14_8 = { 7, &l14_9 };
static ListNode l14_7 = { 6, &l14_8 };
static ListNode l14_6 = { 5, &l14_7 };
static ListNode l14_5 = { 4, &l14_6 };
static ListNode l14_4 = { 3, &l14_5 };
static ListNode l14_3 = { 2, &l14_4 };
static ListNode l14_2 = { 1, &l14_3 };
static ListNode l14_1 = { 0, &l14_2 };
static ListNode l14 = l14_1;

// Palindrome: 12321
static ListNode l15_5 = { 1, nullptr };
static ListNode l15_4 = { 2, &l15_5 };
static ListNode l15_3 = { 3, &l15_4 };
static ListNode l15_2 = { 2, &l15_3 };
static ListNode l15_1 = { 1, &l15_2 };
static ListNode l15 = l15_1;

// Medium with zeros: 10203
static ListNode l16_5 = { 1, nullptr };
static ListNode l16_4 = { 0, &l16_5 };
static ListNode l16_3 = { 2, &l16_4 };
static ListNode l16_2 = { 0, &l16_3 };
static ListNode l16_1 = { 3, &l16_2 };
static ListNode l16 = l16_1;

// Binary-like: 10101010
static ListNode l17_8 = { 1, nullptr };
static ListNode l17_7 = { 0, &l17_8 };
static ListNode l17_6 = { 1, &l17_7 };
static ListNode l17_5 = { 0, &l17_6 };
static ListNode l17_4 = { 1, &l17_5 };
static ListNode l17_3 = { 0, &l17_4 };
static ListNode l17_2 = { 1, &l17_3 };
static ListNode l17_1 = { 0, &l17_2 };
static ListNode l17 = l17_1;

// Prime digits: 2357
static ListNode l18_4 = { 2, nullptr };
static ListNode l18_3 = { 3, &l18_4 };
static ListNode l18_2 = { 5, &l18_3 };
static ListNode l18_1 = { 7, &l18_2 };
static ListNode l18 = l18_1;

// Long with repeating pattern: 121212121
static ListNode l19_9 = { 1, nullptr };
static ListNode l19_8 = { 2, &l19_9 };
static ListNode l19_7 = { 1, &l19_8 };
static ListNode l19_6 = { 2, &l19_7 };
static ListNode l19_5 = { 1, &l19_6 };
static ListNode l19_4 = { 2, &l19_5 };
static ListNode l19_3 = { 1, &l19_4 };
static ListNode l19_2 = { 2, &l19_3 };
static ListNode l19_1 = { 1, &l19_2 };
static ListNode l19 = l19_1;

// Very long number: 98765432109876543210
static ListNode l20_20 = { 9, nullptr };
static ListNode l20_19 = { 8, &l20_20 };
static ListNode l20_18 = { 7, &l20_19 };
static ListNode l20_17 = { 6, &l20_18 };
static ListNode l20_16 = { 5, &l20_17 };
static ListNode l20_15 = { 4, &l20_16 };
static ListNode l20_14 = { 3, &l20_15 };
static ListNode l20_13 = { 2, &l20_14 };
static ListNode l20_12 = { 1, &l20_13 };
static ListNode l20_11 = { 0, &l20_12 };
static ListNode l20_10 = { 9, &l20_11 };
static ListNode l20_9 = { 8, &l20_10 };
static ListNode l20_8 = { 7, &l20_9 };
static ListNode l20_7 = { 6, &l20_8 };
static ListNode l20_6 = { 5, &l20_7 };
static ListNode l20_5 = { 4, &l20_6 };
static ListNode l20_4 = { 3, &l20_5 };
static ListNode l20_3 = { 2, &l20_4 };
static ListNode l20_2 = { 1, &l20_3 };
static ListNode l20_1 = { 0, &l20_2 };
static ListNode l20 = l20_1;

std::vector<struct ListNode*> test_cases = { 
    &l1, &l2, &l3, &l4, &l5, &l6, &l7, &l8, &l9, &l10, 
    &l11, &l12, &l13, &l14, &l15, &l16, &l17, &l18, &l19, &l20 
};
