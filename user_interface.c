/*****************************************************************
//
//  NAME:        Yujin Chen
//
//  HOMEWORK:    project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 16, 2023
//
//  FILE:        user_interface.c
//
//  DESCRIPTION: 
//   This program will set up the user_interface
//   for the database. 
//
******************************************************************/

#include <stdio.h>
#include <string.h>
#include "database.h"

int debugmode = 0;
void getaddress(char[], int);

/******************************************************************
//
//  Function name: main
//
//  Description:   This function will run the 
//                 user interface.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char *[]) : An array of arguments passed
//                                   to the program.
//
//  Return values: 0: means success
//
*******************************************************************/

int main(int argc, char* argv[])
{
    struct record* start = NULL;
    char input[20];
    int end = 0;
    int result = 0;
    int accountNumber;
    int valid;
    int checkScan;
    char name[30];
    char address[50];
    char clearBuffer[80];
    int readresult;
    int writeresult;

    readresult = readfile(&start, "result.txt");
    if (readresult == 0)
    {
        printf("\nSucessfully loaded the record data from result.txt\n");
    }
    else
    {
        printf("\nUnable to load the record data from the file result.txt\n");
    }

    if (argc > 1)
    {
        if (argc > 2)
        {
            printf("\n./user_interface: Too much command entered, please only enter one command\n");
            end = 1;
        }
        else if (strcmp(argv[1], "debug") != 0)
        {
            printf("\n./user_interface: This command does not exist\n");
            end = 1;
        }
        else
        {
            debugmode = 1;
        }
    }

    while (end == 0)
    {
        printf("%4s", "\nThis is an database user-interface\n\n");
        printf("%4s", "Please choose one of the following menu option that you would like ");
        printf("to proceed by type menu option at the bottom:\n\n");
        printf("%32s",  "Menu Option   Description\n");
        printf("%10s", "add:");
        printf("%43s", "add a new record in the database\n");
        printf("%15s", "printall:");
        printf("%39s", "Print all records in the database\n");
        printf("%11s", "find:");
        printf("%51s", "Find record(s) with a specified account #\n");
        printf("%13s", "delete:");
        printf("%79s", "Delete existing record(s) from the database using the account# as a key\n");
        printf("%11s", "quit:");
        printf("%26s", "Quit the program\n");
        printf("\nPlease enter here: ");
        scanf("%s", input);

        if (strlen(input) < 4 && input[0] == 'a')
        {
            if (strcmp(input, "a") == 0 || strcmp(input, "ad") == 0 || strcmp(input, "add") == 0)
            {
                printf("\n******************************************");
                printf("**************************************\n");
                printf("\n To add a new record to the database,");
                printf(" Please follow the instruction below\n\n");
                printf("Please enter your name: ");
                fgets(clearBuffer, 80, stdin);
                fgets(name, 30, stdin);
                valid = 0;
                while (valid == 0)
                {
                    printf("\nPlease enter the account number your");
                    printf(" want to create and add to the record: ");
                    checkScan = scanf("%d", &accountNumber);

                    if (checkScan == 0)
                    {
                        fgets(clearBuffer, 80, stdin);
                        printf("\nThe input is invalid, please enter an integer\n");
                    }
                    else
                    {
                        if (accountNumber <= 0)
                        {
                            printf("\nThe account number is invalid because the number you have");
                            printf(" entered is either 0 or negative.");
                            printf(" \nPlease enter a positive number");
                        }
                        else
                        {
                            valid = 1;
                        }
                        fgets(clearBuffer, 80, stdin);
                    }
                }
                getaddress(address, 50);
                result = addRecord(&start, accountNumber, name, address);
                printf("\nThank you for your information.");
                if (result == -1)
                {
                    printf("\nThere is already a record associated with the account number");
                    printf(". The record will not be added\n");
                }
                else
                {
                    printf("Your information will be added into the database.\n");
                }
                printf("\n******************************************");
                printf("**************************************\n");
            }
            else
            {
                printf("\ninvalid option, please enter an valid option from menu option\n");
            }
        }
        else if (strlen(input) < 5 && input[0] == 'q')
        {
            if (strcmp(input, "q") == 0 || strcmp(input, "qu") == 0 ||\
                strcmp(input, "qui") == 0 || strcmp(input, "quit") == 0)
            {
                printf("\n******************************************");
                printf("**************************************\n");
                writeresult = writefile(start, "result.txt");
                if (writeresult == -1)
                {
                    printf("\nUnable to write the record data into the file result.txt\n");
                }
                else
                {
                    printf("\nSuccessfully written the record data into the file result.txt\n");
                }
                cleanup(&start);
                end = 1;
                printf("\nThank you for using the program,");
                printf(" Your session will now be terminated\n\n");
                printf("\n*********************************************");
                printf("***********************************\n");
            }
            else
            {
                printf("\ninvalid option, please enter an valid option from menu option\n");
            }
        }
        else if (strlen(input) < 5 && input[0] == 'f')
        {
            if (strcmp(input, "f") == 0 || strcmp(input, "fi") == 0 ||\
                strcmp(input, "fin") == 0 || strcmp(input, "find") == 0)
            {
                printf("\n****************************************");
                printf("****************************************\n");
                printf("\nTo find your record, please following the instruction below\n");
                valid = 0;
                while (valid == 0)
                {
                    printf("\nPlease enter the account number that is associated");
                    printf(" with the record you want to find: ");
                    checkScan = scanf("%d", &accountNumber);

                    if (checkScan == 0)
                    {
                        fgets(clearBuffer, 80, stdin);
                        printf("\nThe input is invalid, please enter an integer\n");
                    }
                    else
                    {
                        if (accountNumber <= 0)
                        {
                            printf("\nThe account number is invalid because the number you have");
                            printf(" entered is either 0 or negative.");
                            printf(" \nPlease enter a positive number");
                        }
                        else
                        {
                            valid = 1;
                        }
                        fgets(clearBuffer, 80, stdin);
                    }
                }
                printf("\nThank you for enter your account number\n");
                result =  findRecord(start, accountNumber);
                if (result == 0)
                {
                    printf("\nThe record is found, printed above\n");
                }
                else
                {
                    printf("\nRecord not found, no record is associated");
                    printf(" with account number entered\n");
                }
                printf("\n********************************************");
                printf("************************************\n");
            }
            else
            {
                printf("\ninvalid option, please enter an valid option from menu option\n");
            }
        }
        else if (strlen(input) < 7 && input[0] == 'd')
        {
            if (strcmp(input, "d") == 0 || strcmp(input, "de") == 0 || strcmp(input, "del") == 0 ||\
                strcmp(input, "dele") == 0 || strcmp(input, "delet") == 0\
                || strcmp(input, "delete") == 0)
            {
                printf("\n**************************************");
                printf("******************************************\n");
                printf("\nTo delete a record, please follow the instruction below\n\n");
                valid = 0;
                while (valid == 0)
                {
                    printf("Please enter your account number that wants to be deleted: ");
                    checkScan = scanf("%d", &accountNumber);
                    if (checkScan == 0)
                    {
                        fgets(clearBuffer, 80, stdin);
                        printf("\nThe input is invalid, please enter an integer\n");
                    }
                    else
                    {
                        if (accountNumber <= 0)
                        {
                            printf("\nThe account number is invalid because the number you have");
                            printf(" entered is either 0 or negative.");
                            printf(" \nPlease enter a positive number\n");
                        }
                        else
                        {
                            valid = 1;
                        }
                        fgets(clearBuffer, 80, stdin);
                    }
                }
                result = deleteRecord(&start, accountNumber);
                printf("\nThank you for entering your account number\n");
                if (result == 0)
                {
                    printf("\nRecord found, we will delete the record");
                    printf(" associated with this account number\n");
                }
                else
                {
                    printf("\nNo record deleted because the account does not exist\n");
                }
                printf("\n*************************************");
                printf("*******************************************\n");
            }
            else
            {
                printf("\ninvalid option, please enter an valid option from menu option\n");
            }
        }
        else if (strlen(input) < 9 && input[0] == 'p')
        {
            if (strcmp(input, "p") == 0 || strcmp(input, "pr") == 0 ||\
                strcmp(input, "pri") == 0 ||\
                strcmp(input, "prin") == 0 || strcmp(input, "print") == 0 ||\
                strcmp(input, "printa") == 0\
                || strcmp(input, "printal") == 0 || strcmp(input, "printall") == 0)
            {
                printf("\n*********************************************");
                printf("***********************************\n");
                printf("\nThe records will be printed\n\n");
                printAllRecords(start);
                printf("\n*********************************************");
                printf("***********************************\n");
            }
            else
            {
                printf("\ninvalid option, please enter an valid option from menu option\n");
            }
        }
        else
        {
            printf("\ninvalid option, please enter an valid option from menu option\n");
        }
    }
    return 0;
}

/******************************************************************
//
//  Function name: getAddress
//
//  Description:   This function will get customer's address
//
//  Parameters:    address (char []): Where the address will be
//                                    stored.
//                 accountNumber (int): account number the address
//                                      will be associated to.
//
//  Return values: none
//
*******************************************************************/

void getaddress(char address[], int size)
{
    int i = 0;
    char c;
    int read = 1;
    char clearBuffer [80];

    printf("\nPlease enter your address below and type dollar sign '$' end of your address: \n");
    while (read == 1)
    {
        if ( i != size - 1)
        {
            c = fgetc(stdin);
            if ( c == '$')
            {
                read = 0;
            }
            else
            {
                address[i] = c;
                i++;
            }
        }
        else
        {
            read = 0;
            fgets(clearBuffer, 80, stdin);
        }
    }
    address[i] = '\0';
    if (debugmode == 1)
    {
        printf("\n-----------------------------------------\n");
        printf("Output from debug mode: \n");
        printf("Function Name:  getAddress\n");
        printf("Address: \n%s", address);
        printf("\n-----------------------------------------\n");
    }
}
