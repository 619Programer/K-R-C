#include <stdio.h>

#define LIMIT 30

void printd(int n) {
    printf("==== printd start ==== %d\n", n);
    if(n < 0) {
        putchar('-');
        n = -n;
    }
    if(n / 10) {
        int temp = n / 10;
        printd(temp);
    }
    putchar(n % 10 + '0');
    printf("==== printd end ==== %d\n", n);
}

int itoa_helper(unsigned int n, char s[], int i) {
    if (n / 10)
        i = itoa_helper(n / 10, s, i);  // 一直递归到最高位才结束
    s[i++] = n % 10 + '0';  // 先在当前位置写入字符然后往后偏移一个位置
    return i; // 返回下次索引位置
}

void itoa(int n, char s[]) {
    int i = 0;
    unsigned int num;
    if (n < 0) {
        s[i++] = '-';
        // 转为无符号避免 INT_MIN 溢出 (-2147483648)
        num = -(unsigned int)n;
    } else {
        num = n;
    }
    i = itoa_helper(num, s, i);
    s[i] = '\0';  // 必须添加字符串终止符
}

int main() {
    char s[LIMIT] = {0};
    itoa(102, s);
    printf("%s\n", s);
    return 0;
}