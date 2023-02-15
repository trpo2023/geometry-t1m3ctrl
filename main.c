#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 60

// void FigureDefinition(char* s);
// void FigureInput();
// void FigureOutput(char* s, int n);

typedef struct {
    float x;
    float y;
} point;

typedef struct {
    int id;
    char FigureName[15];
    point center;
    float radius;
    float perimeter;
    float area;
    int* intersects;
} circle;

typedef struct {
    int id;
    char FigureName[15];
    point apex[3];
    float perimeter;
    float area;
    int* intersects;
} triangle;

typedef struct {
    int id;
    char FigureName[15];
    point* apex;
    float perimeter;
    float area;
    int* intersects;
} polygon;

int main()
{
    triangle* triangles;
    circle* circles;
    polygon* polygons;
    char s[MAX_SIZE];
    return 0;
}

// void FigureDefinition(char* s)
// {
// }

// void FigureInput()
// {
//     char string[];
//     scanf("%s", string);
// }

// void FigureOutput(char* s, int n)
// {
//     for (i = 0; i < n; i++)
//         fputs(s, stdout);
// }