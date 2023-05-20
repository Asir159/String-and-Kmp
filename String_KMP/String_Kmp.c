#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;

typedef char String[MAXSIZE+1];

Status StrAssign(String S,char *str)
{
    int i;
    if(strlen(str) > MAXSIZE)
    {
        return ERROR;
    }
    else
    {
        S[0] = strlen(str);
        for(i=1; i<=S[0]; i++)
        {
            S[i] = str[i-1];
        }
    }

    return OK;
}

Status StrPrint(String S)
{
    int i;
    for(i=1; i<=S[0];i++)
    {
        printf("%c ",S[i]);
    }
    printf("\n");

    return OK;
}

int StrLength(String S)
{
    return S[0];
}

/* 通过计算返回子串T的next数组。 */
Status Get_next(String S,int *next)
{
    int i = 1;
    int k = 0;
    next[1] = 0;            //第一默认为零
    while(i <S[0])
    {
        if(k==0 || S[i] == S[k])
        {
            i++;
            k++;
            next[i] = k;
        }
        else
        {
            k = next[k];
        }
    }
    return OK;
}

Status NextPrint(int *next, int len)
{
    int i;
    for(i=1; i<=len; i++)
    {
        printf("%d ",next[i]);
    }
    printf("\n");

    return OK;
}

/* 求模式串T的next函数修正值并存入数组nextval */
Status Get_nextval(String S, int *next)
{
    int i = 1;
    int k = 0;
    next[1] = 0;

    while(i<S[0])
    {
        if(k==0 || S[i] == S[k])        /* T[i]表示后缀的单个字符，T[k]表示前缀的单个字符 */
        {
            i++;    
            k++;                         /* 若当前字符与前缀字符不同 */
            if(S[i] != S[k])               /* 则当前的j为nextval在i位置的值 */
                next[i] = k;
            else         
                next[i] = next[k];      /* 如果与前缀字符相同，则将前缀字符的 */
                                        /* nextval值赋值给nextval在i位置的值 */
        }
        else
        {
            k = next[k];                /* 若字符不相同，则k值回溯 */
        }
    }

    return OK;
}

Status Index(String S1, String S2,int pos)
{
    if(pos < 1 || pos >S1[0]-S2[0]+1)
        return ERROR;
    int n = 0;
    int i = pos;
    int j = 1;

    while(i <=S1[0] && j<=S2[0])
    {
        if(S1[i] == S2[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i-j+2;
            j = 1;
            printf("n=%d i=%d j=%d\n",++n,i,j);  
        }
    }
    if(j >S2[0])
    {
        return i-S2[0];
    }
    else
        return 0;
}

Status Index_Kmp(String S1, String S2,int pos)
{
    int n = 0;
    int i = pos;
    int j = 1;
    int next[MAXSIZE+1];        
    if(pos < 1 || pos >S1[0]-S2[0]+1)
        return ERROR;
    
    Get_next(S2,next);      /* 对串T作分析，得到next数组 */
    while(i<=S1[0] && j<=S2[0])
    {
        if(j==0 || S1[i] == S2[j])          /* 两字母相等则继续，与朴素算法增加了j=0判断    j=0的情况为长度为1的时候*/ 
        {
            i++;
            j++;
        }
        else                        /* 指针后退重新开始匹配 */
        {
            j=next[j];              /* j退回合适的位置，i值不变 */
            printf("n=%d i=%d j=%d\n",++n,i,j);  
        }
    }
    if(j>S2[0])
        return i-S2[0];
    else
        return 0;
}

Status Index_Kmp1(String S1,String S2, int pos)
{
    int n = 0;
    int i = pos;
    int j = 1;
    int next[MAXSIZE+1];
    if(pos <1 || pos >S1[0]-S2[0]+1)
        return ERROR;
    Get_nextval(S2,next);
    while(i<=S1[0] && j<=S2[0])
    {
        if(j==0 || S1[i] == S2[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
            printf("n=%d i=%d j=%d\n",++n,i,j);  
        }
    }
    if(j>S2[0])
        return i-S2[0];
    else
        return 0;
}
int main()
{
    int i,*p=NULL;
    String s1,s2;
    StrAssign(s1,"abcdex");
    printf("字串为: ");
    StrPrint(s1);
    i = StrLength(s1);

    p = (int *)malloc((i+1)*sizeof(int));
    Get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
   free(p);

    StrAssign(s1,"abcabx");
    printf("子串为：");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *)malloc(i+1*(sizeof(int)));
    Get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
    free(p);

    StrAssign(s1,"ababaaaba");
    printf("子串为：");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *)malloc(i+1*(sizeof(int)));
    Get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
   free(p);

    StrAssign(s1,"aaaaaaaab");
    printf("子串为：");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *)malloc(i+1*(sizeof(int)));
    Get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
   free(p);

    StrAssign(s1,"ababaaaba");
    printf("子串为：");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *)malloc(i+1*(sizeof(int)));
    Get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    Get_nextval(s1,p);
    printf("NextVal为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
    free(p);

    StrAssign(s1,"aaaaaaaab");
    printf("子串为：");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *)malloc(i+1*(sizeof(int)));
    Get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    Get_nextval(s1,p);
    printf("NextVal为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
    free(p);

    StrAssign(s1,"000000000200000000020000000002000000000200000000020000000001");
    printf("主串为: ");
    StrPrint(s1);
    StrAssign(s2,"0000001");
    printf("字串为: ");
    StrPrint(s2);
    printf("\n");

    printf("主串和字串在第%d个字符出首次匹配(朴素匹配算法)\n",Index(s1,s2,1));
    printf("主串和字串在第%d个字符出首次匹配(KMP匹配算法)\n",Index_Kmp(s1,s2,1));
    printf("主串和字串在第%d个字符出首次匹配(改良kmp算法)\n",Index_Kmp1(s1,s2,1));

    return 0;
}