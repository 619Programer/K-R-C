#include <stdio.h>

// 原书给的bitcount函数
/** 
    原书给的方法最差情况是遍历32次
    1000 0000 0000 0000 0000 0000 0000 0011
*/
int bitcount(unsigned x) {
    int b;
    for(b = 0; x != 0; x >>= 1) {
        if(x & 1)
            b ++;
    }
    return b;
}

/**
    优化后相同的案例只需要遍历3次
*/
int bitcount2(unsigned x) {
    int b;
    for(b = 0; x != 0; x &= x-1) {
        b ++;
    }
    return b;
}

int main(void) {
    printf("%d\n", bitcount2(589432));
    printf("%d\n", bitcount(589432));
    return 0;
}