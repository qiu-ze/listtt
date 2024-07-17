//
// Created by armstrong on 24-7-17.
//
#include <stdio.h>
#include "student.h"
#include <windows.h>

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