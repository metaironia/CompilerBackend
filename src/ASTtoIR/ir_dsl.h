#ifndef IR_DSL_H
#define IR_DSL_H


#define IR_CELL_                                                      (interm_repr -> cell)

#define IR_SIZE_                                                      (interm_repr -> size)

#define IR_CAPACITY_                                                  (interm_repr -> capacity)

#define IR_TOP_CELL_                                                  (IR_CELL_ + IR_SIZE_)

#define IR_EMIT_CMD_ADD_RI(dest_reg, imm_val)                         IntReprEmit (interm_repr, "add RI",         IR_CMD_ADD,        dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_IMMEDIATE,  VALUE_TYPE_INT,    imm_val, IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_ADD_DOUBLE_RR(dest_reg, src_reg)                  IntReprEmit (interm_repr, "add double RR",  IR_CMD_ADD_DOUBLE, dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)                  
 
#define IR_EMIT_CMD_SUB_DOUBLE_RR(dest_reg, src_reg)                  IntReprEmit (interm_repr, "sub double RR",  IR_CMD_SUB_DOUBLE, dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_MUL_DOUBLE_RR(dest_reg, src_reg)                  IntReprEmit (interm_repr, "mul double RR",  IR_CMD_MUL_DOUBLE, dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_DIV_DOUBLE_RR(dest_reg, src_reg)                  IntReprEmit (interm_repr, "div double RR",  IR_CMD_DIV_DOUBLE, dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_PUSH(src_reg)                                     IntReprEmit (interm_repr, "push",           IR_CMD_PUSH,       IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_POP(src_reg)                                      IntReprEmit (interm_repr, "pop",            IR_CMD_POP,        IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_MOVE_RM(dest_reg, src_reg, src_mem_disp)          IntReprEmit (interm_repr, "move RM",        IR_CMD_MOV,        dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     src_mem_disp, true,  NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_MOVE_RR(dest_reg, src_reg)                        IntReprEmit (interm_repr, "move RR",        IR_CMD_MOV,        dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_MOVE_DOUBLE_MR(dest_reg, dest_mem_disp, src_reg)  IntReprEmit (interm_repr, "move double MR", IR_CMD_MOV_DOUBLE, dest_reg,         NOT_A_VALUE, NAN, dest_mem_disp, true,  src_reg,          NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_MOVE_DOUBLE_RM(dest_reg, src_reg, src_mem_disp)   IntReprEmit (interm_repr, "move double RM", IR_CMD_MOV_DOUBLE, dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     src_mem_disp, true,  NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_MOVE_DOUBLE_MI(dest_reg, dest_mem_disp, imm_val)  IntReprEmit (interm_repr, "move double MI", IR_CMD_MOV_DOUBLE, dest_reg,         NOT_A_VALUE, NAN, dest_mem_disp, true,  IR_OP_IMMEDIATE,  VALUE_TYPE_DOUBLE, imm_val, IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_MOVE_DOUBLE_RI(dest_reg, imm_val)                 IntReprEmit (interm_repr, "move double RI", IR_CMD_MOV_DOUBLE, dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_IMMEDIATE,  VALUE_TYPE_DOUBLE, imm_val, IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_MOVE_DOUBLE_RR(dest_reg, src_reg)                 IntReprEmit (interm_repr, "move double RR", IR_CMD_MOV_DOUBLE, dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     false, NULL, IR_POISON, IR_POISON, false)

#define IR_EMIT_CMD_READ_DOUBLE_                                      IntReprEmit (interm_repr, "read double",    IR_CMD_READ,       IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)

#define IR_EMIT_CMD_CMP_DOUBLE_RM(dest_reg, src_reg, src_mem_disp)    IntReprEmit (interm_repr, "cmp double",     IR_CMD_CMP,        dest_reg,         NOT_A_VALUE, NAN, IR_POISON,     false, src_reg,          NOT_A_VALUE,       NAN,     src_mem_disp, true,  NULL, IR_POISON, IR_POISON, false)

#define IR_EMIT_CMD_PRINT_DOUBLE_                                     IntReprEmit (interm_repr, "print double",   IR_CMD_PRINT,      IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)

#define IR_EMIT_CMD_FUNC_START(func_name)                             IntReprEmit (interm_repr, func_name,        IR_CMD_FUNC_START, IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)

#define IR_EMIT_CMD_FUNC_END_                                         IntReprEmit (interm_repr, "func end",       IR_CMD_FUNC_END,   IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)

#define IR_EMIT_CMD_RET_                                              IntReprEmit (interm_repr, "ret",            IR_CMD_RET,        IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)

#define IR_EMIT_CMD_FUNC_CALL(func_name)                              IntReprEmit (interm_repr, func_name,        IR_CMD_FUNC_CALL,  IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)

#define IR_EMIT_CMD_EXIT_                                             IntReprEmit (interm_repr, "exit program",   IR_CMD_EXIT,       IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)
 
#define IR_EMIT_CMD_JUMP_EQUAL_                                       IntReprEmit (interm_repr, "jump equal",     IR_CMD_JMP_EQUAL,  IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, true)
 
#define IR_EMIT_CMD_JUMP_                                             IntReprEmit (interm_repr, "jump",           IR_CMD_JMP,        IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, true)
 
#define IR_EMIT_COMMENT(comment)                                      IntReprEmit (interm_repr, comment,          IR_CMD_COMMENT,    IR_OP_NO_OPERAND, NOT_A_VALUE, NAN, IR_POISON,     false, IR_OP_NO_OPERAND, NOT_A_VALUE,       NAN,     IR_POISON,    false, NULL, IR_POISON, IR_POISON, false)

#define IR_PATCH_CMD_JUMP(cell_index_to_patch, cell_index_to_jump)    {                                                                                          \
                                                                          (IR_CELL_ + cell_index_to_patch) -> jump_ptr        = IR_CELL_ + cell_index_to_jump;   \
                                                                          (IR_CELL_ + cell_index_to_patch) -> jump_cell_index = cell_index_to_jump;              \
                                                                      }

#define IR_ACTIVATE_JUMPABLE_STATE(cell_index_to_activate)            {                                                                                          \
                                                                          (IR_CELL_ + cell_index_to_activate) -> is_jumpable_here = true;                        \
                                                                      }                                      

#endif