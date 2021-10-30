/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        if(head==NULL)return head;
        Node*temp=head;
        while(temp){
            if(temp->child!=NULL){
                Node*newChild=flatten(temp->child);
                newChild->prev=temp;
                Node*temp2=temp->next;
                temp->next=newChild;
                temp->child=NULL;
                while(newChild->next){
                    newChild=newChild->next;
                }
                newChild->next=temp2;
                if(temp2)
                temp2->prev=newChild;
                temp=temp2;
            }
            else temp=temp->next;
        }
        return head;
    }
};