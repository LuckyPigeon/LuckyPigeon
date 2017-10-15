# LuckyPigeon
想問為什麼dummy.next可以跑出答案來，但是cur.next跑出來的卻是[]

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0), *cur = &dummy;
        int extra = 0;
        
        while(l1 || l2 || extra){
            if(l1) extra += l1 -> val, l1 = l1 -> next;
            if(l2) extra += l2 -> val, l2 = l2 -> next;
            cur -> next = new ListNode(extra % 10);
            cur = cur -> next;
            extra /= 10;
            
        }
        return dummy.next;
    }
};

原本的例題在這裡 https://leetcode.com/problems/add-two-numbers/description/ 
