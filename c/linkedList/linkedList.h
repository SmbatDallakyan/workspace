typedef struct Node {
    int val;
    struct Node * next;
} Node;

Node* initialize(Node* list, int n);
void deleteList(Node* list);
void printList(Node* list);
Node* reverse(Node* list);
Node* shuffle(Node* list);
Node* shuffleN(Node* list, int n);