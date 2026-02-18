#include <stdio.h>

#define swap(t, x, y) do{ \
    t temp = (x); \
    (x) = (y); \
    (y) = temp; \
    } while(0)

int main() {
    int a = 10;
    int b = 20;
    printf("a:%d, b:%d\n", a, b);
    swap(int, a, b);
    printf("a:%d, b:%d\n", a, b);
    return 0;
}