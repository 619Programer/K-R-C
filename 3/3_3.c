#include <stdio.h>
#include <ctype.h>

#define LEN 100

// 校验字符是否合法范围 合法0-9 a-z A-Z
int isValidRange(char startChar, char endChar) {
    if(startChar > endChar) return 0;
    return (islower(startChar) && islower(endChar))
            || (isupper(startChar) && isupper(endChar))
            || (isdigit(startChar) && isdigit(endChar));
}

void expend(char s1[], char s2[]) {
    int i, j;
    char c, prev = '\0';
    for(i = j = 0; (c = s1[i]) != '\0' && j < LEN - 1; ) {
        if(prev != '\0' && c == '-' && s1[i+1] != '\0' && isValidRange(prev, s1[i+1])) {
            char end = s1[i+1];
            int maxExpend = (LEN - 1 - j) < (end - prev) ? (LEN - 1 - j) : (end - prev);
            char cur = prev;
            while(maxExpend-- && ++cur <= end) {
                s2[j++] = cur;
            }
            prev = end;
            i += 2;
            continue;
        }
        prev = c;
        s2[j++] = c;
        i ++;
    }
    s2[j] = '\0';
}

int main() {
char s1[] = "a-z";
    char s2[] = "a-b-c";
    char s3[] = "a-z0-9";
    char s4[] = "-a-z";
    char t1[LEN] = {0};
    char t2[LEN] = {0};
    char t3[LEN] = {0};
    char t4[LEN] = {0};
    expend(s1, t1);
    printf("s1:%s\n, t1:%s\n============\n", s1, t1);
    expend(s2, t2);
    printf("s2:%s\n, t2:%s\n============\n", s2, t2);
    expend(s3, t3);
    printf("s3:%s\n, t3:%s\n============\n", s3, t3);
    expend(s4, t4);
    printf("s4:%s\n, t4:%s\n============\n", s4, t4);
    return 0;
}