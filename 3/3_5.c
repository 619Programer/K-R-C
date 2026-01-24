#include <stdio.h>
#include <string.h>

#define LEN 20

void reverse(char s[]) {
    for(int i = 0, j = strlen(s)-1; i < j; i ++, j --) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

void itob(int n, char s[], int b) {
    if(b < 2 || b > 16)
        return;
    unsigned int nTemp;
    int sign, i = 0;
    nTemp = (sign = n) < 0 ? -(unsigned int)n : (unsigned int)n;
    do {
        s[i++] = nTemp % b + '0';
    } while ((nTemp /= b) > 0);
    if(sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main() {
    char s1[LEN] = {0};
    char s2[LEN] = {0};
    char s3[LEN] = {0};
    itob(100, s1, 2);
    itob(100, s2, 8);
    itob(100, s3, 16);
    printf("2: %s\n", s1);
    printf("8: %s\n", s2);
    printf("16: %s\n", s3);
    return 0;
}