#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include<windows.h>
#include <time.h>
#include <conio.h>
#define MaxNumber 3

char accName[30];

typedef struct record
{
    char accountNum[6];
    char accName[30];
    int age;
    int initialDep;
    int month;
    int day;
    int year;
    char contactNumber[13];
    char pin[7];
} REC;

typedef struct list
{
    REC atm[MaxNumber];
    int last;
} LIST;
LIST L;

int menu();
void makeNull();
int isFull();
void addData(REC x);
int locateData(char name[30]);
int locatePosition(char name[30]);
void contactNum(char contactNum[12]);
void inputPin(char pin[7]);
void encryptPin(char pin[7]);
void saveData();
void retrieveData();
void insertCard();
void removeCard();
void inputName();

int main()
{
    system("color 3F");
    time_t now;
    time(&now);
    makeNull();
    retrieveData();
    //insertCard();
    REC sr;
    int check, accNum;
    srand(time(0));

    while(1)
    {
        switch(menu())
        {
        case 1:
            system("cls");
            if(isFull())
            {
                system("color 4F");
                system("cls");
                printf("\nThe student record is already full! \n\n");
                system("pause");
            }
            else if(!isFull())
            {
                accNum = 10000 + (rand() % 99999);
                sprintf(sr.accountNum, "%d", accNum);
                printf("\n\n\n\t\t\t\t\t\tRegistration Module\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
                printf("Please enter your name: ");
                inputName();
                strcpy(sr.accName, accName);
                check = locateData(sr.accName);
                if(check == -1)
                {
                    printf("\nPlease enter your age: ");
                    scanf("%d", &sr.age);
                    if(sr.age < 18)
                    {
                        system("color 4F");
                        system("cls");
                        printf("\nYou must be an 18 years old and above to create an account! \n\n");
                        system("pause");
                    }
                    else if(sr.age >= 18)
                    {
                        printf("\nNote: In order to register, you must deposit an amount of money that is not less than 5k.");
                        printf("\nHow much would you like to deposit?: ");
                        scanf("%d", &sr.initialDep);
                        printf("\n");
                        if(sr.initialDep >= 5000)
                        {
                            system("cls");
                            printf("\n\n\n\t\t\t\t\t\tRegistration Module\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
                            printf("Months\n");
                            printf("1. January\n");
                            printf("2. February\n");
                            printf("3. March\n");
                            printf("4. April\n");
                            printf("5. May\n");
                            printf("6. June\n");
                            printf("7. July\n");
                            printf("8. August\n");
                            printf("9. September\n");
                            printf("10. October\n");
                            printf("11. November\n");
                            printf("12. December\n");
                            printf("\nPlease enter the month of your birthday: ");
                            scanf("%d", &sr.month);
                            if(sr.month == 1 || sr.month == 3 || sr.month == 5 || sr.month == 8 || sr.month == 10 || sr.month == 12)
                            {
                                printf("\nPlease enter the day of your birthday: ");
                                scanf("%d", &sr.day);
                                if(sr.day < 1 || sr.day > 31)
                                {
                                    system("color 4F");
                                    system("cls");
                                    printf("\nThe day that you entered is invalid! \n\n");
                                    system("pause");
                                }
                                else
                                {
                                    printf("\nPlease enter the year: ");
                                    scanf("%d", &sr.year);
                                    contactNum(sr.contactNumber);
                                    inputPin(sr.pin);
                                    encryptPin(sr.pin);
                                    addData(sr);
                                    saveData();
                                }
                            }
                            else if(sr.month == 2)
                            {
                                printf("\nPlease enter the day of your birthday: ");
                                scanf("%d", &sr.day);
                                if(sr.day < 1 || sr.day > 28)
                                {
                                    system("color 4F");
                                    system("cls");
                                    printf("\nThe day that you entered is invalid! \n\n");
                                    system("pause");
                                }
                                else
                                {
                                    printf("\nPlease enter the year: ");
                                    scanf("%d", &sr.year);
                                    contactNum(sr.contactNumber);
                                    inputPin(sr.pin);
                                    encryptPin(sr.pin);
                                    addData(sr);
                                    saveData();
                                }
                            }
                            else if(sr.month == 4 || sr.month == 6 || sr.month == 9 || sr.month == 11)
                            {
                                printf("\nPlease enter the day of your birthday: ");
                                scanf("%d", &sr.day);
                                if(sr.day < 1 || sr.day > 30)
                                {
                                    system("color 4F");
                                    system("cls");
                                    printf("\nThe day that you entered is invalid! \n\n");
                                    system("pause");
                                }
                                else
                                {
                                    printf("\nPlease enter the year: ");
                                    scanf("%d", &sr.year);
                                    contactNum(sr.contactNumber);
                                    inputPin(sr.pin);
                                    encryptPin(sr.pin);
                                    addData(sr);
                                    saveData();
                                }
                            }
                            else
                            {
                                system("color 4F");
                                system("cls");
                                printf("\nInvalid input! \n\n");
                                system("pause");
                            }
                        }
                        else
                        {
                            system("color 4F");
                            system("cls");
                            printf("\nThe amount of money that you deposit is less than 5000! \n\n");
                            system("pause");
                        }
                    }
                    else{
                    system("color 4F");
                    system("cls");
                    printf("\nInvalid Input!\n");
                    system("pause");}
                }
                else
                {
                    system("color 4F");
                    system("cls");
                    printf("\n\nThe name you entered is already on our record. \n\n");
                    system("pause");
                }
            }
            break;
        case 2:
            system("cls");
            removeCard();
            exit(0);
            break;
        default:
            system("color 4F");
            system("cls");
            printf("\nInvalid input! \n\n");
            system("pause");
            break;
        }
    }
    return (0);
}

void makeNull()
{
    L.last = -1;
}

int isFull()
{
    return(L.last == MaxNumber - 1);
}

void addData(REC x)
{
    int i, p;

    if(isFull())
    {
        system("color 4F");
        printf("\nThe student record is already full! \n\n");
        system("pause");
    }
    else
    {
        p = locatePosition(x.accName);
        for (i = L.last; i >= p; i--)
        {
            L.atm[i + 1] = L.atm[i];
        }
        L.atm[p] = x;
        L.last++;
    }
}

int locateData(char name[30])
{
    for(int i = 0; i <= L.last; i++)
    {
        if(strcmp(L.atm[i].accName, name) == 0)
        {
            return (i);
        }
    }
    return (-1);
}

int locatePosition(char name[30])
{
    int i;

    for(i = 0; i <= L.last; i++)
    {
        if(strcmp(L.atm[i].accName, name) > 0)
            return (i);
    }
    return (i);
}

int menu()
{
    time_t now;
    time(&now);
    int choice;
    system("cls");
    system("color 3F");
    printf("\n\n\n\t\t\t\t\t\tMenu");
    printf("\n\t\t\t\t\t1. Registration Module\n");
    printf("\t\t\t\t\t2. Exit\n");
    printf("\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
    printf("Please select from (1-2): ");
    scanf("%d", &choice);
    return (choice);
}

void insertCard()
{
    FILE *ATMFile1;
    ATMFile1 = fopen("D:\\ATM-Data.txt", "a+");
    time_t now;
    time(&now);
    do
    {
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
    while(ATMFile1 == NULL);

    fclose(ATMFile1);
    printf("\n\n\n\t\t\t\t\tThank you for inserting your card!\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
    system("pause");
}

void removeCard()
{
    time_t now;
    time(&now);
    FILE *ATMFile1;
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

void saveData()
{
    int i;
    int p;

    //THIS IS FOR FILE IN USB.

    FILE *ATMFile1;
    ATMFile1 = fopen("D:\\ATM-Data.txt", "w+");

    if(ATMFile1 == NULL)
    {
        printf("\nThe file does not exist yet! \n");
        system("pause");
    }
    else
    {
        p = locateData(accName);
        fprintf(ATMFile1, "%s \t%s \t%d \t%d \t%d/%d/%d \t%s \t%s \n", L.atm[p].accountNum, L.atm[p].accName, L.atm[p].age, L.atm[p].initialDep, L.atm[p].month, L.atm[p].day, L.atm[p].year, L.atm[p].contactNumber, L.atm[p].pin);
    }
    fclose(ATMFile1);

    //THIS IS FOR THE FILE IN PC.

    FILE *ATMFile2;
    ATMFile2 = fopen("ATM-Data.txt", "w+");

    if(ATMFile2 == NULL)
    {
        printf("The file does not exist! \n");
        system("pause");
    }
    else
    {
        for(i = 0; i <= L.last; i++)
        {
            fprintf(ATMFile2, "%s \t%s \t%d \t%d \t%d/%d/%d \t%s \t%s \n", L.atm[i].accountNum, L.atm[i].accName, L.atm[i].age, L.atm[i].initialDep, L.atm[i].month, L.atm[i].day, L.atm[i].year, L.atm[i].contactNumber, L.atm[i].pin);
        }
    }
    fclose(ATMFile2);
}

void retrieveData()
{
    REC r;

    //THIS IS FOR FILE IN USB.

    /*FILE * ATMFile1;
    ATMFile1 = fopen("F:\\ATM-Data.txt", "r+");

    if(ATMFile1 == NULL){
        printf("The file does not exist!\n");
        system("pause");
    } else{
        while(!feof(ATMFile1)){
            fscanf(ATMFile1, "%s \t%s \t%d \t%d \t%d/%d/%d \t%s \t%s \n", r.accountNum, r.accName, &r.age, &r.initialDep, &r.month, &r.day, &r.year, r.contactNumber, r.pin);
            addData(r);
        }
    }
    fclose(ATMFile1);*/

    //THIS IS FOR THE FILE IN PC.

    FILE *ATMFile2;
    ATMFile2 = fopen("ATM-Data.txt", "r+");

    if(ATMFile2 == NULL)
    {
        system("pause");
    }
    else
    {
        while(!feof(ATMFile2))
        {
            fscanf(ATMFile2, "%s \t%s \t%d \t%d \t%d/%d/%d \t%s \t%s \n", r.accountNum, r.accName, &r.age, &r.initialDep, &r.month, &r.day, &r.year, r.contactNumber, r.pin);
            addData(r);
        }
    }
    fclose(ATMFile2);
}

void inputName()
{
    int index = 0;
    char ch;
    while((ch=getch()) != 13)
    {
        if (index<0)
        {
            index=0;
        }
        if(ch == 8 && index != 0)
        {
            putch('\b');
            putch(' ');
            putch('\b');
            index--;
            continue;
        }
        if(isalpha(ch))
        {
            accName[index++] = ch;
            putch(ch);
        }
    }
    if (index == 30)
    {
        accName[index++]=ch;
        accName[index]='\0';
    }
    //fix if counter reaches 5 automatic exit
}

void contactNum(char contactNum[13])
{
    system("cls");
    int index = 0;
    char ch;
    time_t now;
    time(&now);

    printf("\n\n\n\t\t\t\t\t\tRegistration Module\r\n\n\n\n========================================================================================================================\n \t\t\t                  %s========================================================================================================================\n",ctime(&now));
    printf("Enter your contact number: ");
    while((ch = getch()) != 13 && index != 10)
    {
        if(index < 0)
        {
            index = 0;
        }
        if(ch == 8 && index != 0)
        {
            putch('\b');
            putch(' ');
            putch('\b');
            index--;
            continue;
        }
        if(isdigit(ch))
        {
            contactNum[index++] = ch;
            putch(ch);
        }
    }
    if(index == 10)
    {
        contactNum[index++] = ch;
        contactNum[index] = '\0';
    }
    else
    {
        printf("\nThe contact number must be 11 digits! \n\n");
        system("pause");
    }
}

void inputPin(char pin[7])
{
    int index = 0;
    char ch;

    printf("\n\nEnter your desired pin code: ");
    while((ch = getch()) != 13 && index < 5)
    {
        if(index < 0)
        {
            index = 0;
        }
        if(ch == 8 && index != 0)
        {
            putch('\b');
            putch(' ');
            putch('\b');
            index--;
            continue;
        }
        if(isdigit(ch))
        {
            pin[index++] = ch;
            putch('*');
        }
    }
    if(index == 5)
    {
        pin[index++] = ch;
        pin[index] = '\0';
    }
    else if(index != 6)
    {
        printf("\nThe pin code must be 4 or 6 digits! \n\n");
        system("pause");
    }
}

void encryptPin(char pin[7])
{
    int i = 0;
    while(pin[i] != '\0')
    {
        pin[i] = pin[i] + 7;
        i++;
    }
}

void decryptPin(char pin[7])
{
    int i = 0;
    while(pin[i] != '\0')
    {
        pin[i] = pin[i] - 7;
        i++;
    }
}


