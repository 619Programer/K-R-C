#include <stdio.h>
#include <limits.h>

#define SPLIT 4

void printBin(unsigned x) {
    int split = SPLIT;
    for(int i = 31; i >= 0; i --) {
        printf("%d", (x & (1 << i)) == 0 ? 0 : 1);
        split --;
        if(split == 0) {
            printf(" ");
            split = SPLIT;
        }
    }
    printf("\n");
}

unsigned rightrot(unsigned x, int n) {
    int bits = sizeof(unsigned) * CHAR_BIT;
    n %= bits;  // 处理n大于位数的情况
    // x << (bits - n) 把x右边的n个二进制位移到左边
    // x: 1000 1000 0001 0001 1111 1010 1010 1100 n: 4 bits: 32 bits-n: 28
    // x << 28 -> 1100 0000 0000 0000 0000 0000 0000 0000 准备做|运算将1100设置到x最左边的4位
    // x >> n 右移n位把位置空出来 右移后左侧补0
    return (x >> n) | (x << (bits - n));
}

void testRightrot(unsigned x, int n, const char* desc) {
    unsigned result = rightrot(x, n);
    printf("rightrot测试: %s\n", desc);
    printf("  x      = 0x%08X = ", x);
    printBin(x);
    printf("  n=%d\n", n);
    printf("  结果   = 0x%08X = ", result);
    printBin(result);
    printf("\n");
}

int main(void) {
printf("=== rightrot 函数测试 ===\n\n");
    
    // 测试9: 基本循环右移
    testRightrot(0x80000001, 1, 
                 "右移1位 (1000...0001 → 1100...0000)");
    
    // 测试10: 右移多位
    testRightrot(0x12345678, 8, 
                 "右移8位 (0x12345678 → 0x78123456)");
    
    // 测试11: 边界条件 - n等于总位数
    testRightrot(0xDEADBEEF, 32, 
                 "右移32位 (应该不变)");
    
    // 测试12: 边界条件 - n大于位数（取模）
    testRightrot(0xAABBCCDD, 36, 
                 "右移36位 (等价于右移4位)");
    
    // 测试13: 右移16位（半字交换）
    testRightrot(0x11223344, 16, 
                 "右移16位 (半字交换)");
    return 0;
}