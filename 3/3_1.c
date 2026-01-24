#include <stdio.h>

int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n-1;
    while(low <= high) {
        mid = (low+high) / 2;
        if(x < v[mid])
            high = mid - 1;
        else if(x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int binsearch2(int x, int v[], int n) {
    int low, high, mid, index;
    low = 0;
    high = n-1;
    index = -1;
    mid = (low+high) / 2;
    while(low <= high && x != v[mid]) {
        if(x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low+high) / 2;
    }
    if(x == v[mid])
        index = mid;
    return index;
}

int main(void) {
    int v[] = {1,2,3,4,5,6,7,8,9,10};
    int x = 4;
    printf("%d\n", binsearch(x, v, 10));
    printf("%d\n", binsearch2(x, v, 10));
    return 0;
}