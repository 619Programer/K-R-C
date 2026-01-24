#include <stdio.h>
#include <string.h>
#include <limits.h>

#define LEN 20

void reverse(char s[]) {
    for(int i = 0, j = strlen(s)-1; i < j; i ++, j --) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

void itoa(int n, char s[]) {
    int i, sign;
    if((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if(sign < 0)
        s[i++] = '-';
    reverse(s);
}

void itoa2(int n, char s[]) {
    int i, sign;
    unsigned int nTemp;
    nTemp = (sign = n) < 0 ? -(unsigned int)n : (unsigned int)n;
    i = 0;
    do {
        s[i++] = nTemp % 10 + '0';
    } while ((nTemp /= 10) > 0);
    if(sign < 0)
        s[i++] = '-';
    reverse(s);
}

int main() {
    int a = INT_MIN;
    char s[LEN] = {0};
    itoa2(a, s);
    printf("%s\n", s);

    char b = -128;
    printf("%d\n", b);
    printf("%d\n", ~b);
    return 0;
}