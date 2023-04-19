#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <geometry.h>

#define M_PI 3.14159265358979323846

Circle* CircleExtractor(char* str, long int len)
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
    temporary->radius = fabs(atof(istr));

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

int* IntersectsDetector(
        Circle our_circ, Circle* other_circs, int circs_cnt, int circ_id)
{
    int* intersects;
    int inter_count = 0;
    intersects = (int*)malloc(circs_cnt * sizeof(int));
    for (int i = 0; i < circs_cnt; i++) {
        if (i == circ_id) {
            intersects[inter_count] = 0;
            inter_count++;
            continue;
        }
        double distance
                = sqrt(pow(our_circ.center.x - other_circs[i].center.x, 2)
                       + pow(our_circ.center.y - other_circs[i].center.y, 2));
        double radius_sum = our_circ.radius + other_circs[i].radius;

        if (distance <= radius_sum)
            intersects[inter_count] = i + 1;
        else
            intersects[inter_count] = 0;

        inter_count++;
    }

    return intersects;
}
// Triangle* TriangleExtractor(char* str, long int len, int line)
// {
// }

// Polygon* PolygonExtractor(char* str, long int len, int line)
// {
// }
