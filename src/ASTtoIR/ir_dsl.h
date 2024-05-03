#ifndef IR_DSL_H
#define IR_DSL_H

#define IR_CELL_                                                     (interm_repr -> cell)
                         
#define IR_SIZE_                                                     (interm_repr -> size)
                         
#define IR_CAPACITY_                                                 (interm_repr -> capacity)
                         
#define IR_TOP_CELL_                                                 (IR_CELL_ + IR_SIZE_)

#define IR_EMIT_CMD_ADD_RR(dest_reg, src_reg)                        IntReprEmit (interm_repr, "add",  IR_CMD_MUL, dest_reg,      NULL, NULL,          false, src_reg,         NULL,    NULL,         false, NULL, NULL, false)                  

#define IR_EMIT_CMD_SUB_RR(dest_reg, src_reg)                        IntReprEmit (interm_repr, "sub",  IR_CMD_MUL, dest_reg,      NULL, NULL,          false, src_reg,         NULL,    NULL,         false, NULL, NULL, false)

#define IR_EMIT_CMD_MUL_RR(dest_reg, src_reg)                        IntReprEmit (interm_repr, "imul", IR_CMD_MUL, dest_reg,      NULL, NULL,          false, src_reg,         NULL,    NULL,         false, NULL, NULL, false)

#define IR_EMIT_CMD_DIV_RR(src_reg)                                  IntReprEmit (interm_repr, "div",  IR_CMD_DIV, IR_OP_REG_RAX, NULL, NULL,          false, src_reg,         NULL,    NULL,         false, NULL, NULL, false)

#define IR_EMIT_CMD_MOV_MR(dest_reg, dest_mem_disp, src_reg)         IntReprEmit (interm_repr, "mov",  IR_CMD_MOV, dest_reg,      NULL, dest_mem_disp, true,  src_reg,         NULL,    NULL,         false, NULL, NULL, false)

#define IR_EMIT_CMD_MOV_RM(dest_reg, src_reg, src_mem_disp)          IntReprEmit (interm_repr, "mov",  IR_CMD_MOV, dest_reg,      NULL, NULL,          false, src_reg,         NULL,    src_mem_disp, true,  NULL, NULL, false)

#define IR_EMIT_CMD_MOV_MI(dest_reg, dest_mem_disp, imm_val)         IntReprEmit (interm_repr, "mov",  IR_CMD_MOV, dest_reg,      NULL, dest_mem_disp, true,  IR_OP_IMMEDIATE, imm_val, NULL,         false, NULL, NULL, false)

#endif