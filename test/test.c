#include <ctest.h>
#include <ctype.h>
#include <string.h>

#include <errors.h>
#include <geometry.h>

char figure_name[][10] = {"circle", "triangle", "polygon"};

CTEST(partest, test1)
{
    char str[] = "poawlygon((3 -2.0, 3.0 2, 1.0 0, 3.0 -2, 3.0 2, 3 -2.0)) ";
    int len = strlen(str);
    char name[len];
    int error_num;
    long int column = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            name[i] = '\0';
            break;
        }
        name[i] = tolower(str[i]);
    }
    error_num = BasicErrorChecker(str, len, name, &column);
    if (error_num == 0)
        if (strncmp(name, figure_name[0], strlen(figure_name[0])) == 0)
            error_num = CircleContentErrorChecker(str, len);

    ASSERT_EQUAL(2, error_num);
}

CTEST(partest, test2)
{
    char str[] = "circle(10x 0, 1.5) ";
    int len = strlen(str);
    char name[len];
    int error_num;
    long int column = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            name[i] = '\0';
            break;
        }
        name[i] = tolower(str[i]);
    }
    error_num = BasicErrorChecker(str, len, name, &column);
    if (error_num == 0)
        if (strncmp(name, figure_name[0], strlen(figure_name[0])) == 0)
            error_num = CircleContentErrorChecker(str, len);

    ASSERT_EQUAL(4, error_num);
}

CTEST(partest, test3)
{
    char str[] = "circle(10 0, 1..5) ";
    int len = strlen(str);
    char name[len];
    int error_num;
    long int column = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            name[i] = '\0';
            break;
        }
        name[i] = tolower(str[i]);
    }
    error_num = BasicErrorChecker(str, len, name, &column);
    if (error_num == 0)
        if (strncmp(name, figure_name[0], strlen(figure_name[0])) == 0)
            error_num = CircleContentErrorChecker(str, len);

    ASSERT_EQUAL(4, error_num);
}

CTEST(partest, test4)
{
    char str[] = "circle10 0, 1.5) ";
    int len = strlen(str);
    char name[len];
    int error_num;
    long int column = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            name[i] = '\0';
            break;
        }
        name[i] = tolower(str[i]);
    }
    error_num = BasicErrorChecker(str, len, name, &column);
    if (error_num == 0)
        if (strncmp(name, figure_name[0], strlen(figure_name[0])) == 0)
            error_num = CircleContentErrorChecker(str, len);

    ASSERT_EQUAL(1, error_num);
}

CTEST(partest, test5)
{
    char str[] = "circle(10 0, 1.5 ";
    int len = strlen(str);
    char name[len];
    int error_num;
    long int column = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            name[i] = '\0';
            break;
        }
        name[i] = tolower(str[i]);
    }
    error_num = BasicErrorChecker(str, len, name, &column);
    if (error_num == 0)
        if (strncmp(name, figure_name[0], strlen(figure_name[0])) == 0)
            error_num = CircleContentErrorChecker(str, len);

    ASSERT_EQUAL(5, error_num);
}

CTEST(partest, test6)
{
    char str[] = "circle(10 0, 1.5) wowo ";
    int len = strlen(str);
    char name[len];
    int error_num;
    long int column = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            name[i] = '\0';
            break;
        }
        name[i] = tolower(str[i]);
    }
    error_num = BasicErrorChecker(str, len, name, &column);
    if (error_num == 0)
        if (strncmp(name, figure_name[0], strlen(figure_name[0])) == 0)
            error_num = CircleContentErrorChecker(str, len);

    ASSERT_EQUAL(3, error_num);
}