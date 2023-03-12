#include <fstream>
#include <vector>
#include <iostream>
 
using namespace std;
 
void quick(int arr[], int left, int right, int k) {
    int j = right;
    int i = left;
    int mid = (left + right) / 2;
    int pivot = arr[mid];
 
    while (i <= j) {
        while (arr[i] < pivot){
            i++;
        }
        while (arr[j] > pivot){
            j--;
        }
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j && k <= j) {
        quick(arr, left, j, k);
    }
    if (i < right && k >= i) {
        quick(arr, i, right, k);
    }
}
 
int main() {
 
    ifstream cin("kth.in");
    ofstream cout("kth.out");
    int num, k, A, B, C;
    cin >> num >> k;
    int arr[num];
    cin >> A >> B >> C >> arr[0] >> arr[1];
    for(int i = 2; i < num; i++){
        arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
    }
    quick(arr, 0, num-1, k-1);
    cout << arr[k-1];
    return 0;
}
