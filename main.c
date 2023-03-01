#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 300

#define RESET "\033[0m"
#define RED "\033[1;31m"

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    Point center;
    float radius;
    float perimeter;
    float area;
    int* intersects;
} Circle;

// typedef struct {
//     Point apex[3];
//     float perimeter;
//     float area;
//     int* intersects;
// } Triangle;

// typedef struct {
//     Point* apex;
//     float perimeter;
//     float area;
//     int* intersects;
// } Polygon;

int BasicErrorChecker(char* str, long int len, char* name, int line);
int BracketsErrorChecker(char* str, int line, long int name_len);
int NameErrorChecker(char* str, int line);
int UnexpectedTokenErrorChecker(char* str, int line);
Circle* CircleExtractor(char* str, long int len, int line);
int CircleContentErrorChecker(char* str, long int len, int line);
// Triangle* TriangleExtractor(char* str, long int len, int line);
// Polygon* PolygonExtractor(char* str, long int len, int line);
// int ContainerErrorChecker(char* str, int line);
int isNumber(char* str, int line);

int main()
{
    FILE* geometry;

    Circle circles[20]; // circles = (Circle*)malloc(line * sizeof(Circle));
    Circle* tmp_circle;

    // Triangle triangles[20];
    // Triangle* tmp_triangle;

    // Polygon polygons[20];
    // Polygon* tmp_polygon;

    char str1[MAX_SIZE];
    char figure_name[][10] = {"circle", "triangle", "polygon"};

    int line, error_num = 0, id_circle = 0;
    // int id_triangle = 0, id_polygon = 0;

    geometry = fopen("geometry.txt", "r");

    if (geometry == NULL) {
        printf("FILE READ ERROR!");
    } else {
        line = 1;
        while (!feof(geometry)) {
            if (fgets(str1, MAX_SIZE, geometry) != NULL) {
                int len = strlen(str1);
                char name[len];

                for (int i = 0; i < len; i++) {
                    if (str1[i] == '(') {
                        name[i] = '\0';
                        break;
                    }
                    name[i] = tolower(str1[i]);
                }

                error_num = BasicErrorChecker(str1, len, name, line);

                if (error_num == 0) {
                    if (strncmp(name, figure_name[0], strlen(figure_name[0]))
                        == 0) {
                        if (CircleContentErrorChecker(str1, len, line) == 0) {
                            tmp_circle = CircleExtractor(str1, len, line);
                            circles[id_circle] = *tmp_circle;
                            id_circle++;
                        }
                    }

                    // if (strncmp(name, figure_name[1], strlen(figure_name[1]))
                    //     == 0) {
                    //     tmp_triangle = TriangleExtractor(str1, len, line);
                    //     triangles[id_triangle] = *tmp_triangle;
                    //     id_triangle++;
                    // }

                    // if (strncmp(name, figure_name[2], strlen(figure_name[2]))
                    //     == 0) {
                    //     tmp_polygon = PolygonExtractor(str1, len, line);
                    //     polygons[id_polygon] = *tmp_polygon;
                    //     id_polygon++;
                    // }
                }
                line++;
            }
        }
        fclose(geometry);
    }

    for (int i = 0; i < id_circle; i++) {
        printf("%d. circle(%.2lf %.2lf, %.2lf)\n",
               i + 1,
               circles[i].center.x,
               circles[i].center.y,
               circles[i].radius);
    }
    return 0;
}

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

Circle* CircleExtractor(char* str, long int len, int line)
{
    Circle* temporary = (Circle*)malloc(sizeof(Circle));
    char* bracket_open_first = strchr(str, '(');
    char* bracket_closed_last = strrchr(str, ')');
    int i, j;
    char container[len], *istr = NULL;
    char sep[2] = ", ";

    for (i = bracket_open_first - str + 1, j = 0; i < bracket_closed_last - str;
         i++, j++) {
        container[j] = str[i];
        // printf("%c", container[j]);
    }
    container[j + 1] = '\0';

    istr = strtok(container, sep);
    temporary->center.x = atof(istr);
    istr = strtok(NULL, sep);
    temporary->center.y = atof(istr);
    istr = strtok(NULL, sep);
    temporary->radius = atof(istr);

    return temporary;
}

int CircleContentErrorChecker(char* str, long int len, int line)
{
    char* bracket_open_first = strchr(str, '(');
    char* bracket_closed_last = strrchr(str, ')');
    int i, j, error_extract = 0;
    char container[len], *istr = NULL;
    char sep[2] = ", ";

    for (i = bracket_open_first - str + 1, j = 0; i < bracket_closed_last - str;
         i++, j++) {
        container[j] = str[i];
    }
    container[j + 1] = '\0';

    istr = strtok(container, sep);
    error_extract = isNumber(istr, line);
    if (error_extract == 0) {
        istr = strtok(NULL, sep);
        error_extract = isNumber(istr, line);
        if (error_extract == 0) {
            istr = strtok(NULL, sep);
            error_extract = isNumber(istr, line);
            if (error_extract == 0) {
                istr = strtok(NULL, sep);
                if (istr != NULL)
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

// Triangle* TriangleExtractor(char* str, long int len, int line)
// {
// }

// Polygon* PolygonExtractor(char* str, long int len, int line)
// {
// }

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

// need strtok in extractor functions + in circle must be 2 brackets, other 4
// brackets strtok must have 3 values in circle
//                  6 values in triangle
//                  even (2*n) values in polygon