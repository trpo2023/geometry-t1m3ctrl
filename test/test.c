#include <ctest.h>
#include <ctype.h>
#include <string.h>

#include <errors.h>
#include <geometry.h>

// type id = 3 - wrong format
// 0 - circle
// 1 - triangle
// 2 - polygon

CTEST(partest, test1)
{
    char str[] = "poawlygon((3 -2.0, 3.0 2, 1.0 0, 3.0 -2, 3.0 2, 3 -2.0)) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(2, error_num);
    ASSERT_EQUAL(3, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(partest, test2)
{
    char str[] = "circle(10x 0, 1.5) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(4, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(partest, test3)
{
    char str[] = "circle(10 0, 1..5) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(4, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(partest, test4)
{
    char str[] = "circle(10 0, 1.5)) ";

    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(1, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(7, column);
}

CTEST(partest, test5)
{
    char str[] = "circle((10 0, 1.5) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(5, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(18, column);
}

CTEST(partest, test6)
{
    char str[] = "circle(10 0, 1.5) wowo ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(3, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(17, column);
}

CTEST(partest, test7)
{
    char str[] = "circle(10 0, 1.5 1.4) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(6, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(partest, test8)
{
    char str[] = "triangle((-3.0 -2, -1 0.0, -3.0 2.0, -3 -2)) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(0, error_num);
    ASSERT_EQUAL(1, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(partest, test9)
{
    char str[] = "polygon((-3.0 -2, -1 0.0, -3.0 2.0, -3 -2)) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(0, error_num);
    ASSERT_EQUAL(2, type_id);
    ASSERT_EQUAL(0, column);
}
