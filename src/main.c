#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errors.h>
#include <geometry.h>

#define MAX_SIZE 300

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
    // char figure_name[][10] = {"circle", "triangle", "polygon"};

    int line, error_num = 0, id_circle = 0;
    // int id_triangle = 0, id_polygon = 0;

    geometry = fopen("../res/geometry.txt", "r");

    if (geometry == NULL) {
        printf("FILE READ ERROR!");
    } else {
        line = 1;
        while (!feof(geometry)) {
            if (fgets(str1, MAX_SIZE, geometry) != NULL) {
                printf("%d. %s", line, str1);
                long int column = 0;
                long int len = strlen(str1);
                int type_id = 0;
                error_num = isWKT(str1, &column, &type_id);

                if ((error_num == 0) && (type_id == 0)) {
                    tmp_circle = CircleExtractor(str1, len);
                    circles[id_circle] = *tmp_circle;
                    id_circle++;
                }

                if (error_num != 0) {
                    ErrorOutput(error_num, line, column);
                }
                line++;
            }
        }
        fclose(geometry);
    }

    puts("\nOutput");
    for (int i = 0; i < id_circle; i++) {
        circles[i].area = CircleAreaCalc(circles[i].radius);
        circles[i].perimeter = CirclePerimeterCalc(circles[i].perimeter);
        printf("\n%d. circle(%.1lf %.1lf, %.1lf)\n\tperimeter = %.1lf\n\tarea "
               "= %.1lf\n",
               i + 1,
               circles[i].center.x,
               circles[i].center.y,
               circles[i].radius,
               circles[i].perimeter,
               circles[i].area);
    }
    return 0;
}

// need strtok in extractor functions + in circle must be 2 brackets, other 4
// brackets strtok must have 3 values in circle
//                  6 values in triangle
//                  even (2*n) values in polygon