#include <stdio.h>
#include <ctype.h>

double atof(char s[]) {
    double val, power;
    int i, sign;
    // 科学计数法的指数
    int expVal = 0;
    // 科学计数法的正负
    int expSign = 1;

    // 跳过空白符
    for(i = 0; isspace(s[i]); i++)
        ;
    // 设置正负
    sign = s[i] == '-' ? -1 : 1;
    // 跳过符号
    if(s[i] == '+' || s[i] == '-')
        i++;
    // 处理小数点前面的数
    for(val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    // 跳过小数点
    if(s[i] == '.')
        i++;
    // 处理小数点后面的数
    for(power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    // 先处理val
    val = sign * val / power;
    // 开始处理科学计数法
    if(s[i] == 'e' || s[i] == 'E') {
        i++;
        // 处理指数的正负
        if(s[i] == '+') {
            i++;
        }else if(s[i] == '-') {
            expSign = -1;
            i++;
        }
        // 处理指数部分
        for(; isdigit(s[i]); i ++)
            expVal = 10 * expVal + (s[i] - '0');
        // 根据指数和指数的正负重新处理val
        if(expSign == -1) {
            while(expVal-- > 0)
                val /= 10.0;
        } else {
            while(expVal-- > 0)
                val *= 10.0;
        }
    }
    return val;
}

int main() {
    char s[] = "123.45e-6";
    printf("%.10g\n", atof(s));
    return 0;
}