#include <stdio.h>
#include <string.h>

#define LEN 20

void reverse(char s[]) {
    int i, j;
    for(i = 0, j = strlen(s) - 1; i < j; i ++, j --) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

void itoa(int n, char s[], unsigned int width) {
    int i, sign;
    unsigned int nTemp;
    nTemp = (sign = n) < 0 ? -(unsigned int)n : (unsigned int)n;
    i = 0;
    do {
        s[i++] = nTemp % 10 + '0';
    } while((nTemp /= 10) > 0);
    if(sign < 0)
        s[i++] = '-';
    while(i < width) {
        s[i++] = ' ';
    }
    s[i] = '\0';
    reverse(s);
}

int main() {
    int a = 12345;
    char s[LEN] = {0};
    itoa(a, s, 10);
    printf("%s\n", s);
    return 0;
}