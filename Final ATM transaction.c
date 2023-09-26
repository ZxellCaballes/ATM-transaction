#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include<windows.h>
#include <time.h>
#define MAX 5

//data from and to usb
char retrievedPin[7];
char accName[31];
char bday[10];
int age;
int accNo;
char contactNum[12];
int initialDeposit;
int pinCode;


typedef struct
{
    char PIN[6];
} userInfo;
userInfo UI;

typedef struct record
{
    char accName[31];
    char bday[10];
    int age;
    int accNo;
    char contactNum[12];
    int initialDeposit;
    int pinCode;
    char retrievedPin[7];
} REC;

typedef struct list
{
    REC sr[MAX];
    int last;
} LIST;
LIST L;

char WithdrawAmt[10];
int locate(char n[31]);
int locPosition(char n[31]);
int isempty();
int isfull();
int menu();
void update(char n[31]);
void insertcard();
void inputPin();
void inputValidator();
void withdrawFunc();
void depositFunc();
void fundTrans();
void makenull();
void add(REC x);
void save();
void retrieve();
void changePinCode();
void removeCard();
void encryptPin();
void decryptPin();

int main()
{
    system("color 3F");
    makenull();
    retrieve();
    insertcard();
    inputPin();
    while(1)
    {
        system("color 3F");
        time_t now;
        time(&now);
        switch(menu())
        {
        case 1:
            system("cls");
            printf("\n\t\t\t\t\t========Balance Inquiry========\n\n");
            printf("\t\t\t\t\tYour Current Balance is %d\n", initialDeposit);
            printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
            system("pause");
            break;
        case 2:
            system("cls");
            withdrawFunc();
            break;
        case 3:
            system("cls");
            depositFunc();
            break;
        case 4:
            system("cls");
            printf("\n\t\t\t\tFund Transfer (for enrolled accounts only)\n\n");
            if(initialDeposit!=0)
            {
                fundTrans();
            }
            else
            {
                printf("Insufficient Funds\n");
            }
            system("pause");
            break;
        case 5:
            system("cls");
            changePinCode();
            break;
        case 6:
            system("cls");
            save();
            removeCard();
            exit(0);
            break;
        default:
            system("cls");
            system("color 4F");
            printf("\nInvalid input! \n\n");
            system("pause");
            break;

        }
    }


}
int locPosition(char n[31])
{
    int i;
    for (i=0; i<=L.last; i++)
    {
        if (strcmp(L.sr[i].accName,n)>0)
            return (i);
    }
    return (i);
}
void makenull()
{
    L.last = -1;
}
void add(REC x)
{
    int i,p;
    if (isfull())
    {
        system("color 4F");
        printf("List is full.\n");
        system("pause");
    }
    else
    {
        p=locPosition(x.accName);
        for (i=L.last; i>=p; i--)
        {
            L.sr[i+1]=L.sr[i];
        }

        L.sr[p] = x;

        L.last++;
    }
}

int locate(char n[31])
{
    int i;
    for (i=0; i<=L.last; i++)
        if (strcmp(L.sr[i].accName,n)==0)
            return(i);
    return(-1);
}
int isempty()
{
    return(L.last==-1);
}
int isfull()
{
    return(L.last==MAX-1);
}
int menu()
{
    int ch;
    time_t now;
    time(&now);
    system("cls");
    printf("\n\n\n\t\t\t\t\t\tMenu\n");
    printf("\n\t\t\t\t\t1. Balance Inquiry\n");
    printf("\n\t\t\t\t\t2. Withdraw\n");
    printf("\n\t\t\t\t\t3. Deposit\n");
    printf("\n\t\t\t\t\t4. Fund Transfer (for enrolled accounts only)\n");
    printf("\n\t\t\t\t\t5. Change PIN Code\n");
    printf("\n\t\t\t\t\t6. Exit\n");
    printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
    printf("Select (1-6): ");
    scanf("%d",&ch);
    return(ch);

}
void save()
{
    // writes the updated info unto the usb
    int p;
    FILE*usbFile;
    usbFile = fopen("D:\\ATM-Data.txt","w+");
    p=locate(accName);
    L.sr[p].accNo= accNo;
    L.sr[p].initialDeposit= initialDeposit;
    strcpy(L.sr[p].retrievedPin, retrievedPin);
    fprintf( usbFile,"%d \t%s \t%d \t%d \t%s \t%s \t%s \n", accNo, accName, age, initialDeposit,bday, contactNum, retrievedPin);

    fclose(usbFile);

    //writes the updated info unto the database
    FILE *fp;
    int i;
    fp = fopen("ATM-Data.txt","w+");
    if (fp==NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        for (i=0; i<=L.last; i++){
            fprintf(fp,"%d \t%s \t%d \t%d \t%s \t%s \t%s \n",L.sr[i].accNo,L.sr[i].accName,L.sr[i].age,L.sr[i].initialDeposit,L.sr[i].bday,L.sr[i].contactNum,L.sr[i].retrievedPin);
        }
    }
    fclose(fp);
}
void retrieve()
{
    FILE *fp;
    REC r;
    fp = fopen("ATM-Data.txt","r+");
    if (fp==NULL)
    {
        system("color 4F");
        printf("File error.\n");
        system("pause");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp,"%d \t%s \t%d \t%d \t%s \t%s \t%s\n",&r.accNo,r.accName,&r.age,&r.initialDeposit,r.bday,r.contactNum,&r.retrievedPin);
            add(r);
        }
        fclose(fp);
    }
}

