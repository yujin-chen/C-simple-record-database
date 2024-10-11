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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This header is to create data variable and variable type.
//
****************************************************************/

struct record
{
    int             accountno;
    char            name[30];
    char            address[50];
    struct record*  next;
};
