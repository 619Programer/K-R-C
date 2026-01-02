#include <stdio.h>
#include <limits.h>

/** 定义宏计算不同类型的位数 **/
#define CHARBITS (sizeof(char) * CHAR_BIT)   // 64位 8bit   32位 8bit
#define SHORTBITS (sizeof(short) * CHAR_BIT) // 64位 16bit  32位 16bit
#define INTBITS (sizeof(int) * CHAR_BIT)     // 64位 32bit  32位 32bit
#define LONGBITS (sizeof(long) * CHAR_BIT)   // 64位 64bit  32位 32bit

/** 无符号的处理使用一个通用函数 bits是不同类型的位数 **/
/**
    无符号最大值: 全1
    0的二进制形式是每个二进制位都是0 如果类型有8bit -> 0000 0000 ~0 -> 1111 1111
    二进制减法的规则: 100 - 1 = 011 -> 100...00 - 1 = 011...11
    1 << 8 = 1 0000 0000 -> (1 << 8) - 1 = 1111 1111
*/
unsigned long unsigned_max(unsigned bits) {
    return (bits >= 64) ? ~0UL : (1UL << (bits)) - 1;
}
/** 有符号的处理使用一个通用函数 bits是不同类型的位数 **/
/**
    有符号最小值: 除最高位是1以外其余位都是0
*/
long signed_min(unsigned bits) {
    return -(1UL << (bits-1));
}
/**
    有符号的最大值: 除了最高位是0以外其余位都是1
*/
long signed_max(unsigned bits) {
    // 如果bits=8 那么1<<7 -> 1000 0000
    return (1L << (bits-1)) - 1;
}

int main(void) {
    printf("unsigned char min:0, max:%u", UCHAR_MAX);
    printf("signed char min:%d, max:%d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned short min:0, max:%u\n", USHRT_MAX);
    printf("signed short min:%d, max:%d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned int min:0, max:%u\n", UINT_MAX);
    printf("signed int min:%d, max:%d\n", INT_MIN, INT_MAX);
    printf("unsigned long min:0, max:%lu", ULONG_MAX);
    printf("signed int min:%ld, max:%ld\n", LONG_MIN, LONG_MAX);
    printf("=========================================================\n");
    printf("unsigned char min:0, max:%lu, result:%d\n", unsigned_max(CHARBITS), unsigned_max(CHARBITS) == UCHAR_MAX);
    printf("signed char min:%ld, max:%ld, result_min:%d, result_max:%d\n", signed_min(CHARBITS), signed_max(CHARBITS), signed_min(CHARBITS) == CHAR_MIN, signed_max(CHARBITS) == CHAR_MAX);
    printf("unsigned short min:0, max:%lu, result:%d\n", unsigned_max(SHORTBITS), unsigned_max(SHORTBITS) == USHRT_MAX);
    printf("signed short min:%ld, max:%ld, result_min:%d, result_max:%d\n", signed_min(SHORTBITS), signed_max(SHORTBITS), signed_min(SHORTBITS) == SHRT_MIN, signed_max(SHORTBITS) == SHRT_MAX);    
    printf("unsigned int min:0, max:%lu, result:%d\n", unsigned_max(INTBITS), unsigned_max(INTBITS) == UINT_MAX);
    printf("signed char min:%ld, max:%ld, result_min:%d, result_max:%d\n", signed_min(INTBITS), signed_max(INTBITS), signed_min(INTBITS) == INT_MIN, signed_max(INTBITS) == INT_MAX);
    printf("unsigned long min:0, max:%lu, result:%d\n", unsigned_max(LONGBITS), unsigned_max(LONGBITS) == ULONG_MAX);
    printf("signed char min:%ld, max:%ld, result_min:%d, result_max:%d\n", signed_min(LONGBITS), signed_max(LONGBITS), signed_min(LONGBITS) == LONG_MIN, signed_max(LONGBITS) == LONG_MAX);
    return 0;
    return 0;
}