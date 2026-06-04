#include<stdio.h>

#include "instr.h"
#include "instr_types.h"
int main()
{
	char mnema[5]; //movi самая длинная команда
	while (scanf("%s", mnema) == 1) //считывание mnemonic
	{
		struct instr_t instr;
		get_instr(&instr, mnema);
		print_hex_digit(&instr);
	}
	printf("\n");
}
