#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
void openaccount();//����
void save();//���
void withdraw();//ȡ��
void showAccount();//��ѯ
void transferAccounts();//ת��
void reportLoss();  //��ʧ
void cancelLoss();  //�����ʧ
void cancelAccount();  //ע���˻�
void updatePassword();   //��������
int load();//��½�˺�
int accountnum=0;//����ȫ�ֱ��������������˻���Ŀ
int nowaccount=0;//��¼�ɹ��ǵ��˻�
struct Bank
{
    char account[20]; //�˺�
    char password[7]; //����
    char name[20];   //�û���
    int balance;//�˻����
    int state;//״̬
};    //�ṹ��
struct Bank banks[100];
int load()
{
    int right=0,i=0,j;
    int r1,r2;
    char ch;
    char account1[20]= {0};
    char password1[10]= {0};
    printf("��½\n�������˺ţ�\n");
    scanf("%s",account1);
    printf("���������룺\n");
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
                printf("��¼�ɹ���\n");//��¼�ɹ�
                right=1;
            }
            else if(banks[j].state==1)
            {
                printf("�����˻����ڹ�ʧ״̬,����\n");
                right=3;
            }
            else if(banks[j].state==2)
            {
                printf("�˻��Ѿ�����\n");
                right=2;
            }
            break;
        }
    }
 
    if(right==0)
        printf("��½ʧ�ܣ�\n");
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
            printf("ʧ�ܣ�\n");
            exit(1);
        }
    }
    while(fscanf(fp,"%s%s%s%d%d",banks[i].account,banks[i].name,banks[i].password,&banks[i].balance,&banks[i].state)!=EOF)
    {
        accountnum++;
        i++;
    }
    fclose(fp);
    printf("��ӭ�����ҵ�����\n");
    while(1)
    {
        printf("��ѡ��ҵ��:\n");
        printf("1.����    2.���    3.ȡ��\n");
        printf("4.��ѯ    5.ת��    6.��ʧ\n");
        printf("7.���    8.����    9.����\n");
        printf("-1.�˳�\n");
        scanf("%s",a);
        num=atoi(a);
        if(num==1)
            openaccount();//����
        else if(num==2)
            save();//���
        else if(num==3)
            withdraw();//ȡ��
        else if(num==4)
            showAccount();//��ѯ
        else if(num==5)
            transferAccounts();//ת��
        else if(num==6)
            reportLoss();  //��ʧ
        else if(num==7)
            cancelLoss();  //���
        else if(num==8)
            cancelAccount();  //ע���˻�
        else if(num==9)
            updatePassword();   //��������
        else if(num==-1)
        {
            printf("��ӭ�´�����\n");
            break;
        }
 
        else
            printf("��Ǹ��û�д�ҵ��\n");
    }
    if((fp=fopen("account.txt","w"))==NULL)
    {
        printf("ʧ�ܣ�\n");
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
    printf("�˻���ʮλ������\n");
    scanf("%s",banks[accountnum].account);
    while(banks[accountnum].account[i]!='\0')
        i++;
    if(i!=10)
    {
        printf("�����˺�����\n");
        return;
    }
    i=0;
    printf("������\n");
    scanf("%s",banks[accountnum].name);
    printf("���룺\n");
    while((ch=getch())!='\r')
    {
        banks[accountnum].password[i++]=ch;
        putchar('*');
    }
    printf("\n");
    printf("�ٴ��������룺\n");
    while((ch=getch())!='\r')
    {
        password1[j++]=ch;
        putchar('*');
    }
    printf("\n");
    r=strcmp(banks[accountnum].password,password1);
    if(r!=0)
    {
 
        printf("�������벻��ͬ������ʧ�ܣ�\n");
        return;
    }
    banks[accountnum].balance=0;
    banks[accountnum].state=0;
    accountnum++;
    printf("�����ɹ�\n");
}
void save()
{
    if(load()!=1)
        return;
    char addmoney[10];//������
    int money;//���ַ���ת��Ϊint��
    int i=0;
    printf("������:\n");
    scanf("%s",addmoney);
    while(addmoney[i]!='\0')
    {
        if(addmoney[i]<'0'||addmoney[i]>'9')
        {
            printf("�����ʽ����\n");
            return;
        }
        i++;
    }
    while(addmoney[i]!='\0')
    {
        if(i>9)
        {
            printf("����\n");
            return;
        }
        i++;
    }
    money=atoi(addmoney);
    if(money==0)
    {
        printf("���ʧ��\n");
        return;
    }
    else
    {
        banks[nowaccount].balance+=money;
        printf("���ɹ�\n");
    }
}
void withdraw()
{
    if(load()!=1)
        return;
    char reducemoney[10];//ȡ����
    int money,i=0;
    printf("������ȡ����\n");
    scanf("%s",reducemoney);
    while(reducemoney[i]!='\0')
    {
        if(reducemoney[i]<'0'||reducemoney[i]>'9')
        {
            printf("�����ʽ����\n");
            return;
        }
        i++;
    }
    while(reducemoney[i]!='\0')
    {
        if(i>9)
        {
            printf("����\n");
            return;
        }
        i++;
    }
    money=atoi(reducemoney);
    if(money==0)
    {
        printf("ȡ��ʧ��\n");
        return;
    }
    else
    {
        if(money>banks[nowaccount].balance)
            printf("�����˻�û����ô�����,ȡ��ʧ��!\n");
        else
        {
            banks[nowaccount].balance-=money;
            printf("ȡ��ɹ�\n");
        }
    }
}
void showAccount()
{
    if(load()!=1&&load()!=2)
        return;
    printf("�����˻���Ϣ���£�\n");
    printf("�˺ţ�%s\t��%d\n",banks[nowaccount].account,banks[nowaccount].balance);
}
void transferAccounts()
{
    if(load()!=1)
        return;
    char account1[20];
    int i,judge=0,money,a;
    char tramoney[10];
    printf("��������ת����˻�\n");
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
         printf("û�з��ִ��˻�\n");
         return;
     }
    printf("������ת�˽��\n");
    scanf("%s",tramoney);
    while(tramoney[i]!='\0')
    {
        if(tramoney[i]<'0'||tramoney[i]>'9')
        {
            printf("�����ʽ����\n");
            return;
        }
        i++;
    }
    while(tramoney[i]!='\0')
    {
        if(i>9)
        {
            printf("����\n");
            return;
        }
        i++;
    }
    money=atoi(tramoney);
    if(money==0)
    {
        printf("ת��ʧ��\n");
        return;
    }
    else
    {
        if(money>banks[nowaccount].balance)
            printf("�����˻�û����ô�����,ת��ʧ��!\n");
        else
        {
            banks[nowaccount].balance-=money;
            banks[a].balance+=money;
            printf("ת�˳ɹ�\n");
        }
    }
 
}
void reportLoss()
{
    if(load()!=1)
        return;
    banks[nowaccount].state=1;
    printf("��ʧ�ɹ�\n");
}
void cancelLoss()
{
    int judge=0;
    if(load()==3)
    {
        printf("��������밴1���˳��밴0\n");
        scanf("%d",&judge);
        if(judge==1)
        {
            banks[nowaccount].state=0;
            printf("��ҳɹ�\n");
        }
 
    }
    else if(load()==1)
        printf("�˻�����\n");
}
void cancelAccount()
{
    int r;
    r=load();
    if(r==2)
    {
        printf("�˻��Ѿ�����\n");
        return;
    }
    else if(r==3||r==0)
        return;
    else if(r==1)
    {
        printf("�뽫�����˻����ȡ��\n");
        banks[nowaccount].state=2;
        banks[nowaccount].balance=0;
        printf("ע���ɹ�\n");
    }
}
void updatePassword()
{
    char newpassword1[10]= {0},newpassword2[10]= {0};
    int i=0,j=0,r;
    char ch;
    if(load()!=1)
        return;
    printf("������������\n");
    while((ch=getch())!='\r')
    {
        newpassword1[i++]=ch;
        putchar('*');
    }
    printf("\n");
    printf("�ٴ��������룺\n");
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
 
        printf("�������벻��ͬ������ʧ�ܣ�\n");
        return;
    }
    i=0;
    while(newpassword1[i]!='\0')
    {
        banks[nowaccount].password[i]=newpassword1[i];
        i++;
    }
    printf("���ܳɹ�\n");
}
