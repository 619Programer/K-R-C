#include <stdio.h>
#include <string.h>

void reverse1(char s[]) {
    int start = 0;
    int end = strlen(s)-1;
    printf("start:%d, end:%d\n", start, end);
    while(start < end) {
        printf("s[%d]:%c, s[%d]:%c\n", start, s[start], end, s[end]);
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

void process(char s[], int start, int end) {
    // 函数结束
    if(start >= end){
        printf("==== process return ==== start:%d, end:%d\n", start, end);
        return;
    }
    printf("==== process start ==== start:%d, end:%d\n", start, end);
    char temp = s[start];
    s[start] = s[end];
    s[end] = temp;
    process(s, start+1, end-1);
    printf("==== process end ==== start:%d, end:%d\n", start, end);
}

void reverse2(char s[]) {
    int start = 0;
    int end = strlen(s) - 1;
    process(s, start, end);
}

int main() {
    char s[] = "hello world";
    printf("%s\n", s);
    reverse2(s);
    printf("%s\n", s);
    return 0;
}