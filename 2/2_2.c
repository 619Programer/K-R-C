#include <stdio.h>

#define LIMITS 100

// 原书给的getline程序
int myGetline(char s[], int limit) {
    int i;
    int c;
    for(i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if(c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int myGetlineWithoutLogic(char s[], int limit) {
    int i;
    int c;
    for(i = 0; i < limit - 1; i ++) {
        c = getchar();
        if(c == EOF)
            break;
        if(c == '\n')
            break;
        s[i] = c;
    }
    if(c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int main(void) {
    char s[LIMITS];
    myGetlineWithoutLogic(s, LIMITS);
    printf("%s", s);
    return 0;
}