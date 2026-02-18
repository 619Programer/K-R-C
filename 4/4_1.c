#include <stdio.h>

// 返回s中最左边与t能匹配的开始索引
int strindex(char s[], char t[]) {
    int i, j, k;
    for(i = 0; s[i] != '\0'; i ++) {
        for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j ++, k ++)
            ;
        if(k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

// 返回s中最右边与t能匹配地开始索引
int strindex2(char s[], char t[]) {
    int i, j, k;
    int result = -1;
    for(i = 0; s[i] != '\0'; i ++) {
        for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j ++, k ++)
            ;
        if(k > 0 && t[k] == '\0')
            result = i;
    }
    return result;
}

int main() {
    char s[] = "ouldabcdefgould12345ould";
    char t[] = "ould";
    printf("strindex:%d\n", strindex(s, t));
    printf("strindex2: %d\n", strindex2(s, t));
    return 0;
}