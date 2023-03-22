#pragma once

#define RESET "\033[0m"
#define RED "\033[1;31m"

int BasicErrorChecker(char* str, long int len, char* name, int line);
int BracketsErrorChecker(char* str, int line, long int name_len);
int NameErrorChecker(char* str, int line);
int UnexpectedTokenErrorChecker(char* str, int line);
int CircleContentErrorChecker(char* str, long int len, int line);
int isNumber(char* str, int line);
