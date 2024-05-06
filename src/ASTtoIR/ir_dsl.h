#ifndef IR_DSL_H
#define IR_DSL_H

#include <stdint.h>

const int64_t IR_POISON = 0xFEE1DEAD; 

#define IR_CELL_                                                (interm_repr -> cell)
                         
#define IR_SIZE_                                                (interm_repr -> size)
                         
#define IR_CAPACITY_                                            (interm_repr -> capacity)
                         
#define IR_TOP_CELL_                                            (IR_CELL_ + IR_SIZE_)

#define IR_EMIT_CMD_ADDSD_RR(dest_reg, src_reg)                 IntReprEmit (interm_repr, "addsd", IR_CMD_MUL, dest_reg, NAN, IR_POISON,     false, src_reg,         NAN,     IR_POISON,    false, NULL, IR_POISON, false)                  

#define IR_EMIT_CMD_SUBSD_RR(dest_reg, src_reg)                 IntReprEmit (interm_repr, "subsd", IR_CMD_MUL, dest_reg, NAN, IR_POISON,     false, src_reg,         NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_MULSD_RR(dest_reg, src_reg)                 IntReprEmit (interm_repr, "mulsd", IR_CMD_MUL, dest_reg, NAN, IR_POISON,     false, src_reg,         NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_DIVSD_RR(dest_reg, src_reg)                 IntReprEmit (interm_repr, "divsd", IR_CMD_DIV, dest_reg, NAN, IR_POISON,     false, src_reg,         NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_MOVSD_MR(dest_reg, dest_mem_disp, src_reg)  IntReprEmit (interm_repr, "movsd", IR_CMD_MOV, dest_reg, NAN, dest_mem_disp, true,  src_reg,         NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_MOVSD_RM(dest_reg, src_reg, src_mem_disp)   IntReprEmit (interm_repr, "movsd", IR_CMD_MOV, dest_reg, NAN, IR_POISON,     false, src_reg,         NAN,     src_mem_disp, true,  NULL, IR_POISON, false)

#define IR_EMIT_CMD_MOVSD_MI(dest_reg, dest_mem_disp, imm_val)  IntReprEmit (interm_repr, "movsd", IR_CMD_MOV, dest_reg, NAN, dest_mem_disp, true,  IR_OP_IMMEDIATE, imm_val, IR_POISON,    false, NULL, IR_POISON, false)

#endif