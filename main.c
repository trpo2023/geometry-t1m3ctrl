#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 300

#define RESET "\033[0m"
#define RED "\033[1;31m"

void StringParser(char* str, long int len, int line);
int BracketsErrorChecker(const char* str, int line, long int name_len);
int NameErrorChecker(const char* str, int line);
int UnexpectedTokenErrorChecker(const char* str, int line);
int ContainerErrorChecker(char* str, int line);

// typedef struct {
//     float x;
//     float y;
// } point;

// typedef struct {
//     int id;
//     char figure_name[15];
//     point center;
//     float radius;
//     float perimeter;
//     float area;
//     int* intersects;
// } circle;

// typedef struct {
//     int id;
//     char figure_name[15];
//     point apex[3];
//     float perimeter;
//     float area;
//     int* intersects;
// } triangle;

// typedef struct {
//     int id;
//     char figure_name[15];
//     point* apex;
//     float perimeter;
//     float area;
//     int* intersects;
// } polygon;

int main()
{
    FILE* geometry;

    // triangle* triangles;
    // circle* circles;
    // polygon* polygons;
    char str1[MAX_SIZE];

    int line;

    geometry = fopen("geometry.txt", "r");

    if (geometry == NULL) {
        printf("FILE READ ERROR!");
    } else {
        line = 1;
        while (!feof(geometry)) {
            if (fgets(str1, MAX_SIZE, geometry) != NULL) {
                printf("%s", str1);
                StringParser(str1, strlen(str1) + 1, line); // +1 cause of '\0'
                line++;
            }
        }
        fclose(geometry);
    }
    return 0;
}

void StringParser(char* str, long int len, int line)
{
    int i, error_num = 0;
    char name[len];

    for (i = 0; i < len; i++) {
        if (str[i] == '(') {
            name[i] = '\0';
            break;
        }
        name[i] = tolower(str[i]);
    }

    error_num = NameErrorChecker(name, line);
    if (error_num == 0) {
        error_num = BracketsErrorChecker(str, line, strlen(name) - 1);
        if (error_num == 0) {
            error_num = UnexpectedTokenErrorChecker(str, line);
            // if (error_num == 0) {
            //     error_num = ContainerErrorChecker(str, line);
            // }
        }
    }
}

int BracketsErrorChecker(const char* str, int line, long int name_len)
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
                        printf("%sError: expected '(' [line %d "
                               "column %d]%s\n",
                               RED,
                               line,
                               error_column_open + 1,
                               RESET);
                        break;
                    } else if (column_flag == 0) {
                        error_flag_brackets = 1;
                        printf("%sError: expected '(' [line %d "
                               "column %ld]%s\n",
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

int NameErrorChecker(const char* str, int line)
{
    char figure_name[][10] = {"circle", "triangle", "polygon"};
    int i, error_flag_name = 2;
    for (i = 0; i < 3; i++) {
        if (strncmp(str, figure_name[i], strlen(figure_name[i])) == 0) {
            error_flag_name = 0;
        }
    }
    if (error_flag_name != 0)
        printf("%sError: expected 'circle', 'triangle' or 'polygon' [line %d "
               "column 0]%s\n",
               RED,
               line,
               RESET);
    return error_flag_name;
}

int UnexpectedTokenErrorChecker(const char* str, int line)
{
    int error_flag_token = 0;

    char* bracket_closed_last;

    bracket_closed_last = strrchr(str, ')');

    // printf("bracket_closed_last - str = %ld, strlen(str) = %ld\n",
    //        bracket_closed_last - str,
    //        strlen(str));

    // bracket_closed_last - str + 2 (+1 - \n)
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

// int ContainerErrorChecker(char* str, int line)
// {
//     int i, j, k = 0, error_flag_container = 0, floating_point = 0,
//     error_column,
//               multipart = 0;

//     char* container;
//     char** multipart_content;
//     char* istr;

//     char sep[2] = ", ";

//     char* bracket_open_last;
//     char* bracket_closed_last;
//     char* bracket_open_first;
//     char* bracket_closed_first;

//     bracket_open_first = strchr(str, '(');
//     bracket_closed_last = strrchr(str, ')');

//     container = (char*)malloc(
//             (bracket_closed_last - str - (bracket_open_first - str + 1))
//             * sizeof(char));

//     for (i = bracket_open_first - str + 1, j = 0; i < bracket_closed_last -
//     str;
//          i++, j++) {
//         container[j] = str[i];
//         if (str[i] == '(')
//             multipart++;
//     }

//     multipart_content = (char**)malloc(multipart * sizeof(char*));

//     do {
//         bracket_open_first = strchr(container, '(');
//         bracket_closed_first = strchr(container, ')');
//         multipart_content = (char*)malloc(
//                 (bracket_closed_first - container
//                  - (bracket_open_first - container + 1))
//                 * sizeof(char));
//         for (i = bracket_open_first - str + 1, j = 0;
//              i < bracket_closed_first - str;
//              i++, j++) {
//             multipart_content[k][j] = str[i];
//         }
//         k++;
//     } while (k < multipart);

//     error_column = bracket_open_last - str + 1;
//     istr = strtok(container, sep);
//     error_column++;
//     while (istr != NULL) {
//         floating_point = 0;
//         for (i = 0; i < strlen(istr); i++) {
//             error_column++;
//             if ((i == 0) && (istr[i] == '-'))
//                 continue;
//             if (((i >= 0) || (i <= strlen(istr) - 1)) && (istr[i] == '.')) {
//                 floating_point++;
//                 if (floating_point > 1) {
//                     error_flag_container = 4;
//                     printf("%sError: expected <double> [line %d "
//                            "column %d]%s\n",
//                            RED,
//                            line,
//                            error_column - 2,
//                            RESET);
//                     break;
//                 }
//             }
//             if ((isdigit(istr[i]) == 0) && (istr[i] != '.')) {
//                 error_flag_container = 4;
//                 printf("%sError: expected <double> [line %d "
//                        "column %d]%s\n",
//                        RED,
//                        line,
//                        error_column - 2,
//                        RESET);
//                 break;
//             }
//         }
//         istr = strtok(NULL, sep);
//         error_column++;
//     }
//     return error_flag_container;
// }