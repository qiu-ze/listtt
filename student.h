//
// Created by armstrong on 24-7-10.
//

#ifndef STUDENT_H
#define STUDENT_H
#define M 3
#include <stdbool.h>
typedef struct Student {
    char num[15];
    char name[15];
    char major[10];
    int classNo;
    int score[M];
    struct Student *next;
    struct Student *prev;
}STU;

typedef enum {
    STATE_START_2_0,
    STATE_2_1,
    STATE_2_2,
    STATE_0,
    STATE_2_3,
    STATE_X,
    STATE_VALID,
    STATE_INVALID
} State;

STU *head = NULL;
STU *tail = NULL;

void print_Menu();
void Exit();
void append_Record();
void list_Record();
void delete_Record();
void modify_Record();
void search_Record();
void sort_Score_In_Descending_Order_By_Sum();
void sort_Score_In_Ascending_Order_By_Sum();
void sort_Score_In_Descending_Order_By_Num();
void sort_Score_In_Ascending_Order_By_Num();
void write_To_File();
void read_From_A_File();
void read_All_From_File();
void read_One_From_File();
void Insert();
bool validateInput(const char *input);

#endif //STUDENT_H
