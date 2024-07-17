//
// Created by armstrong on 24-7-14.
//
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
    inputStudentNumber(new_student, head);
    printf("输入姓名: ");
    scanf("%s",new_student->name );
    while(!isUniqueName(new_student->name,head)) {
        printf("已经有学生%s录入，请重新输入姓名:\n", new_student->name);
        scanf("%s", new_student->name);
    }
    printf("输入专业: ");
    scanf("%s", new_student->major);
    while(!major_Confirm(new_student)) {
        printf("重新输入专业: ");
        scanf("%s", new_student->major);
    }
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

    if(current == NULL){
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

    if(current == NULL){
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
            inputStudentNumber(current, head);
            printf("输入修改后姓名: ");
            scanf("%s",current->name );
            while(!isUniqueName(current->name,head)) {
                printf("已经有学生%s录入，请重新输入姓名:\n", current->name);
                scanf("%s", current->name);
            }
            printf("输入修改后专业: ");
            scanf("%s", current->major);
            while(!major_Confirm(current)) {
                printf("重新输入专业: ");
                scanf("%s", current->major);
            }
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

    if(current == NULL){
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

    STU* outer_current = head;

    while (outer_current != NULL) {
        STU *min = outer_current;
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

void sort_Score_In_Ascending_Order_By_Num(){
    STU* current = head;

    if (current == NULL || current->next == NULL) {
        printf("学生记录不足以排序。\n");
        return;
    }

    STU* out_current = head;

    while  (out_current != NULL){
        STU *min = out_current;
        STU* inner_current = head;
        while(inner_current != NULL){
            if(strcmp(inner_current->num,min->num) < 0){
                min = inner_current;
            }
            inner_current = inner_current->next;
        }
        if(min != out_current){
            swap_nodes(out_current,min);
            if (out_current == head){
                head = min;
            }
            if (min == tail){
                tail = out_current;
            }
        }
        out_current = out_current->next;
    }
    printf("学生已按学号升序排序");
}

void write_To_File(){
    FILE *fp = fopen("student.dat","wb");

    if (fp == NULL){
        printf("文件打开失败");
        return;
    }
    STU* current = head;

    while (current != NULL){
    fwrite(current,sizeof(STU),1,fp);
    current = current->next;
    }

    fclose(fp);
    printf("学生信息已成功保存到 student.dat 文件中。\n");
}

void read_From_A_File() {
    printf("想要读取全部学生的数据请按1。\n");
    printf("想要根据学号和姓名读取单个学生的数据请按2。\n");
    int ll;
    while (1) {
        if(scanf("%d", &ll)!=1) {
            while (getchar()!='\n');
            printf("无效的输入，请输入数字。\n");
            continue;
        }
        switch (ll) {
            case 1:
                read_All_From_File();
                break;
            case 2:
                read_One_From_File();
                break;
            default:printf("请输入1或2\n");
        }
        break;
    }
}

void read_All_From_File(){
    FILE *fp = fopen("student.dat","rb");
    
    if (fp == NULL){
        printf("文件打开失败");
        return;
    }

    STU read_student;

    while(fread(&read_student,sizeof(STU),1,fp)) {
        STU* new_student = (STU*)malloc(sizeof(STU));

        if (new_student == NULL) {
            printf("内存分配失败\n");
            fclose(fp);
            return;
        }

        *new_student = read_student;
        new_student->next = NULL;
        new_student->prev = NULL;

        if(head == NULL) {
            head = new_student;
            tail = new_student;
        }else {
            new_student->prev = tail;
            head->next = new_student;
            tail = new_student;
        }
    }
    printf("已从student.dat中读取全部学生数据\n");
}

void read_One_From_File() {
    FILE *fp = fopen("student.dat","rb");

    if (fp == NULL){
        printf("文件打开失败");
        return;
    }

    char searchNumName[15];
    printf("请输入要查找的学生学号或姓名: ");
    scanf("%s",searchNumName);

    STU read_student;
    int found = 0;

    while (fread(&read_student,sizeof(STU),1,fp)) {
        if (strcmp(searchNumName,read_student.name) == 0||strcmp(searchNumName,read_student.num) == 0) {
            printf("学号: %s\n", read_student.num);
            printf("  姓名: %s\n",read_student.name );
            printf("  专业: %s\n",read_student.major);
            printf("  班级: %d\n",read_student.classNo);
            for (int j = 0; j < M; j++) {
                printf("  第%d门课程成绩: %d\n", j + 1, read_student.score[j]);
            }
            found = 1;
            break;
        }
    }
    if(!found) {
        printf("未找到该学生的记录。\n");
    }
    fclose(fp);
}

void Insert() {
    STU* current = head;

    if (current == NULL || current->next == NULL) {
        printf("学生记录不足以排序。\n");
        return;
    }

    while (current != NULL) {
            STU *i = current->prev;
        while (i != current && i != NULL ) {
            if (CalculateTotalScore(i) < CalculateTotalScore(current)){
                swap_nodes(i,current);
            }
            if(i != NULL) {
                i = i->prev;
            }
        }

        current = current->next;
    }

    while (head->prev != NULL) {
        head = head->prev;
    }
    while (tail->next != NULL) {
        tail = tail->next;
    }

    printf("学生记录已按总分降序排序。\n");
}


//helpfunctions

bool validateInput(const char *input) {
    State state = STATE_START_2_0;
    int x_count = 0;

    while (*input != '\0') {
        switch (state) {
            case STATE_START_2_0:
                if (*input == '2') {
                    state = STATE_2_1;
                } else {
                    state = STATE_INVALID;
                }
            break;

            case STATE_2_1:
                if (*input == '2') {
                    state = STATE_2_2;
                } else {
                    state = STATE_INVALID;
                }
            break;

            case STATE_2_2:
                if (*input == '2') {
                    state = STATE_0;
                } else {
                    state = STATE_INVALID;
                }
            break;

            case STATE_0:
                if (*input == '0') {
                    state = STATE_2_3;
                } else {
                    state = STATE_INVALID;
                }
            break;

            case STATE_2_3:
                if (*input == '2') {
                    state = STATE_X;
                } else {
                    state = STATE_INVALID;
                }
            break;

            case STATE_X:
                if (*input >= '0' && *input <= '9') {
                    x_count++;
                    if (x_count == 5) {
                        state = STATE_VALID;
                    }
                } else {
                    state = STATE_INVALID;
                }
            break;

            case STATE_VALID:
                state = STATE_INVALID;
            break;

            case STATE_INVALID:
                return false;

            default:
                return false;
        }
        input++;
    }

    return state == STATE_VALID;
}


int major_Confirm(const STU* new_student) {
    if(strcmp(new_student->major,"software")!=0 && strcmp(new_student->major,"computer")!=0 && strcmp(new_student->major,"network")!=0) {
        while (getchar()!='\n');
        printf("无效的输入，请输入computer,software,network三者之一。\n");
        return 0;
    }
    else {
        return 1;
    }
}

int CalculateTotalScore(const STU* current) {
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

int isUniqueNumber(const char *num, STU *head) {
    STU *current = head;
    while (current != NULL) {
        if (strcmp(num, current->num) == 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

int isUniqueName(const char *name, STU *head) {
    STU *current = head;
    while (current != NULL) {
        if (strcmp(name, current->name) == 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

void inputStudentNumber(STU *new_student, STU *head) {
    bool is_valid = validateInput(new_student->num);
    int is_unique = isUniqueNumber(new_student->num, head);

    while (!is_valid || !is_unique) {
        if (!is_unique) {
            printf("已经有学生的学号是%s，请重新输入学号:\n", new_student->num);
            scanf("%s", new_student->num);
        }
        if (!is_valid) {
            printf("%s 不是正确的学号类型，请输入类似22202xxxxx的学号\n", new_student->num);
            printf("重新输入学号: ");
            scanf("%s", new_student->num);
        }
        is_valid = validateInput(new_student->num);
        is_unique = isUniqueNumber(new_student->num, head);
    }
}