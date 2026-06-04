#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instr_types.h"

// Статические вспомогательные функции (видны только в этом файле)
static void is_valid_register(char reg) {
    if (reg < 'A' || reg > 'D') {
        fprintf(stderr, "Wrong register %c\n", reg);
        abort();
    }
}

static void handle_arith(struct instr_t* instr, enum opcode_t opcode) {
    char reg1, reg2;
    getchar();
    scanf("%c", &reg1);
    getchar(); getchar();
    scanf("%c", &reg2);
    
    is_valid_register(reg1);
    is_valid_register(reg2);
    
    instr->opcode = opcode;
    instr->opnd.ops.rd = reg1 - 'A';
    instr->opnd.ops.rs = reg2 - 'A';
}

static void handle_io(struct instr_t* instr, enum opcode_t opcode) {
    getchar();
    char reg;
    scanf("%c", &reg);
    is_valid_register(reg);
    instr->opcode = opcode;
    instr->opnd.rop = reg - 'A';
}

// Публичные функции
void get_instr(struct instr_t* instr, const char* mnema) {
    if (strcmp(mnema, "MOVI") == 0) {
        int immediate;
        int res = scanf("%d", &immediate);
        if (res != 1) {
            fprintf(stderr, "Cannot read integer\n");
            abort();
        }
        char ch = immediate & 0x7F;
        if (ch != immediate) {
            fprintf(stderr, "Wrong number, must be under 128\n");
            abort();
        }
        instr->opcode = MOVI;
        instr->opnd.imm = ch;
        return;
    }
    
    if (strcmp(mnema, "IN") == 0) {
        handle_io(instr, IN);
        return;
    }
    
    if (strcmp(mnema, "OUT") == 0) {
        handle_io(instr, OUT);
        return;
    }
    
    if (strcmp(mnema, "ADD") == 0) {
        handle_arith(instr, ADD);
        return;
    }
    
    if (strcmp(mnema, "SUB") == 0) {
        handle_arith(instr, SUB);
        return;
    }
    
    if (strcmp(mnema, "MUL") == 0) {
        handle_arith(instr, MUL);
        return;
    }
    
    if (strcmp(mnema, "DIV") == 0) {
        handle_arith(instr, DIV);
        return;
    }
    
    fprintf(stderr, "Cannot recognize command\n");
    abort();
}

void print_hex_digit(const struct instr_t* instr) {
    unsigned char hex = 0;
    switch (instr->opcode) {
        case MOVI:
            hex = instr->opnd.imm;
            break;
        case IN:
            hex = 0xC0 | instr->opnd.rop;
            break;
        case OUT:
            hex = 0xC4 | instr->opnd.rop;
            break;
        case ADD:
        case SUB:
        case MUL:
        case DIV:
            hex = ((instr->opcode << 4) & 0xF0) | 
                  (instr->opnd.ops.rd << 2) | 
                  instr->opnd.ops.rs;
            break;
        default:
            fprintf(stderr, "Cannot recognize instr\n");
            abort();
    }
    printf("%#x ", hex);
}
