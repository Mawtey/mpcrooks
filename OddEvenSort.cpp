#include <iostream>

using namespace std;

void odd_even_sort(int a[], int n){
    bool sorted = true;

    while (sorted){
        sorted = false;
// для четных
        for (int i = 0; i <= n - 2; i += 2){
            if (a[i] > a[i + 1]){
                swap(a[i], a[i+1]);

                sorted = true;
            }
        }
// для нечетных
        for (int i = 1; i <= n - 2; i += 2){
            if (a[i] > a[i+1]){
                swap(a[i], a[i+1]);

                sorted = true; 
            }
        }

    }
    
    for (int i = 0; i < n; i++) cout << a[i] << " ";

    return;
}

int main(){
    int a[] = {-19, 25, 0, 15, 12, 3, 6, -9};
    int n = sizeof(a) / sizeof(a[0]);

    odd_even_sort(a, n);

    return 0;
}

