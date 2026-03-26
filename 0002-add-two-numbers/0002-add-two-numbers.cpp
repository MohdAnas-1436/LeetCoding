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
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Dummy node to simplify the handling of the head of the result list
        ListNode dummyHead(0);
        ListNode* current = &dummyHead;
        int carry = 0;
        
        // Loop continues as long as there are nodes to process or a carry left over
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;
            
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }
            
            // The new carry is the tens digit (e.g., 18 / 10 = 1)
            carry = sum / 10;
            
            // The new node's value is the ones digit (e.g., 18 % 10 = 8)
            current->next = new ListNode(sum % 10);
            current = current->next;
        }
        
        return dummyHead.next;
    }
};