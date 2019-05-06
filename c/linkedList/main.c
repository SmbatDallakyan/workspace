#include <stdio.h>
#include "linkedList.h"

int main() {
    Node* reverseList = NULL;
    reverseList = initialize(reverseList, 10);
    reverseList = reverse(reverseList);
    printList(reverseList);
    deleteList(reverseList);

    Node* shuffleList = NULL;
    shuffleList = initialize(shuffleList, 10);
    shuffleList = shuffle(shuffleList);
    printList(shuffleList);
    deleteList(shuffleList);

    Node* shuffleListN = NULL;
    shuffleListN = initialize(shuffleListN, 10);
    shuffleListN = shuffleN(shuffleListN, 4);
    printList(shuffleListN);
    deleteList(shuffleListN);

    Node* reverseListN = NULL;
    reverseListN = initialize(reverseListN, 14);
    reverseListN = reverseN(reverseListN, 2);
    printList(reverseListN);
    deleteList(reverseListN);
}
