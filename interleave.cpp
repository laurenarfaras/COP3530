
#include <iostream>
#include <list>

using namespace std;

void printList(list<int> L1){
    for (list<int>::iterator printer=L1.begin(); printer != L1.end(); ++printer)
            cout << *printer << " ";
}

void interleave(list<int> &L1, int numberOfElements, int stepValue) {
    list<int>::iterator it = L1.begin();
    int i = 0;
    for(advance(it, stepValue); i < numberOfElements; advance(it, stepValue)){
        int data;
        cin >> data;
        L1.insert(it, data);
        ++i;
    }
}

list<int> createList(int size) {
    list<int> numbers;
    for (int i = 0; i < size; i++) {
        int a;
        cin >> a;
        numbers.push_back(a);
    }
    return numbers;
}

int main() {
    ios_base::sync_with_stdio(false);
    int sizeL1;
    cin >> sizeL1;
    std::list<int> L1 = createList(sizeL1);
    int numberOfLists;
    cin >> numberOfLists;
    for (int i = 0; i < numberOfLists; i++) {
        int stepValue, numberOfElements;
        cin >> stepValue >> numberOfElements;
        interleave(L1, numberOfElements, stepValue);
    }
    printList(L1);
}
