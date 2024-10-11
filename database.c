/********************************************************************************
//
//  NAME:        Yujin Chen
//
//  HOMEWORK:    project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 18,2023
//
//  FILE:        database.c
//
//  DESCRIPTION: 
//   This program will implement functions
//   functions: addRecord, printAllRecords,
//   findRecord, deleteRecord, writefile,
//   readfile, and cleanup.
//
********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

extern int debugmode;

/*******************************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Will add record to data base and collect
//                 customer's name, address, account number.
//
//  Parameters:    record1 (struct record **): poiner to pointer of first record
//                 accountNumber (int): customer's account number.
//                 name (char []) : name of customer.
//                 address (char []) : customer's address.
//
//  Return values: -1: means that the account is already existed. The record can't be
//                     added.
//                  0: means the record is sucessfully added.
//
*******************************************************************************/

int addRecord(struct record ** record1, int accountNumber, char name[], char address[])
{
    int exist = 0;
    int stop = 0;
    struct record* start = *record1;
    struct record* temp;
    struct record* current;
    struct record* after;
    current = start;
    if (debugmode == 1)
    {
        printf("\n-----------------------------------------\n");
        printf("\nOutput from debug mode: \n");
        printf("%s", "Function name: addRecord\n");
        printf("%s", "Name: ");
        printf("%s", name);
        printf("%s", "Account Number: ");
        printf("%d\n", accountNumber);
        printf("%s", "Address: \n");
        printf("%s\n", address);
        printf("\n-----------------------------------------\n");
    }

    if (start != NULL)
    {
        while (current -> next != NULL)
        {
            if (current -> accountno == accountNumber)
            {
                exist = -1;
                stop = 1;
            }
            current = current -> next;
        }
        if (current -> accountno == accountNumber)
        {
            exist = -1;
        }
        current = start;
    }

    if (exist == 0)
    {
        temp = (struct record*)malloc(sizeof(struct record));
        temp -> accountno = accountNumber;
        strcpy(temp -> name, name);
        strcpy(temp -> address, address);
        temp -> next = NULL;

        if (start == NULL)
        {
            *record1 = temp;
            stop = 1;
        }

        while (stop == 0)
        {
            if (accountNumber > start -> accountno)
            {
                temp -> next = start;
                *record1 = temp;
                stop = 1;
            }
            else if (current -> next == NULL && accountNumber < current -> accountno)
            {
                temp -> next = current -> next;
                current -> next = temp;
                stop = 1;
            }
            else
            {
                after = current -> next;
                if (after != NULL && accountNumber > after -> accountno)
                {
                    temp -> next = current -> next;
                    current -> next = temp;
                    stop = 1;
                }
                else
                {
                    current = current -> next;
                }
            }
        }
    }
    return exist;
}

/*******************************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Will print all records in the data base
//
//  Parameters:    record1 (struct record *): pointer to the first record in heap.
//
//  Return values: none
//
*******************************************************************************/

void printAllRecords(struct record * record1)
{
    struct record* current = record1;
    if (debugmode == 1)
    {
        printf("\n-----------------------------------------\n");
        printf("\nOutput from debug mode: \n");
        printf("Function name: printAllRecords\n");
        printf("\n-----------------------------------------\n");
    }
    if (record1  == NULL)
    {
        printf("There are no record in the database");
    }
    else
    {
        while (current != NULL)
        {
            printf("\n--------------------------------------------\n");
            printf("Account Number: %d\n", current -> accountno);
            printf("Name: %s\n", current -> name);
            printf("Address:\n%s\n\n", current -> address);
            printf("\n--------------------------------------------\n");
            current = current -> next;
        }
    }
}

/*******************************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Will find the record  associated with the 
//                 customer's account number
//
//  Parameters:    record1(struct record *): pointer to the first record in heap.
//                 accountNumber (int): customer's account number
//
//  Return values: 0: means sucessfully find the record
//                 -1: Did not found the record.
//
*******************************************************************************/

int findRecord(struct record * record1, int accountNumber)
{
    int exist = -1;
    struct record* current = record1;
    if (debugmode == 1)
    {
        printf("\n-----------------------------------------\n");
        printf("\nOutput from debug mode: \n");
        printf("Function name: findRecord\n");
        printf("Account Number: ");
        printf("%d\n", accountNumber);
        printf("\n-----------------------------------------\n");
    }
    while (current != NULL)
    {
        if (current -> accountno == accountNumber)
        {
            printf("\n--------------------------------------------\n");
            printf("Account Number: %d\n", current -> accountno);
            printf("Name: %s\n", current -> name);
            printf("Address:\n%s\n\n", current -> address);
            printf("\n--------------------------------------------\n");
            exist = 0;
        }
        current = current -> next;
    }
    return exist;
}

/******************************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Will delete record that is associated the account number
//
//  Parameters:    record2 (struct record **): a pointer to pointer of record
//                 accountNumber (int): customer's account number.
//
//  Return values: -1: means the record does not exist and can't be deleted.
//                  0: means that the record is successfully deleted
//
*******************************************************************************/

