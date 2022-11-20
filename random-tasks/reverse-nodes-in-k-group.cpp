#include<iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* getNext(ListNode* head, int k) {
    while(k && head) {
        head = head->next;
        --k;
    }

    return head;
}

ListNode* reverse(ListNode*& head) {
    ListNode* next = nullptr;
    ListNode* prev = nullptr;
    ListNode* it = head;
    ListNode* tmp = head;

    while(it) {
        next = it->next;
        it->next = prev;
        prev = it;
        it = next;
    }

    head = prev;
    return tmp;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* end = getNext(head, k - 1);

    if(end == nullptr)
        return head;

    ListNode* next = end->next;

    end->next = nullptr;
    
    ListNode* last = reverse(head);
    ListNode* res = reverseKGroup(next, k);

    last->next = res;
    return head;
}

int main() {
    
}