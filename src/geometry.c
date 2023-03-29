#include "../include/geometry.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_PI 3.14159265358979323846

Circle* CircleExtractor(char* str, long int len, int line)
{
    Circle* temporary = (Circle*)malloc(sizeof(Circle));
    char* bracket_open_first = strchr(str, '(');
    char* bracket_closed_last = strrchr(str, ')');
    int i, j;
    char container[len], *istr;
    char sep[2] = ", ";

    for (i = bracket_open_first - str + 1, j = 0; i < bracket_closed_last - str;
         i++, j++) {
        container[j] = str[i];
        // printf("%c", container[j]);
    }
    container[j] = '\0';

    istr = strtok(container, sep);
    temporary->center.x = atof(istr);
    istr = strtok(0, sep);
    temporary->center.y = atof(istr);
    istr = strtok(0, sep);
    temporary->radius = atof(istr);

    return temporary;
}

double CircleAreaCalc(double radius)
{
    double area = M_PI * radius * radius;
    return area;
}

double CirclePerimeterCalc(double radius)
{
    double perimeter = 2 * M_PI * radius;
    return perimeter;
}

// Triangle* TriangleExtractor(char* str, long int len, int line)
// {
// }

// Polygon* PolygonExtractor(char* str, long int len, int line)
// {
// }
