#include <stdio.h>

#define LEN 100 // dst字符数组的最大长度

void escape(char dst[], char src[]) {
    int srcIndex = 0, dstIndex = 0;
    for(;src[srcIndex] != '\0'; srcIndex ++) {
        int need = 1;
        // 这层只处理越界问题 如果是转义字符那么从当前dstIndex位置开始至少要保留3个字符空间
        switch (src[srcIndex]) {
            case '\n': case '\t': case '\r': case '\\': case '\b': case '\f':
            case '\v': case '\'': case '\"': case '\a': case '\?':
            need = 2;
            break;
        }
        // dst的长度无法保存转义后的src了直接结束
        if(dstIndex + need >= LEN) {
            break;
        }
        // 这层只负责复制字符
        switch (src[srcIndex]) {
            case '\n': dst[dstIndex++] = '\\'; dst[dstIndex++] = 'n'; break;
            case '\t': dst[dstIndex++] = '\\'; dst[dstIndex++] = 't'; break;
            case '\r': dst[dstIndex++] = '\\'; dst[dstIndex++] = 'r'; break;
            case '\\': dst[dstIndex++] = '\\'; dst[dstIndex++] = '\\'; break;
            case '\b': dst[dstIndex++] = '\\'; dst[dstIndex++] = 'b'; break;
            case '\f': dst[dstIndex++] = '\\'; dst[dstIndex++] = 'f'; break;
            case '\v': dst[dstIndex++] = '\\'; dst[dstIndex++] = 'v'; break;
            case '\'': dst[dstIndex++] = '\\'; dst[dstIndex++] = '\''; break;
            case '\"': dst[dstIndex++] = '\\'; dst[dstIndex++] = '\"'; break;
            case '\a': dst[dstIndex++] = '\\'; dst[dstIndex++] = '?'; break;
            case '\?': dst[dstIndex++] = '\\'; dst[dstIndex++] = '?'; break;
            default: dst[dstIndex++] = src[srcIndex]; break;
        }
    }
    // 结尾补字符串结束符
    dst[dstIndex] = '\0';
}

void unescape(char dst[], char src[]) {
    int srcIndex = 0, dstIndex = 0;
    // dstIndex < LEN - 1 留一个'\0'的位置
    for(;src[srcIndex] != '\0' && dstIndex < LEN - 1; srcIndex ++) {
        if(src[srcIndex] == '\\') {
            if(src[srcIndex + 1] == '\0')
                break; // 下个字符不存在直接结束
            switch(src[++srcIndex]) {
                case 'n': dst[dstIndex++] = '\n'; break;
                case 't': dst[dstIndex++] = '\t'; break;
                case 'r': dst[dstIndex++] = '\r'; break;
                case '\\': dst[dstIndex++] = '\\'; break;
                case 'b': dst[dstIndex++] = '\b'; break;
                case 'f': dst[dstIndex++] = '\f'; break;
                case 'v': dst[dstIndex++] = '\v'; break;
                case '\'': dst[dstIndex++] = '\''; break;
                case '\"': dst[dstIndex++] = '\"'; break;
                case 'a': dst[dstIndex++] = '\a'; break;
                case '?': dst[dstIndex++] = '\?'; break;
                default: dst[dstIndex++] = src[srcIndex]; break;
            }
        } else {
            // 普通字符
            dst[dstIndex ++] = src[srcIndex];
        }
    }
    // 结尾补字符串结束符
    dst[dstIndex] = '\0';
}

int main(void) {
    // 初始化
    char dst[LEN] = {0};
    char dst2[LEN] = {0};
    char src[] = "ab\ncd\tef\rhi\bjk\flm\vno\\pq\'rs\"tu\avw\?xyz";
    printf("src:%s\n", src);
    escape(dst, src);
    printf("dst:%s\n", dst);
    unescape(dst2, dst);
    printf("dst2:%s\n", dst2);
    return 0;
}