#include <stdio.h>
#include "student.h"
#include "function.c"
#include <windows.h>

void print_Menu() {
    printf("*******************************************************\n");
    printf("|              欢迎使用基于数组的学生信息管理系统        |\n");
    printf("|       1.Append record                               |\n");
    printf("|       2.List record                                 |\n");
    printf("|       3.Delete record                               |\n");
    printf("|       4.Modify record                               |\n");
    printf("|       5.Search record                               |\n");
    printf("|       6.Sort Score in descending order by sum       |\n");
    printf("|       7.Sort Score in ascending order by sum        |\n");
    printf("|       8.Sort Score in descending order by num       |\n");
    printf("|       9.Sort Score in ascending order by num        |\n");
    printf("|      10.Write to a File                             |\n");
    printf("|      11.Read from a File                            |\n");
    printf("|      12.Insert                                      |\n");
    printf("|      13.Exit                                        |\n");
    printf("*******************************************************\n");
}

int main() {
    SetConsoleOutputCP(65001);
    int aa;
    while (1) {
        print_Menu();
        printf("选择你要使用的功能\n");
        if(scanf("%d", &aa)!=1) {
            while (getchar()!='\n');
            printf("无效的输入，请输入数字。\n");
            continue;
        };
        switch (aa) {
            case 1:
                printf("你选择的功能是Append record\n");
                append_Record();
                break;
            case 2:
                printf("你选择的功能是List record\n");
                list_Record();
                break;
            case 3:
                printf("你选择的功能是Delete record\n");
                delete_Record();
                break;
            case 4:
                printf("你选择的功能是Modify record\n");
                modify_Record();
                break;
            case 5:
                printf("你选择的功能是Search record\n");
                search_Record();
                break;
            case 6:
                printf("你选择的功能是Sort score in descending order by sum\n");
                sort_Score_In_Descending_Order_By_Sum();
                break;
            case 7:
                printf("你选择的功能是Sort score in ascending order by sum\n");
                sort_Score_In_Ascending_Order_By_Sum();
                break;
            case 8:
                printf("你选择的功能是Sort score in descending order by num\n");
                sort_Score_In_Descending_Order_By_Num();
                break;
            case 9:
                printf("你选择的功能是Sort score in ascending order by num\n");
                sort_Score_In_Ascending_Order_By_Num();
                break;
            case 13:
                printf("Byebye\n");
                Exit();
                break;
            default: printf("无此功能\n");
        }
        system("pause");
        system("cls");
    }
}