void insertcard()
{
    FILE *fp;
    time_t now;
    time(&now);
    do
    {
        fp = fopen("D:\\ATM-Data.txt","r+");

    system("cls");
    printf("\n\n\nInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\t\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\t\t\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tInsert Card Here\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");
    }
    while(fp==NULL);

    while (!feof(fp))
    {

        fscanf(fp, "%d \t%s \t%d \t%d \t%s \t%s \t%s \n", &accNo, accName, &age, &initialDeposit, bday, contactNum, retrievedPin);
        decryptPin();
        pinCode = atoi(retrievedPin);
        printf("\n\n\n\t\t\t\t\tThank you for inserting your card %s\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",accName,ctime(&now));
        printf( "%d \t%s \t%d \t%d \t%s \t%s \t%s \n", accNo, accName, age, initialDeposit, bday, contactNum, retrievedPin);
        system("pause");
    }
    fclose(fp);
}
void inputPin()
{
    FILE *fp;
    int value;
    time_t now;
    time(&now);
    do
    {
        fp = fopen("D:\\ATM-Data.txt","r+");
        system("cls");
        printf("\n\n\n\t\t\t\t\tThank you for inserting your card %s\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",accName,ctime(&now));
        printf("Enter Your Pin:");
        int index =0;
        char ch;
        while((ch=getch())!=13 && index<5)
        {
            if (index<0)
                index=0;

            if(ch==8 && index != 0)
            {
                putch('\b');
                putch(' ');
                putch('\b');
                index--;
                continue;
            }
            if(isdigit(ch))
            {
                UI.PIN[index++]=ch;
                putch('*');
            }
        }
        if (index==5)
        {
            UI.PIN[index++]=ch;
            UI.PIN[index]='\0';
        }
        value = atoi(UI.PIN);
        system("cls");
        printf("\n");
    }
    while(value!=pinCode);
}
void inputValidator()
{
    memset(WithdrawAmt, 0, 10);
    int index =0;
    char ch;
    while((ch=getch())!=13 && index!=6)
    {
        if (index<0)
            index=0;
        if(ch==8)
        {
            putch('\b');
            putch(' ');
            putch('\b');
            index--;
            continue;
        }
        if(isdigit(ch))
        {
            WithdrawAmt[index++]=ch;
            putch(ch);
        }
    }
    if (index==6)
    {
        WithdrawAmt[index++]=ch;
        WithdrawAmt[index]='\0';
    }

}

void withdrawFunc()
{
    int withdraw;
    time_t now;
    time(&now);
    do
    {   printf("\n\t\t\t\t\t===========Withdraw===========\n\n");
        printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
        printf("\nEnter withdraw amount:");
        inputValidator();
        withdraw = atoi(WithdrawAmt);

    }
    while(withdraw>initialDeposit);
    initialDeposit-=withdraw;
    system("cls");
    printf("\n\t\t\t\t\t===========Withdraw===========\n\n");
    printf("\n\n\t\t\t\t\t\tYou have successfully withdrawed %d",withdraw);
    printf("\n\n\t\t\t\t\t\tYour current balance is %d\n", initialDeposit);
    printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
    system("pause");


}

void depositFunc()
{
    int deposit;
    time_t now;
    time(&now);
    do
    {
        printf("\n\t\t\t\t\t===========Deposit===========\n\n");
        printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
        printf("\nEnter Deposit:");
        inputValidator();
        deposit = atoi(WithdrawAmt);
        if(deposit>500000)
        {

            break;
        }
    }
    while(deposit>500000);
    if(deposit<500000)
    {
        initialDeposit+=deposit;
    }
    else
    {
        initialDeposit+=0;
    }
    system("cls");
    printf("\n\t\t\t\t\t\t===========Deposit===========\n\n");
    printf("\n\t\t\t\t You have deposited %d",deposit);
    printf("\n\n\t\t\t\t Your Current Balance is now %d\n", initialDeposit);
    printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
    system("pause");



}

