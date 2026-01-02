#include <stdio.h>

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

unsigned invert(unsigned x, int p, int n) {
    // 先生成一个掩码 需要n个1 然后将这n个1向左移p的位置
    unsigned mask = ((1U << n) - 1) << (p + 1 - n);
    // 异或运算 1^1=0 0^1=1 完成取反操作
    return x ^ mask;
}

void testInvert(unsigned x, int p, int n, const char* desc) {
    unsigned result = invert(x, p, n);
    printf("invert测试: %s\n", desc);
    printf("  x      = 0x%08X = ", x);
    printBin(x);
    printf("  p=%d, n=%d\n", p, n);
    printf("  结果   = 0x%08X = ", result);
    printBin(result);
    printf("\n");
}

int main(void) {

    printf("=== invert 函数测试 ===\n\n");
    
    // 测试5: 基本取反
    testInvert(0xFF00FF00, 15, 8, 
               "取反第15-8位 (8位)");
    
    // 测试6: 边界条件 - n=1, 取反最低位
    testInvert(0xFFFFFFFF, 0, 1, 
               "取反最低位 (全1 → 全1最低位变0)");
    
    // 测试7: 边界条件 - p=31, 取反最高位
    testInvert(0x7FFFFFFF, 31, 1, 
               "取反最高位 (0x7FFF → 0xFFFF)");
    
    // 测试8: 取反中间4位
    testInvert(0xF0F0F0F0, 19, 4, 
               "取反第19-16位 (4位)");

    return 0;
}