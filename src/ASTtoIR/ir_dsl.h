#ifndef IR_DSL_H
#define IR_DSL_H


#define IR_CELL_                                                      (interm_repr -> cell)

#define IR_SIZE_                                                      (interm_repr -> size)

#define IR_CAPACITY_                                                  (interm_repr -> capacity)

#define IR_TOP_CELL_                                                  (IR_CELL_ + IR_SIZE_)

#define IR_EMIT_CMD_ADD_DOUBLE_RR(dest_reg, src_reg)                  IntReprEmit (interm_repr, "add double",      IR_CMD_ADD,   dest_reg,         NAN, IR_POISON,     false, src_reg,          NAN,     IR_POISON,    false, NULL, IR_POISON, false)                  

#define IR_EMIT_CMD_SUB_DOUBLE_RR(dest_reg, src_reg)                  IntReprEmit (interm_repr, "sub double",      IR_CMD_SUB,   dest_reg,         NAN, IR_POISON,     false, src_reg,          NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_MUL_DOUBLE_RR(dest_reg, src_reg)                  IntReprEmit (interm_repr, "mul double",      IR_CMD_MUL,   dest_reg,         NAN, IR_POISON,     false, src_reg,          NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_DIV_DOUBLE_RR(dest_reg, src_reg)                  IntReprEmit (interm_repr, "div double",      IR_CMD_DIV,   dest_reg,         NAN, IR_POISON,     false, src_reg,          NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_MOVE_DOUBLE_MR(dest_reg, dest_mem_disp, src_reg)  IntReprEmit (interm_repr, "move double MR",  IR_CMD_MOV,   dest_reg,         NAN, dest_mem_disp, true,  src_reg,          NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_MOVE_DOUBLE_RM(dest_reg, src_reg, src_mem_disp)   IntReprEmit (interm_repr, "move double RM",  IR_CMD_MOV,   dest_reg,         NAN, IR_POISON,     false, src_reg,          NAN,     src_mem_disp, true,  NULL, IR_POISON, false)

#define IR_EMIT_CMD_MOVE_DOUBLE_MI(dest_reg, dest_mem_disp, imm_val)  IntReprEmit (interm_repr, "move double MI",  IR_CMD_MOV,   dest_reg,         NAN, dest_mem_disp, true,  IR_OP_IMMEDIATE,  imm_val, IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_MOVE_DOUBLE_RI(dest_reg, imm_val)                 IntReprEmit (interm_repr, "move double RI",  IR_CMD_MOV,   dest_reg,         NAN, IR_POISON,     false, IR_OP_IMMEDIATE,  imm_val, IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_MOVE_DOUBLE_RR(dest_reg, src_reg)                 IntReprEmit (interm_repr, "move double RR",  IR_CMD_MOV,   dest_reg,         NAN, IR_POISON,     false, src_reg,          NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_READ_DOUBLE(dest_reg)                             IntReprEmit (interm_repr, "read double",     IR_CMD_READ,  dest_reg,         NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#define IR_EMIT_CMD_CMP_DOUBLE_RM(dest_reg, src_reg, src_mem_disp)    IntReprEmit (interm_repr, "cmp double",      IR_CMD_CMP,   dest_reg,         NAN, IR_POISON,     false, src_reg,          NAN,     src_mem_disp, true,  NULL, IR_POISON, false)

#define IR_EMIT_CMD_PRINT_DOUBLE(src_reg)                             IntReprEmit (interm_repr, "print double",    IR_CMD_PRINT, IR_OP_NO_OPERAND, NAN, IR_POISON,     false, src_reg,          NAN,     IR_POISON,    false, NULL, IR_POISON, false)

#endif