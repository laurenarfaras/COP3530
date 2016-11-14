#include<iostream>
using namespace std;

int main(){
    std::ios_base::sync_with_stdio(false);
    //number of elements in array
    int n = 0;
    cin >> n;
    int A[n];
    
    //read the elements and place in array
    for (int i = 0; i < n; i++){
        int number = 0;
        cin >> number;
        A[i] = number;
    }
    
    //insertion sort algorithm
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j;
        for (j = i - 1; j >= 0 && key < A[j]; j--){
            A[j+1] = A[j];
        }
        A[j+1] = key;
    }
    
    //print sorted array
    for (int b = 0; b < n; b++) {
        cout << A[b] << "\n";
    }
}
