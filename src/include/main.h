#ifndef MAIN_H
#define MAIN_H

int input_number();
void append_and(char* buffer, struct NumberFormat format, int is_last);
void convert_to_danish(int number, char* buffer, struct NumberFormat format);

#endif // MAIN_H
