#include <stdio.h>

// 将s2中任一字符再s1中第一次出现的位置作为结果返回
int any(char s1[], char s2[]) {
    for(int i = 0; s1[i] != '\0'; i++) {
        for(int j = 0; s2[j] != '\0'; j++) {
            if(s1[i] == s2[j]) {
                return i;
            }
        }
    }
    return -1;
}

int main(void) {
    printf("%d\n", any("hello world", "oa"));    // 输出: 4  (字符'o'第一次出现)
    printf("%d\n", any("hello world", "xyz"));   // 输出: -1 (找不到)
    printf("%d\n", any("hello world", "ab"));    // 输出: -1 (a和b都不存在)
    printf("%d\n", any("hello world", "ow"));    // 输出: 4  (o在w之前)
    printf("%d\n", any("hello world", "d"));     // 输出: 10 (字符'd')
    return 0;
}