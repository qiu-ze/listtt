#include <stdio.h>
#include "student.h"
#include <windows.h>

void free_memory() {
    STU* current = head;
    while (current != NULL) {
        STU *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

void Exit() {
    free_memory();
    printf("退出程序\n");
    printf("谢谢您的使用\n");
    exit(0);
}



void append_Record() {

STU* new_student = (STU*)malloc(sizeof(STU));

    if (new_student == NULL) {
        printf("内存分配失败");
        return;
    }

    printf("输入学号: ");
    scanf("%s", new_student->num);
    printf("输入姓名: ");
    scanf("%s",new_student->name );
    printf("输入专业: ");
    scanf("%s", new_student->major);
    printf("输入班级: ");
    scanf("%d", &new_student->classNo);
    for (int j = 0; j < M; j++) {
        printf("输入第%d门课程成绩: ", j + 1);
        scanf("%d", &new_student ->score[j]);
    }

    new_student->next = NULL;

    if (head == NULL) {
        new_student->prev = NULL;
        head = new_student;
        tail = new_student;
    }
    else {
        new_student->prev = tail;
        tail->next = new_student;
        tail = new_student;
    }
}

void list_Record() {
    STU* current = head;

    if (current == NULL) {
        printf("无学生数据可查\n");
    }
    else {
        while (current != NULL) {
            printf("学号: %s\n", current->num);
            printf("  姓名: %s\n",current->name );
            printf("  专业: %s\n",current->major);
            printf("  班级: %d\n",current->classNo);
            for (int j = 0; j < M; j++) {
                printf("  第%d门课程成绩: %d\n", j + 1, current->score[j]);
            }
            current = current->next;
        }
    }
}

void delete_Record(){
    STU* current = head;
    STU* previous = NULL;
    
    char searchNumName[15];
    printf("请输入要删除的学生学号或姓名: ");
    scanf("%s",searchNumName);

    if(current = NULL){
        printf("无学生数据可以删除\n");
        return;
    }

    while (current != NULL) {
        if (strcmp(searchNumName, current->num) == 0 || strcmp(searchNumName, current->name) == 0) {
            if (previous == NULL) {  // 如果删除的是头节点
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("学生记录已删除\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("未找到匹配的学生记录\n");
}

void modify_Record(){
    STU* current = head;

    if(current = NULL){
        printf("无学生数据可以修改\n");
        return;
    }

    char searchNumName[15];
    printf("请输入要修改的学生学号或姓名: ");
    scanf("%s",searchNumName);

     while (current != NULL) {
        if (strcmp(searchNumName, current->num) == 0 || strcmp(searchNumName, current->name) == 0) {
            printf("输入修改后学号: ");
            scanf("%s", current->num);
            printf("输入修改后姓名: ");
            scanf("%s",current->name );
            printf("输入修改后专业: ");
            scanf("%s", current->major);
            printf("输入修改后班级: ");
            scanf("%d", &current->classNo);
            for (int j = 0; j < M; j++) {
                printf("输入修改后第%d门课程成绩: ", j + 1);
                scanf("%d", &current ->score[j]);
            }
        printf("修改成功\n");
        return;
        }
        current = current->next;
    }

    printf("没有找到学号或姓名为 %s 的学生信息。\n", searchNumName);
}

void search_Record(){
    
    STU* current = head;

    if(current = NULL){
        printf("无学生数据可以查找\n");
        return;
    }

    char searchNumName[15];
    printf("请输入要查找的学生学号或姓名: ");
    scanf("%s",searchNumName);

    while (current != NULL) {
        if(strcmp(searchNumName, current->num) == 0 || strcmp(searchNumName, current->name) == 0){
            printf("学号: %s\n", current->num);
            printf("  姓名: %s\n",current->name );
            printf("  专业: %s\n",current->major);
            printf("  班级: %d\n",current->classNo);
            for (int j = 0; j < M; j++) {
                printf("  第%d门课程成绩: %d\n", j + 1, current->score[j]);
            }
            return;
        }
        current = current->next;
    }
    printf("没有找到学号或姓名为 %s 的学生信息。\n", searchNumName);
}

int CalculateTotalScore(STU* current) {
    int total = 0;
    for (int i = 0; i < M; i++) {
        total += current->score[i];
    }
    return total;
}

void swap_nodes(STU* node1, STU* node2) {
    if (node1 == NULL || node2 == NULL) {
        return;
    }

    if (node1->next == node2) {
        STU* prev_node1 = node1->prev;
        STU* next_node2 = node2->next;

        if (prev_node1 != NULL) {
            prev_node1->next = node2;
        }
        node2->prev = prev_node1;
        node2->next = node1;
        node1->prev = node2;
        node1->next = next_node2;
        if (next_node2 != NULL) {
            next_node2->prev = node1;
        }
    } else if (node2->next == node1) {
        swap_nodes(node2, node1);
    } else {
        STU* temp_prev1 = node1->prev;
        STU* temp_next1 = node1->next;
        STU* temp_prev2 = node2->prev;
        STU* temp_next2 = node2->next;

        if (temp_prev1 != NULL) {
            temp_prev1->next = node2;
        }
        if (temp_next1 != NULL) {
            temp_next1->prev = node2;
        }
        node1->prev = temp_prev2;
        node1->next = temp_next2;

        if (temp_prev2 != NULL) {
            temp_prev2->next = node1;
        }
        if (temp_next2 != NULL) {
            temp_next2->prev = node1;
        }
        node2->prev = temp_prev1;
        node2->next = temp_next1;
    }
}

void sort_Score_In_Descending_Order_By_Sum(){
    STU* current = head;
    if(current == NULL||current->next == NULL){
        printf("学生记录不足以排序。\n");
        return;
    }


    int swapped;

    do {
        swapped = 0;
        current = head;
        
        while (current->next != NULL) {
            if (CalculateTotalScore(current) < CalculateTotalScore(current->next)) {
                swap_nodes(current,current->next);
                swapped = 1;    
            } else {
                current = current->next;
            }
        }
    } while (swapped);

   while (head->prev != NULL) {
        head = head->prev;
    }
    while (tail->next != NULL) {
        tail = tail-> next;
    }

    printf("学生记录已按总分降序排序。\n");
}

void sort_Score_In_Ascending_Order_By_Sum() {
    STU* current = head;

    if (current == NULL || current->next == NULL) {
        printf("学生记录不足以排序。\n");
        return;
    }

    STU* min;
    STU* outer_current = head;

    while (outer_current != NULL) {
        min = outer_current;
        STU* inner_current = outer_current->next;

        while (inner_current != NULL) {
            if (CalculateTotalScore(inner_current) < CalculateTotalScore(min)) {
                min = inner_current;
            }
            inner_current = inner_current->next;
        }

        if (min != outer_current) {
            swap_nodes(outer_current, min);

            if (outer_current == head) {
                head = min;
            }

            if (min == tail) {
                tail = outer_current;
            }
        }

        outer_current = outer_current->next;
    }

    printf("学生记录已按总分升序排序。\n");
}

void sort_Score_In_Descending_Order_By_Num(){
     STU* current = head;
    if(current == NULL||current->next == NULL){
        printf("学生记录不足以排序。\n");
        return;
    }


    int swapped;

    do {
        swapped = 0;
        current = head;
        
        while (current->next != NULL) {
            if (strcmp(current->num, current->next->num)<0) {
                swap_nodes(current,current->next);
                swapped = 1;    
            } else {
                current = current->next;
            }
        }
    } while (swapped);

   while (head->prev != NULL) {
        head = head->prev;
    }
    while (tail->next != NULL) {
        tail = tail-> next;
    }

    printf("学生记录已按学号降序排序。\n");
}