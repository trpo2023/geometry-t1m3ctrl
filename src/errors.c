#include "../include/errors.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BasicErrorChecker(char* str, long int len, char* name, int line)
{
    int error_num = 0;

    error_num = NameErrorChecker(name, line);
    if (error_num == 0) {
        error_num = BracketsErrorChecker(str, line, strlen(name) - 1);
        if (error_num == 0) {
            error_num = UnexpectedTokenErrorChecker(str, line);
        }
    }
    return error_num;
}

int BracketsErrorChecker(char* str, int line, long int name_len)
{
    int column = 0;
    int error_column_open;
    int error_column_close;
    int column_flag = 0;
    int error_flag_brackets = 0;
    int stack = 0;
    do {
        if (*str == '(') {
            error_column_open = column;
            column_flag = 1;
            stack++;
            str++;
        } else {
            if (*str == ')') {
                error_column_close = column;
                if (--stack < 0) {
                    if (column_flag == 1) {
                        error_flag_brackets = 1;
                        printf("%sError: expected '(' [line %d column "
                               "%d]%s\n",
                               RED,
                               line,
                               error_column_open + 1,
                               RESET);
                        break;
                    } else if (column_flag == 0) {
                        error_flag_brackets = 1;
                        printf("%sError: expected '(' [line %d column "
                               "%ld]%s\n",
                               RED,
                               line,
                               name_len,
                               RESET);
                        break;
                    }
                }
            }
            str++;
        }
        column++;
    } while (*str);
    if (stack > 0) {
        error_flag_brackets = 1;
        printf("%sError: expected ')' [line %d column %d]%s\n",
               RED,
               line,
               error_column_close + 1,
               RESET);
    }
    return error_flag_brackets;
}

int NameErrorChecker(char* str, int line)
{
    char figure_name[][10] = {"circle", "triangle", "polygon"};
    int i, error_flag_name = 2;
    for (i = 0; i < 3; i++) {
        if (strncmp(str, figure_name[i], strlen(figure_name[i])) == 0) {
            error_flag_name = 0;
        }
    }
    if (error_flag_name != 0)
        printf("%sError: expected 'circle', 'triangle' or 'polygon' [line "
               "%d "
               "column 0]%s\n",
               RED,
               line,
               RESET);
    return error_flag_name;
}

int UnexpectedTokenErrorChecker(char* str, int line)
{
    int error_flag_token = 0;

    char* bracket_closed_last;

    bracket_closed_last = strrchr(str, ')');

    if (bracket_closed_last - str + 2 != strlen(str)) {
        error_flag_token = 3;
        printf("%sError: unexpected token [line %d "
               "column %ld]%s\n",
               RED,
               line,
               bracket_closed_last - str + 1,
               RESET);
    }

    return error_flag_token;
}

int isNumber(char* str, int line)
{
    int floating_point = 0;
    int i;
    int minus = 0;
    int error_flag_container = 0;
    int len = strlen(str);

    for (i = 0; i < len; i++) {
        if ((i == 0) && (str[i] == '-')) {
            minus = 1;
            continue;
        } else if ((isdigit(str[minus]) == 0) || (isdigit(str[len - 1]) == 0)) {
            error_flag_container = 4;
            printf("%sError: expected <double> in brackets [line %d]%s\n",
                   RED,
                   line,
                   RESET);
            break;
        } else if (((i > minus) || (i < len - 1)) && (str[i] == '.')) {
            floating_point++;
            if (floating_point > 1) {
                error_flag_container = 4;
                printf("%sError: expected <double> in brackets [line "
                       "%d]%s\n",
                       RED,
                       line,
                       RESET);
                break;
            }
        } else if (
                ((i > minus) || (i < len - 1))
                && ((isdigit(str[i]) == 0) && (str[i] != '.'))) {
            error_flag_container = 4;
            printf("%sError: expected <double> in brackets [line %d]%s\n",
                   RED,
                   line,
                   RESET);
            break;
        }
    }
    return error_flag_container;
}

int CircleContentErrorChecker(char* str, long int len, int line)
{
    char* bracket_open_first = strchr(str, '(');
    char* bracket_closed_last = strrchr(str, ')');
    int i, j, error_extract = 0;
    char container[len], *istr;
    char sep[2] = ", ";

    for (i = bracket_open_first - str + 1, j = 0; i < bracket_closed_last - str;
         i++, j++) {
        container[j] = str[i];
    }
    container[j + 1] = '\0';

    istr = strtok(container, sep);
    error_extract = isNumber(istr, line);
    if (error_extract == 0) {
        istr = strtok(0, sep);
        error_extract = isNumber(istr, line);
        if (error_extract == 0) {
            istr = strtok(0, sep);
            error_extract = isNumber(istr, line);
            if (error_extract == 0) {
                istr = strtok(0, sep);
                if (istr)
                    printf("%sError: unexpected token in brackets [line "
                           "%d]%s\n",
                           RED,
                           line,
                           RESET);
            }
        }
    }

    return error_extract;
}