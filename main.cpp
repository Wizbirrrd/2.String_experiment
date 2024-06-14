#include <iostream>
#include <stdlib.h>
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define INITSIZE 20
#define ARGC 3

typedef int Status;

typedef struct
{
    char *ch;
    int length;
} HString; ////堆分配存储串

Status InitSting(HString &S)
{
    S.ch = (char *)malloc(INITSIZE * sizeof(char));
    if (!S.ch)
        exit(OVERFLOW);
    S.length = 0;
    return OK;
}

Status StrAssign(HString &T, char *chars)
{
    T.length = 0;
    for (T.length = 0; chars[T.length]; T.length++)
        ;
    T.ch = (char *)malloc(T.length * sizeof(char));
    if (!T.ch)
        exit(OVERFLOW);
    for (int i = 1; chars[i - 1]; i++)
    {
        T.ch[i] = chars[i - 1]; // 首位不存,方便KMP算法编写
    }
    return OK;
}

Status StrCopy(HString &T, HString S)
{
    T = S;
    return OK;
}

Status StrEmpty(HString S)
{
    if (S.length == 0)
        return TRUE;
    return FALSE;
}

int StrCompare(HString S, HString T)
{
    int i = 1;
    while (i < S.length && i < T.length)
    {
        if (S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];
        i++;
    }
    return S.length - T.length;
}

int StrLength(HString S) { return S.length; }

Status SubString(HString &Sub, HString S, int pos, int len)
{
    if (pos + len - 1 > S.length)
        return ERROR;
    for (int i = 1; i <= len; i++)
    {
        Sub.ch[i] = S.ch[pos + i - 1];
    }
    Sub.ch[len + 1] = '\0';
    Sub.length = len;

    return OK;
}

Status Concat(HString &T, HString S1, HString S2)
{
    for (int i = 1; i <= S1.length; i++)
    {
        T.ch[i] = S1.ch[i];
    }
    for (int i = 1; i <= S2.length; i++)
    {
        T.ch[i + S1.length] = S2.ch[i];
    }
    T.length = S1.length + S2.length;
    return OK;
}

Status get_nextval(HString t, int next[])
{
    int i = 1, j = 0;
    next[1] = 0;
    while (i <= t.length)
    {
        if (j == 0 || t.ch[i] == t.ch[j])
        {
            i++;
            j++;
            if (t.ch[i] != t.ch[j])
            {
                next[i] = j;
            }
            else
            {
                next[i] = next[j];
            }
        }
        else
        {
            j = next[j];
        }
    }
    return OK;
}

int KMP(HString s, HString t, int next[])
{
    int i = 1, j = 1;
    while (i <= s.length && j <= t.length)
    {
        if (j == 0 || s.ch[i] == t.ch[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j > t.length)
    {
        return i - t.length;
    }
    else
    {
        return -1;
    }
}

Status ClearString(HString &S)
{
    S.length = 0;
    return OK;
}

Status DestoryString(HString &S)
{
    free(S.ch);
    S.length = 0;
    return OK;
}

int main(int argc, char **argv)
{
    HString s, t;
    if (argc != ARGC)
    {
        printf("ERROR_01");
        return ERROR;
    } // 命令行参数检查

    InitSting(s);
    InitSting(t);
    StrAssign(s, argv[1]);
    StrAssign(t, argv[2]);

    int *next = (int *)malloc(t.length * sizeof(int));
    if (!next)
    {
        exit(OVERFLOW);
    }
    get_nextval(t, next);
    cout << "S: \"" << argv[1] << "\"\n";
    cout << "T: \"" << argv[2] << "\"\n";
    cout << "return: " << KMP(s, t, next) << endl;

    DestoryString(s);
    DestoryString(t);
    free(next); // 释放内存

    return 0;
}