int deleteRecord(struct record ** record2, int accountNumber)
{
    int exist = -1;
    struct record* current;
    struct record* after;
    struct record* beforeExistLocation;

    if (debugmode == 1)
    {
        printf("\n-----------------------------------------\n");
        printf("Output from debug mode: \n ");
        printf("Function name: deleteRecord\n");
        printf("Account Number: ");
        printf("%d\n", accountNumber);
        printf("\n-----------------------------------------\n");
    }
    if (*record2 == NULL)
    {
        exist = -1;
    }
    else
    {
        current = *record2;
        after = current -> next;
        if (current -> accountno == accountNumber)
        {
            *record2  = after;
            free(current);
            exist = 0;
        }
        else
        {
            while (after != NULL)
            {
                if (after -> accountno == accountNumber)
                {
                    exist = 0;
                    beforeExistLocation = current;
                    current = current -> next;
                    after = current -> next;
                    beforeExistLocation -> next = after;
                    free(current);
                }
                if (after != NULL)
                {
                    current = current -> next;
                    after = current -> next;
                }
            }
        }
    }
    return exist;
}

/******************************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Will write the record data into the designated text file.
//
//  Parameters:    record2 (struct record *): a pointer that points to the first
//                                             record in heap.
//                 filename (char []): The textfile you wanted to be written on.
//
//  Return values: 0: means success
//
*******************************************************************************/

int writefile(struct record* record2, char filename[])
{
    FILE *text;
    struct record* current = record2;
    int exist = -1;
    if (debugmode == 1)
    {
        printf("\n-----------------------------------------\n");
        printf("\nOutput from debug mode: \n");
        printf("Function name: writefile\n");
        printf("File Name: %s", filename);
        printf("\n-----------------------------------------\n");
    }
    text = fopen(filename, "w");
    if (text == NULL)
    {
        exist = -1;
    }
    else
    {
        exist = 0;
        while (current != NULL)
        {
            fprintf(text, "%d\n", current -> accountno);
            fprintf(text, "%s", current -> name);
            fprintf(text, "%s", current -> address);
            fprintf(text, "$\n");
            current = current -> next;
        }
        fclose(text);
    }
    return exist;
}

/******************************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Will read the record datas saved in the textfile and add it
//                 to the heap.
//
//  Parameters:    record1 (struct record **): a pointer to pointer that point
//                                              to the first record.
//                 filename (char[]): The name of the file you wanted to be read.
//
//  Return values: 0: means the file exist.
//                 -1: means the file can't be opened.
//
*******************************************************************************/

int readfile(struct record** record1, char filename[])
{
    int i = 0;
    char character;
    int read = 1;
    int exist = 0;
    int moreRecord = 1;
    int accountNumber;
    char name[30];
    char address[50];
    char clearBuffer[80];
    struct record* current;
    struct record* before;
    FILE* text;
    if (debugmode == 1)
    {
        printf("\n-----------------------------------------\n");
        printf("\nOutput from debug mode: \n");
        printf("Function name: readfile\n");
        printf("File Name: %s", filename);
        printf("\n-----------------------------------------\n");
    }

    text = fopen(filename, "r");
    if (text == NULL)
    {
        exist = -1;
    }
    else
    {
        while (moreRecord == 1)
        {
            moreRecord = fscanf(text, "%d", &accountNumber);
            if (moreRecord == 1)
            {
                fgets(clearBuffer, 80, text);
                fgets(name, 30, text);
                while (read == 1)
                {
                    character = fgetc(text);
                    if (character == '$')
                    {
                        read = 0;
                    }
                    else
                    {
                        address[i] = character;
                        i++;
                    }
                }
                address[i] = '\0';
                i = 0;
                read = 1;
                if (*record1 == NULL)
                {
                    current = (struct record*)malloc(sizeof(struct record));
                    *record1 = current;
                    current -> accountno = accountNumber;
                    strcpy(current -> name, name);
                    strcpy(current -> address, address);
                    current -> next = NULL;
                }
                else
                {
                    before = current;
                    current = (struct record*)malloc(sizeof(struct record));
                    before -> next = current;
                    current -> accountno = accountNumber;
                    strcpy(current -> name, name);
                    strcpy(current -> address, address);
                    current -> next = NULL;
                }
            }
        }
        fclose(text);
    }
    return exist;
}

/******************************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Will release all the allocated spaces in the heap and assign
//                 Null to start.
//
//  Parameters:    record1 (struct record **): a pointer to a pointer that point
//                                              to the first record.
//
//  Return values: Does not have a return value;
//
*******************************************************************************/

void cleanup(struct record** record1)
{
    struct record* current;
    struct record* next;
    if (debugmode == 1)
    {
        printf("\n-----------------------------------------\n");
        printf("\nOutput from debug mode: \n");
        printf("Function name: cleanup\n");
        printf("\n-----------------------------------------\n");
    }
    if (*record1 != NULL)
    {
        current = *record1;
        next = current  -> next;
        while (next != NULL)
        {
            free(current);
            current = next;
            next = next -> next;
        }
        free(current);
        *record1 = NULL;
    }
}