void fundTrans()
{
    int funds;
    int p;
    char receiver[30];
    int transAmt;
    int receiverBalance = 0;
    time_t now;
    time(&now);
    do
    {
        system("cls");
        printf("\n\t==========Fund Transfer (for enrolled accounts only)==========\n\n");
        printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
        printf("\nEnter receiver's name:");
        scanf("%s",receiver);
        p=locate(receiver);
        if (p==-1)
        {
            system("color 4F");
            printf("Not found.\n");
            system("pause");
        }
        else
        {
            printf("Enter amount to transfer:");
            inputValidator();
            transAmt=atoi(WithdrawAmt);
        }


    }
    while(transAmt>initialDeposit && transAmt == initialDeposit );

    initialDeposit-=transAmt;
    receiverBalance=L.sr[p].initialDeposit;
    receiverBalance+=transAmt;
    L.sr[p].initialDeposit=receiverBalance;
    system("cls");
    printf("\n\t==========Fund Transfer (for enrolled accounts only)==========\n\n");
    printf( "\n\n\t\t\t\t%d \t%s \t%d \t%d \n", accNo, accName, age, initialDeposit);
    printf( "\n\t\t\t\t%d \t%s \t%d \t%d \n", L.sr[p].accNo, L.sr[p].accName, L.sr[p].age, L.sr[p].initialDeposit);
    printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));

}

void changePinCode()
{
    int changePin;
    int confirmPin;
    time_t now;
    time(&now);
    do
    {
        int index =0;
        int indexs =0;
        char ch;
        char chs;

        printf("\n\t\t\t\t\t=========Change PIN Code=========\n");
        printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
        printf("Enter PIN code:");

        while((ch=getch())!=13 && index<5)
        {
            if (index<0)
                index=0;
            if(ch==8&& index != 0)
            {
                putch('\b');
                putch(' ');
                putch('\b');
                index--;
                continue;
            }
            if(isdigit(ch))
            {
                UI.PIN[index++]=ch;
                putch(ch);
            }
        }
        if (index==5)
        {
            UI.PIN[index++]=ch;
            UI.PIN[index]='\0';
        }
        changePin = atoi(UI.PIN);
        printf("\n%d\n",changePin);

        printf("\nConfirm PIN code:");
        while((chs=getch())!=13 && indexs<5)
        {
            if (indexs<0)
                indexs=0;
            if(chs==8&& index != 0)
            {
                putch('\b');
                putch(' ');
                putch('\b');
                indexs--;
                continue;
            }
            if(isdigit(chs))
            {
                UI.PIN[indexs++]=chs;
                putch(chs);
            }
        }
        if (indexs==5)
        {
            UI.PIN[indexs++]=chs;
            UI.PIN[indexs]='\0';
        }
        confirmPin = atoi(UI.PIN);
        printf("\n%d\n",confirmPin);

        if (confirmPin != changePin)
        {
            system("color 4F");
            printf("\nwrong pin entered try again\n");
            system("Pause");
        }
        system("cls");
    }
    while (confirmPin!= changePin);
    //pincode is int to string which is retrievedPin
    sprintf(retrievedPin, "%d", confirmPin);
    encryptPin();
    printf("\n\t\t\t\t\t=========Change PIN Code=========\n");
    printf("\n\t\t\t\t\t\tChange Successful\n");
    printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
    system("Pause");


}

void removeCard()
{
    time_t now;
    time(&now);
    FILE *ATMFile1;
    system("color 4F");
    do
    {
            system("cls");

    printf("\n\nRemove Card \r\n\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\nRemove Card \r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\t\tRemove Card \r\n\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\tRemove Card\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\t\t\t\tRemove Card\r\n\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\tRemove Card\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\t\t\t\t\tRemove Card\r\n\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\tRemove Card\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\t\t\t\t\t\t\tRemove Card\r\n\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\t\t\tRemove Card\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\t\t\t\t\t\t\t\t\tRemove Card\r\n\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\t\t\t\t\tRemove Card\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\t\t\t\t\t\t\t\t\t\t\tRemove Card\r\n\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");

    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tRemove Card\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================",ctime(&now));
    Sleep(100);
    system("cls");
        ATMFile1 = fopen("D:\\ATM-Data.txt", "r");
    }
    while(ATMFile1 != NULL);

    fclose(ATMFile1);

    printf("\nThank you for banking with us! \n");
}


void encryptPin()
{
    int i = 0;
    while(retrievedPin[i] != '\0')
    {
        retrievedPin[i] = retrievedPin[i] + 7;
        i++;
    }
}

void decryptPin()
{
    int i = 0;
    while(retrievedPin[i] != '\0')
    {
        retrievedPin[i] = retrievedPin[i] - 7;
        i++;
    }
}
