#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
// 这个程序是从终端将一个完整的数读出来(1.234) 返回这个标识符
#define NUMBER '0'
// 借鉴原书NUMBER的方式 增加一个字符串表示符
#define STRING '#'

// 在stack.c中有实现
extern void push(double);
extern double pop(void);
// 打印栈顶元素
extern double peek(void);
// 拷贝栈顶元素
extern void copy(void);
// 交换栈顶元素
extern void swap(void);
// 清空栈
extern void clear(void);

// 缓冲区 保存多读取的字符
#define BUFSIZE 100
// bufp指向当前能使用的缓冲区位置 bufp=0 缓冲区是空的
int bufp = 0;
// buf缓冲区 从终端读的都是字符类型 防止有ASCII没有的字符使用int来保存
int buf[BUFSIZE] = {0};
// 优先从缓冲区读字符 缓冲区读完了从终端读
int getch() {
    // bufp指向能使用的缓冲区的位置 bufp后面的位置才要使用的字符
    return (bufp > 0) ? buf[--bufp] : getchar();
}
// 将字符放入缓冲区
void ungetch(int ch) {
    if(bufp >= BUFSIZE) {
        printf("error: buf is full\n");
    } else {
        // bufp指向能使用的缓冲区的位置 写入后要将bufp往后偏移一个位置
        buf[bufp++] = ch;
    }
}

// 读取一个数字或操作符写入到s
int getop(char s[]) {
    // i:s的下标 c:当前读取的字符
    int i, c;
    // 跳过空格 制表符
    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    // s[0]可能是一个操作符或数字 先补一个结束符 如果是操作符直接返回
    s[1] = '\0';

    // 增加一步读取命令的操作 为了支持sin exp pow 
    if(isalpha(c)) {
        i = 0;
        while(isalpha(s[++i] = c = getch()))
            ;
        // 命令读完了
        s[i] = '\0';
        if(c != EOF) {
            ungetch(c);
        }
        // 只输入了一个字母 练习4_6将单个字母作为变量使用
        if(strlen(s) == 1) {
            return s[0];
        }
        return STRING;
    }

    if(!isdigit(c) && c != '.')
        return c; // 是操作符直接返回
    // 要读取数字了 下标重设
    i = 0;
    // 读整数部分 不能超过s的长度 还要给\0留空间
    if(isdigit(c)) {
        while(i < MAXOP-2 && isdigit(s[++i] = c = getch()))
            ;
    }
    // 读小数部分 不能超过s的长度 还要给\0留空间
    if(c == '.') {
        while(i < MAXOP-2 && isdigit(s[++i] = c = getch()))
            ;
    }
    // 开始读数了 读到了第一个非数字字符 数读完了
    s[i] = '\0';
    if(c != EOF) {
        // 将多读取的字符写回到缓冲区
        ungetch(c);
    }
    return NUMBER;
}

// 读取一个数字或操作符写入到s
int getop2(char s[]) {
    // 使用static修饰保证下次getop调用时能访问到上次反压的字符
    static int lastCh = EOF;

    // i:s的下标 c:当前读取的字符
    int i, c;
    // 上次有反压的字符先取上次反压的字符
    if(lastCh != EOF) {
        c = lastCh;
        lastCh = EOF;
    } else {
        c = getchar();
    }
    // 跳过空格 制表符
    while(c == ' ' || c == '\t')
        c = getchar();
    // s[0]可能是一个操作符或数字 先补一个结束符 如果是操作符直接返回
    s[0] = c;
    s[1] = '\0';

    if(!isdigit(c) && c != '.')
        return c; // 是操作符直接返回
    // 要读取数字了 下标重设
    i = 0;
    // 读整数部分 不能超过s的长度 还要给\0留空间
    if(isdigit(c)) {
        while(i < MAXOP-2 && isdigit(s[++i] = c = getchar()))
            ;
    }
    // 读小数部分 不能超过s的长度 还要给\0留空间
    if(c == '.') {
        while(i < MAXOP-2 && isdigit(s[++i] = c = getchar()))
            ;
    }
    // 开始读数了 读到了第一个非数字字符 数读完了
    s[i] = '\0';
    if(c != EOF) {
        lastCh = c;
    }
    return NUMBER;
}

#define LIMIT 100
// 读一整行数据
int myGetline(char s[], int limit) {
    int i, c;
    for(i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if(c == '\n')
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}
// 直接解析myGetline读取的数据
int getop3(char s[]) {
    static char line[LIMIT] = {0};
    static int i = 0;
    int c, j;
    if(line[i] == '\0') {
        if(myGetline(line, LIMIT) == 0)
            return EOF; // 没读到返回EOF在main函数里面结束程序
        i = 0; // 读到新行了 重置
    }
    // 跳过空白符
    while((s[0] = c = line[i++]) == ' ' || c == '\t') {
        if(line[i] == '\0')   // 这行读完了 重读一行
            return getop3(s);
    }
    s[1] = '\0';
    if(!isdigit(c) && c != '.')
        return c; // 操作符
    j = 0;
    if(isdigit(c)) {
        while(isdigit(s[++j] = c = line[i++]))
            ;
    }
    if(c == '.') {
        while(isdigit(s[++j] = c = line[i++]))
            ;
    }
    s[j] = '\0';
    // 已经把数据全都到line里面了 调整下标就能重新访问 不是getchar那种读完就没了
    if(c != '\n' && c != '\0')
        i--; // 回退一个字符
    return NUMBER;
}

/**
 * 主函数流程
 * while(下个字符是数字或操作符) {
 *     if(是数)
 *         将数添加到栈
 *     else if(是操作符)
 *         从栈里面取出操作符需要的数字数
 *         执行运算
 *         将数据放回栈
 *     else if(是换行符)
 *         弹出并打印栈顶数据
 *     else
 *         出错
 * }
*/
int main() {
    int type;
    double op2 = 0.0;
    char s[MAXOP] = {0};

    // 新增val数组
    double val[26] = {0};
    double lastVal = 0.0;

    while ((type = getop3(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case STRING:
                if(strcmp(s, "print") == 0) {
                    op2 = peek();
                    printf("stack top: %.8g\n", op2);
                } else if(strcmp(s, "copy") == 0) {
                    copy();
                } else if(strcmp(s, "swap") == 0) {
                    swap();
                } else if(strcmp(s, "clear") == 0) {
                    clear();
                } else if(strcmp(s, "sin") == 0) {
                    push(sin(pop()));
                } else if (strcmp(s, "exp") == 0) {
                    push(exp(pop()));
                } else if (strcmp(s, "pow") == 0) {
                    op2 = pop();
                    push(pow(pop(), op2));
                } else {
                    printf("main():139 error: unknown command\n");
                }
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if(op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: 0 divisor\n");
                break;
            case '\n':
                lastVal = pop();
                printf("%.8g\n", lastVal);
                break;
            case '@':
                push(lastVal);
                break;
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
            case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
            case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x':
            case 'y': case 'z':
                push(val[type - 'a']);
                break;
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H':
            case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
            case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
            case 'Y': case 'Z':
                val[type - 'A'] = pop();
                break;
            case '%':
                op2 = pop();
                if(op2 != 0.0) {
                    push(fmod(pop(), op2));
                } else {
                    printf("error: 0 mod\n");
                }
                break;
            default:
                printf("main():187 error: unknow command\n");
                break;
        }
    }
    return 0;
}