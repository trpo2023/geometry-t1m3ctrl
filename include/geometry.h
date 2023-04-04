#pragma once

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

Circle* CircleExtractor(char* str, long int len);
double CircleAreaCalc(double radius);
double CirclePerimeterCalc(double radius);
// Triangle* TriangleExtractor(char* str, long int len, int line);
// Polygon* PolygonExtractor(char* str, long int len, int line);
// int ContainerErrorChecker(char* str, int line);
