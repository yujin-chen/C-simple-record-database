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
//  DATE:        October 19, 2023
//
//  FILE:        databse.h
//
//  DESCRIPTION:
//   This header file will declare the prototype of the functions: 
//   addRecord, printAllRecords, findRecord, deleteRecord, writefile
//   , readfile, and cleanup.
//
****************************************************************/

#include "record.h"

int addRecord(struct record **, int, char[], char[]);
void printAllRecords(struct record *);
int findRecord(struct record *, int);
int deleteRecord(struct record **, int);
int writefile(struct record *, char[]);
int readfile(struct record **, char[]);
void cleanup(struct record**);
