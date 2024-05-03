#ifndef IR_DSL_H
#define IR_DSL_H

#define IR_CELL_                               (interm_repr -> cell)

#define IR_SIZE_                               (interm_repr -> size)

#define IR_CAPACITY_                           (interm_repr -> capacity)

#define IR_TOP_CELL_                           (IR_CELL_ + IR_SIZE_)

#define IR_EMIT_CMD_ADD_(dest_reg, src_reg)    IntReprEmit (interm_repr, "add",  IR_CMD_MUL, dest_reg,      NULL, NULL, false, src_reg, NULL, NULL, false, NULL, NULL, false)                  

#define IR_EMIT_CMD_SUB_(dest_reg, src_reg)    IntReprEmit (interm_repr, "sub",  IR_CMD_MUL, dest_reg,      NULL, NULL, false, src_reg, NULL, NULL, false, NULL, NULL, false)

#define IR_EMIT_CMD_MUL_RR(dest_reg, src_reg)  IntReprEmit (interm_repr, "imul", IR_CMD_MUL, dest_reg,      NULL, NULL, false, src_reg, NULL, NULL, false, NULL, NULL, false)

#define IR_EMIT_CMD_DIV_RR(src_reg)            IntReprEmit (interm_repr, "div",  IR_CMD_DIV, IR_OP_REG_RAX, NULL, NULL, false, src_reg, NULL, NULL, false, NULL, NULL, false)

//IR_MOV_RI

#endif