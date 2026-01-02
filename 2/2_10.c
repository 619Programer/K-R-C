/**
等价代码
(expr1) ? expr2 : expr3;

if(expr1) {
    expr2
} else {
    expr3
}
**/

#include <stdio.h>

int lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}

int main(void) {
    putchar(lower('A'));
    putchar(lower('a'));
    return 0;
}