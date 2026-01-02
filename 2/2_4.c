#include <stdio.h>

void squeeze2(char s1[], char s2[]) {
    int i, j, k;
    for(j = 0; s2[j] != '\0'; j ++) {
        // k是当前遍历的字符的前个字符 只有不是s2中的字符时k才会往前移动
        for(i = 0, k = 0; s1[i] != '\0'; i ++) {
            if(s1[i] != s2[j])
                s1[k++] = s1[i];
        }
        s1[k] = '\0'; // 遍历一次s后加上\0
    }
}

int main(void) {
    char s2[] = "abccba";
    char t2[] = "ab";
    squeeze2(s2, t2);
    printf("%s\n", s2);
    return 0;
}