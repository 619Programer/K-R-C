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

// 将x中从第p位开始的n个二进制位设置为y中最右边n位的值
unsigned setbits(unsigned x, int p, int n, unsigned y) {
    // 拿到y最右边n位的二进制
    // 0U -> 0000 .... 0000
    // ~0U -> 1111 .... 1111
    // ~0U << n (取反的运算优先级大于左移 左移的右侧补0) -> 1111 ....00 (n个0)
    // ~(~0U << n) -> ~(1111 ....00) -> 0000 .... 11 (n个1)
    // ~(~0U << n) << p 掩码后面用来获取x从p位开始n个位的实际数据 -> 0000 .... (n个1) .... (p个0)
    unsigned mask = (~(~0U << n)) << p;
    // y & (~(~0U << n)) p最右边n位的值
    // (y & (~(~0U << n))) << p 整体左移p位
    unsigned yBits = (y & (~(~0U << n))) << p;
    return (x & ~mask) | yBits;
}

void testSetbits(unsigned x, int p, int n, unsigned y, const char* desc) {
    unsigned result = setbits(x, p, n, y);
    printf("setbits测试: %s\n", desc);
    printf("  x      = 0x%08X = ", x);
    printBin(x);
    printf("  y      = 0x%08X = ", y);
    printBin(y);
    printf("  p=%d, n=%d\n", p, n);
    printf("  结果   = 0x%08X = ", result);
    printBin(result);
    printf("\n");
}

int main(void) {
    printf("=== setbits 函数测试 ===\n\n");
    
    // 测试1: 基本功能 - 用y的低4位替换x的第7-4位
    testSetbits(0xFFFFFFFF, 7, 4, 0x0000000A, 
                "用0xA(1010)替换全1的第7-4位");
    
    // 测试2: 边界条件 - n=1, 替换最低位
    testSetbits(0xFFFFFFFE, 0, 1, 0x00000001, 
                "将最低位设为1 (偶数变奇数)");
    
    // 测试3: 边界条件 - p=31, 替换最高位
    testSetbits(0x7FFFFFFF, 31, 1, 0x00000001, 
                "设置最高位为1 (0x7FFF → 0xFFFF)");
    
    // 测试4: n超过y的实际位数（y的低位为0）
    testSetbits(0xFFFFFFFF, 15, 8, 0x0000000F, 
                "提取y的低8位(00001111)替换x的第15-8位");
}