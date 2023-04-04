#pragma once

#define RESET "\033[0m"
#define RED "\033[1;31m"

int BasicErrorChecker(char* str, long int len, char* name, long int* column);
int BracketsErrorChecker(char* str, long int name_len, long int* column);
int NameErrorChecker(char* str, long int* column);
int UnexpectedTokenErrorChecker(char* str, long int* column);
int CircleContentErrorChecker(char* str, long int len);
int isNumber(char* str);
void ErrorOutput(int error_num, int line, long int column);
