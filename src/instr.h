#ifndef INSTR_H
#define INSTR_H
#include "instr_types.h"
void get_instr(struct instr_t* instr, const char* mnema);
void print_hex_digit(const struct instr_t* instr);
#endif
