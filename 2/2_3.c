#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int htoi(char s[]) {
    unsigned int n = 0;  // 最后的转换结果
    int i = 0;
    while(isspace((unsigned char)s[i]))  // 跳过字符串开头的空白符
        i ++;
    if(s[i] == '0' && s[i+1] != '\0' && (s[i+1] == 'x' || s[i+1] == 'X'))  // 处理0x和0X前缀
        i += 2;
    for(;; i++) {
        int digit;
        if (s[i] >= '0' && s[i] <= '9')
            digit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            digit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            digit = s[i] - 'A' + 10;
        else
            break;                 /* 非法字符，结束 */

        /**
            溢出检测 溢出时返回0
            安全阈值：(65535 - 15) / 16 = 4095
            当 n = 4095：16*4095 + 15 = 65535 安全
            当 n = 4096：16*4096 + 15 = 65551 > 65535 溢出
        */
        if (n > (UINT_MAX - digit) / 16) {
            return 0;
        }
        n = 16 * n + digit;
    }
    return n;
}

int main(void) {
    printf("%d\n",htoi("0x1234")); // 4660
    printf("%d\n",htoi("0xabcd")); // 43981
    printf("%d\n",htoi("0xCDEF")); // 52719
    printf("%d\n",htoi("1234"));
    printf("%d\n",htoi("abcd"));
    printf("%d\n",htoi("CDEF"));
    printf("%d\n",htoi("0xEFG")); // 239
    printf("%d\n",htoi("0xG")); // 0
    printf("%d\n", htoi("0"));
    return 0;
}