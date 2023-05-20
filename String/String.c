#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 40

typedef int Status;
typedef char String[MAXSIZE+1];

Status StrAssign(String S,char* str)
{
    int i;
    if(strlen(str) > MAXSIZE)
        return ERROR;
    S[0] = strlen(str);
    for(i=1; i<=S[0]; i++)
    {
        S[i] = *str++;
    }
    return OK;
}

int StrLength(String S)
{
    return S[0];
}

Status StrEmpty(String S)
{
    if(S[0] == 0)
        return TRUE;
    else
        return FALSE;
}

Status StrCopy(String dest, String src)
{
    int i;
    for(i=1;i<=src[0];i++)
    {
        dest[i] = src[i];
    }
    dest[0] = src[0];

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

Status StrCompare(String S, String S1)
{
    int i;
    for(i=1; i<=S[0]&&i<=S1[0];i++)
    {
        if(S[i] != S1[i])       //对比不一样相减，得到大于/小于
            return S[i]-S1[i];
    }
    return S[0] - S1[0];        //都相等减去长度,如果长度相等返回0 其他大于/小于
}

Status Concat(String dest,String src1,String src2)
{
    int i,j;
    //两串相加没有溢出
    if(src1[0] + src2[0] <= MAXSIZE)
    {
        for(i=1; i<=src1[0];i++)
        {
            dest[i] = src1[i];
        }
        for(j=1;j<=src2[0];j++)
        {
            dest[i] = src2[j];
            i++;
        }
        dest[0] = src1[0] + src2[0];
        return TRUE;
    }
    else
    {
        //截断
        for(i=1; i<=src1[0];i++)
        {
            dest[i] = src1[i];
        }
        for(j=1; i<=MAXSIZE-src1[0];j++)
        {         
            dest[i] = src2[j];
            i++;
        }
        dest[0] = MAXSIZE;
        return FALSE;
    }
    
}

Status SubString(String dest, String src,int pos,int len)
{
    int i = pos;
    int j;
    if(pos<1 || pos>src[0]-len || len <0 || len > src[0])
        return ERROR;
    //在位置i,得len长度的串
    for(j=1;j<=len;j++)
    {
        dest[j] = src[i++];
    }
    dest[0] = len;
    return OK;
}

Status StrDelete(String S, int pos, int len)
{
    int i;
    if(pos < 1 || pos >S[0]-len+1 || len>S[0])      //加一 S[0]不能删除
        return ERROR;
    //在第pos位置删除len长度
    i = pos;
    for(i=pos+len;i<=S[0];i++)
    {
        S[i-len] = S[i];
    }
    S[0] -= len;
}

//在dest的pos位置插入src
Status StrInsert(String dest, int pos, String src)
{
    int i,j;
    if(pos <1 || pos>dest[0]+1)
        return ERROR;
    //插入的长度没有溢出
    i = dest[0];
    if(dest[0] + src[0] <= MAXSIZE)
    {
        for(j=dest[0];j>=pos;j--)
        {
            dest[j+src[0]] = dest[j]; //在pos之后的串一个个放在dest+src的末尾
        }
        for(j=pos;j<pos+src[0];j++)     //进行插入
        {
            dest[j] = src[j-pos+1];  //j-pos+1 等于 pos-pos+1从一个开始插入
        }
        dest[0] = dest[0] + src[0];
        return TRUE;
    }
    else
    {
        //溢出截取
        for(j=MAXSIZE;j>=pos;j--)
        {
            dest[j] = dest[j-src[0]];           //将pos后的一个放在MAXSIZE最后一个，MAX--,后续依次进行
        }
        for(j=pos;j<pos+src[0];j++)             //后插入数据
        {
            dest[j] = src[i-pos + 1];
        }
        dest[0] = MAXSIZE;                      
        return FALSE;
    }

    return OK;
}

Status Index(String S1, String S2, int pos)
{
    int i = pos,j = 1;                  //i相当于主串的下标，j用于字串的起始位置
    while(i<=S1[0] && j<=S2[0])
    {
    if(S1[i] == S2[i])                  //两个字母相等则继续
    {
        i++;
        j++;
    }
    else
    {
        i = i-j+2;                  //不相等返回下标的下一个位置
        j = 1;                      //j退回第一位
    }
    }
    if(j>S2[0])                     //当对比完成j大于原来的长度
        return i-S2[0];             //主串的位置减去字串的总长度得到当前下标的位置
    else
        return 0;                   //不是则返回0
}

/*功能查找dest是否有src1的数据，有 使用src2中的串替换dest中有src1相同的元素*/  //查找替换 例如:文中找a 全部换成b
Status Replace(String dest,String src1,String src2)
{
    int i = 1;
    if(StrEmpty(src1))
        return ERROR;
    
    do
    {
          /* code */  
    i = Index(dest,src1,i);
    if(i)
    {
        StrDelete(dest,i,StrLength(src1));
        StrInsert(dest,i,src2);
        i += StrLength(src2);
    }
    } while (i);

    return OK;
}

int main()
{
    int i,j;
    char s;
    Status k;
    String s1,s2,t;
    printf("添加串s1: abcd \n");
    k = StrAssign(s1,"abcd");
    if(!k)
    {
        printf("串长超过MAXSIZE(%d)\n",MAXSIZE);
        //exit(0);
    }
    printf("串长为%d,串空否%d?(1:是 0：否)\n",StrLength(s1),StrEmpty(s1));
    StrCopy(s2,s1);
    printf("拷贝s1生成的串s2为: ");
    StrPrint(s2);
    printf("给s2添加新的串 efghijk\n");

    k = StrAssign(s2,"efghijk");
    if(!k)
    {
        printf("长度超过MAXSIZE(%d)\n",MAXSIZE);
        exit(0);
    }
    //StrPrint(s2);
    i = StrCompare(s1,s2);
    if(i<0)
     s = '<';
     else if(i == 0)
      s = '=';
      else
      s = '>';
      printf("s1 %c s2\n",s);
    
      //StrPrint(s1);
      //StrPrint(s2);
      k = Concat(t,s1,s2); //s1与s2融合相接，得到串t
      printf("s1和s2相接得到的t为: ");
      StrPrint(t);
      printf("串长为%d,串空否%d?(1:是 0：否)\n",StrLength(s1),StrEmpty(s1));
    i = 2;
      j = 3;
      printf("在t串第%d的位置拿出长度为%d的字串 ",i,j);

      k = SubString(s2,t,i,j);
      if(k)
      {
        printf("字串s2为：");
        StrPrint(s2);
      }
      i=4;
	  j=2;
      printf("从串t的第%d个字符起,删除%d个字符\n",i,j);

      StrDelete(t,i,j);
      printf("删除后t为: ");
      StrPrint(t);
      i = StrLength(s2) / 2;
      
      printf("s2为：");
      StrPrint(s2);
      printf("t为：");
      StrPrint(t);
      StrInsert(s2,i,t);
      printf("在串s2的第%d个字符之前插入串t后, 串s2为: ",i);
      StrPrint(s2);

      i = Index(s2,t,1);
      printf("s2的第%d个字母起和t第一次匹配\n",i);
      SubString(t,s2,1,1);
      printf("串t为: ");
      StrPrint(t);
      Concat(s1,t,t);
      printf("串s1为：");
      StrPrint(s1);
      Replace(s2,t,s1);
      printf("用串s1取代串s2中和串t相同的不重叠的串后,串s2为: ");
	  StrPrint(s2);

    return 0;
}