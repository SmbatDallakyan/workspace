#include "linkedList.h"

int main() {
    Node* reverseList;
    reverseList = initialize(reverseList, 10);
    reverseList = reverse(reverseList);
    printList(reverseList);
    deleteList(reverseList);

    Node* shuffleList;
    shuffleList = initialize(shuffleList, 10);
    shuffleList = shuffle(shuffleList);
    printList(shuffleList);
    deleteList(shuffleList);

    Node* shuffleListN;
    shuffleListN = initialize(shuffleListN, 10);
    shuffleListN = shuffleN(shuffleListN, 4);
    printList(shuffleListN);
    deleteList(shuffleListN);
}