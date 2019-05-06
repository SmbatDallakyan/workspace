#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "linkedList.h"

Node* createNode(int val) {
    Node* node = (Node*) malloc(sizeof (Node));
    if (!node) {
        exit(0);
    }
    node -> val = val;
    node -> next = NULL;
    return node;
}

Node* initialize(Node* list, int n) {
    if(n < 1) {
        return NULL;
    }
    list = createNode(1);
    Node* currentNode = list;
    for(int i = 2; i <= n; ++i) {
      currentNode -> next = createNode(i);
      currentNode = currentNode -> next;
    }
    return list;
}

void deleteList(Node* list) {
    while(list) {
        free(list);
        list = list -> next;
    }
}

void printList(Node* list) {
    if(!list) {
        printf("List is empty\n");
    }
    while(list) {
        printf("%p %s %d %s", (void *) list, ":" , list -> val, "-> ");
        list = list -> next;
    }
    printf("%s\n", "NULL");
}

Node* reverse(Node* list) {
    if(!list) {
        return list;
    }
    Node* currentNode = list -> next;
    list -> next = NULL;
    Node* prevNode = list;
    Node* nextNode;
    while(currentNode) {
        nextNode = currentNode -> next;
        currentNode -> next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    return prevNode;
}

Node* reverseN(Node* list, int n) {
    if(!list || n < 1) {
        return list;
    }
    Node *head = list;
    Node *currentNode = list->next;
    Node *prevNode = list;
    Node *nextNode = NULL;
    Node *lastNStart = list;
    Node *lastNEnd = list;
    lastNEnd->next = NULL;
    for (int i = 1; i < n && currentNode; ++i) {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    head = prevNode;
    while(currentNode) {
        lastNStart = currentNode;
        for (int i = 0; i < n && currentNode; ++i) {
            nextNode = currentNode->next;
            currentNode->next = prevNode;
            prevNode = currentNode;
            currentNode = nextNode;
        }
        lastNEnd->next = prevNode;
        lastNEnd = lastNStart;
        lastNEnd->next = NULL;
    }
    return head;
}

Node* shuffle(Node* list) {
    if(!list) {
        return list;
    }
    Node* oddTopNode = list;
    Node* currentNode = list -> next;
    Node* nextCurrentNode = NULL;
    while (currentNode && currentNode -> next) {
        nextCurrentNode = currentNode -> next -> next;
        currentNode -> next -> next = oddTopNode -> next;
        oddTopNode -> next = currentNode -> next;
        oddTopNode = oddTopNode -> next;
        currentNode -> next = nextCurrentNode;
        currentNode = nextCurrentNode;
    }
    return list;
}

Node* shuffleN(Node* list, int n) {
    if(n < 2 || !list) {
        return list;
    }
    Node* top[n];
    Node* end[n];
    Node* head = list;
    int i;

    for(i = 0; i < n && list; ++i) {
        top[i] = list;
        end[i] = list;
        list = list -> next;
    }
    if (!list) {
        return head;
    };
    while(list) {
        for(int i = 0; i < n && list; ++i) {
            end[i] -> next = list;
            end[i] = list;
            list = list -> next;
            end[i] -> next = NULL;
        }
    }
    list = top[0];
    for(int i = 0; i < n - 1; ++i) {
        end[i] -> next = top[i + 1];
    }
    end[n - 1] -> next = NULL;
    return list;
}

//--------------Old implementation of function shuffleN--------------------
//
// Node* shuffleN(Node* list, int n) {
//     Node* topNode = list;
//     Node* currentNode = list;
//     Node* nextCurrentNode;
//     Node* nextNode;
//     bool isNodeExists = true;
//     while (n > 1 && currentNode) {
//         while (currentNode && currentNode -> next && isNodeExists) {
//             for (int i = 1; i < n && isNodeExists; ++i) {
//                 currentNode = currentNode -> next;
//                 if (!currentNode) {
//                     isNodeExists = false;
//                 }
//             }
//             if(isNodeExists && currentNode -> next) {
//                 nextNode = currentNode -> next -> next;
//                 currentNode -> next -> next = topNode -> next;
//                 topNode -> next = currentNode -> next;
//                 topNode = topNode -> next;
//                 currentNode -> next = nextNode;
//             }
//         }
//         topNode = topNode -> next;
//         currentNode = topNode;
//         isNodeExists = true;
//         --n;
//     }
//     return list;
// }
