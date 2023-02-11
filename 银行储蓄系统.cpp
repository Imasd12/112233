#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
void openaccount();//开户
void save();//存款
void withdraw();//取款
void showAccount();//查询
void transferAccounts();//转账
void reportLoss();  //挂失
void cancelLoss();  //解除挂失
void cancelAccount();  //注销账户
void updatePassword();   //更改密码
int load();//登陆账号
int accountnum=0;//定义全局变量，用来计算账户数目
int nowaccount=0;//登录成功是的账户
struct Bank
{
    char account[20]; //账号
    char password[7]; //密码
    char name[20];   //用户名
    int balance;//账户余额
    int state;//状态
};    //结构体
struct Bank banks[100];
int load()
{
    int right=0,i=0,j;
    int r1,r2;
    char ch;
    char account1[20]= {0};
    char password1[10]= {0};
    printf("登陆\n请输入账号：\n");
    scanf("%s",account1);
    printf("请输入密码：\n");
    while((ch=getch())!='\r')
    {
        password1[i++]=ch;
        putchar('*');
    }
    for(j=0; j<accountnum; j++)
    {
        r1=strcmp(account1,banks[j].account);
        r2=strcmp(password1,banks[j].password);
        if(r1==0&&r2==0)
        {
            nowaccount=j;
            if(banks[j].state==0)
            {
                printf("登录成功！\n");//登录成功
                right=1;
            }
            else if(banks[j].state==1)
            {
                printf("您的账户处于挂失状态,请解挂\n");
                right=3;
            }
            else if(banks[j].state==2)
            {
                printf("账户已经销户\n");
                right=2;
            }
            break;
        }
    }
 
    if(right==0)
        printf("登陆失败！\n");
    return right;
}
int main()
{
    int i=0,num;
    char a[100];
    FILE *fp;
    if((fp=fopen("account.txt","r"))==NULL)
    {
        if((fp=fopen("account.txt","w"))==NULL)
        {
            printf("失败！\n");
            exit(1);
        }
    }
    while(fscanf(fp,"%s%s%s%d%d",banks[i].account,banks[i].name,banks[i].password,&banks[i].balance,&banks[i].state)!=EOF)
    {
        accountnum++;
        i++;
    }
    fclose(fp);
    printf("欢迎来到我的银行\n");
    while(1)
    {
        printf("请选择业务:\n");
        printf("1.开户    2.存款    3.取款\n");
        printf("4.查询    5.转账    6.挂失\n");
        printf("7.解挂    8.销户    9.改密\n");
        printf("-1.退出\n");
        scanf("%s",a);
        num=atoi(a);
        if(num==1)
            openaccount();//开户
        else if(num==2)
            save();//存款
        else if(num==3)
            withdraw();//取款
        else if(num==4)
            showAccount();//查询
        else if(num==5)
            transferAccounts();//转账
        else if(num==6)
            reportLoss();  //挂失
        else if(num==7)
            cancelLoss();  //解挂
        else if(num==8)
            cancelAccount();  //注销账户
        else if(num==9)
            updatePassword();   //更改密码
        else if(num==-1)
        {
            printf("欢迎下次再来\n");
            break;
        }
 
        else
            printf("抱歉，没有此业务\n");
    }
    if((fp=fopen("account.txt","w"))==NULL)
    {
        printf("失败！\n");
        exit(1);
    }
    for(i=0; i<accountnum; i++)
    {
        fprintf(fp,"%s\t%s\t%s\t%d\t%d\n",banks[i].account,banks[i].name,banks[i].password,banks[i].balance,banks[i].state);
    }
    fclose(fp);
    return 0;
}
void openaccount()
{
 
    int i=0,j=0;
    int r;
    char ch;
    char password1[10]= {0};
    printf("账户（十位数）：\n");
    scanf("%s",banks[accountnum].account);
    while(banks[accountnum].account[i]!='\0')
        i++;
    if(i!=10)
    {
        printf("输入账号有误\n");
        return;
    }
    i=0;
    printf("姓名：\n");
    scanf("%s",banks[accountnum].name);
    printf("密码：\n");
    while((ch=getch())!='\r')
    {
        banks[accountnum].password[i++]=ch;
        putchar('*');
    }
    printf("\n");
    printf("再次输入密码：\n");
    while((ch=getch())!='\r')
    {
        password1[j++]=ch;
        putchar('*');
    }
    printf("\n");
    r=strcmp(banks[accountnum].password,password1);
    if(r!=0)
    {
 
        printf("两次密码不相同，开户失败！\n");
        return;
    }
    banks[accountnum].balance=0;
    banks[accountnum].state=0;
    accountnum++;
    printf("开户成功\n");
}
void save()
{
    if(load()!=1)
        return;
    char addmoney[10];//存入金额
    int money;//将字符型转化为int型
    int i=0;
    printf("存入金额:\n");
    scanf("%s",addmoney);
    while(addmoney[i]!='\0')
    {
        if(addmoney[i]<'0'||addmoney[i]>'9')
        {
            printf("输入格式错误！\n");
            return;
        }
        i++;
    }
    while(addmoney[i]!='\0')
    {
        if(i>9)
        {
            printf("金额超限\n");
            return;
        }
        i++;
    }
    money=atoi(addmoney);
    if(money==0)
    {
        printf("存款失败\n");
        return;
    }
    else
    {
        banks[nowaccount].balance+=money;
        printf("存款成功\n");
    }
}
void withdraw()
{
    if(load()!=1)
        return;
    char reducemoney[10];//取款金额
    int money,i=0;
    printf("请输入取款金额\n");
    scanf("%s",reducemoney);
    while(reducemoney[i]!='\0')
    {
        if(reducemoney[i]<'0'||reducemoney[i]>'9')
        {
            printf("输入格式错误！\n");
            return;
        }
        i++;
    }
    while(reducemoney[i]!='\0')
    {
        if(i>9)
        {
            printf("金额超限\n");
            return;
        }
        i++;
    }
    money=atoi(reducemoney);
    if(money==0)
    {
        printf("取款失败\n");
        return;
    }
    else
    {
        if(money>banks[nowaccount].balance)
            printf("您的账户没有这么多余额,取款失败!\n");
        else
        {
            banks[nowaccount].balance-=money;
            printf("取款成功\n");
        }
    }
}
void showAccount()
{
    if(load()!=1&&load()!=2)
        return;
    printf("您的账户信息如下：\n");
    printf("账号：%s\t余额：%d\n",banks[nowaccount].account,banks[nowaccount].balance);
}
void transferAccounts()
{
    if(load()!=1)
        return;
    char account1[20];
    int i,judge=0,money,a;
    char tramoney[10];
    printf("请输入您转入的账户\n");
    scanf("%s",account1);
    for(i=0; i<accountnum; i++)
    {
        if(strcmp(account1,banks[i].account)==0)
        {
            a=i;
            judge=1;
            break;
        }
    }
    if(judge!=1)
     {
         printf("没有发现此账户\n");
         return;
     }
    printf("请输入转账金额\n");
    scanf("%s",tramoney);
    while(tramoney[i]!='\0')
    {
        if(tramoney[i]<'0'||tramoney[i]>'9')
        {
            printf("输入格式错误！\n");
            return;
        }
        i++;
    }
    while(tramoney[i]!='\0')
    {
        if(i>9)
        {
            printf("金额超限\n");
            return;
        }
        i++;
    }
    money=atoi(tramoney);
    if(money==0)
    {
        printf("转账失败\n");
        return;
    }
    else
    {
        if(money>banks[nowaccount].balance)
            printf("您的账户没有这么多余额,转账失败!\n");
        else
        {
            banks[nowaccount].balance-=money;
            banks[a].balance+=money;
            printf("转账成功\n");
        }
    }
 
}
void reportLoss()
{
    if(load()!=1)
        return;
    banks[nowaccount].state=1;
    printf("挂失成功\n");
}
void cancelLoss()
{
    int judge=0;
    if(load()==3)
    {
        printf("立即解挂请按1，退出请按0\n");
        scanf("%d",&judge);
        if(judge==1)
        {
            banks[nowaccount].state=0;
            printf("解挂成功\n");
        }
 
    }
    else if(load()==1)
        printf("账户正常\n");
}
void cancelAccount()
{
    int r;
    r=load();
    if(r==2)
    {
        printf("账户已经销户\n");
        return;
    }
    else if(r==3||r==0)
        return;
    else if(r==1)
    {
        printf("请将您的账户余额取完\n");
        banks[nowaccount].state=2;
        banks[nowaccount].balance=0;
        printf("注销成功\n");
    }
}
void updatePassword()
{
    char newpassword1[10]= {0},newpassword2[10]= {0};
    int i=0,j=0,r;
    char ch;
    if(load()!=1)
        return;
    printf("请输入新密码\n");
    while((ch=getch())!='\r')
    {
        newpassword1[i++]=ch;
        putchar('*');
    }
    printf("\n");
    printf("再次输入密码：\n");
    while((ch=getch())!='\r')
    {
        newpassword2[j++]=ch;
        putchar('*');
    }
    printf("\n");
    r=strcmp(newpassword1,newpassword2);
    printf("r:%d",r);
    if(r!=0)
    {
 
        printf("两次密码不相同，改密失败！\n");
        return;
    }
    i=0;
    while(newpassword1[i]!='\0')
    {
        banks[nowaccount].password[i]=newpassword1[i];
        i++;
    }
    printf("改密成功\n");
}
