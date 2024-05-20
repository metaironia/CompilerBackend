DEF_IR_CMD      (IR_CMD_ADD,            "add")
DEF_IR_CMD      (IR_CMD_ADD_DOUBLE,     "addsd")
DEF_IR_CMD      (IR_CMD_SUB_DOUBLE,     "subsd")
DEF_IR_CMD      (IR_CMD_MUL_DOUBLE,     "mulsd")
DEF_IR_CMD      (IR_CMD_DIV_DOUBLE,     "divsd")
DEF_IR_CMD      (IR_CMD_PUSH,           "push")
DEF_IR_CMD      (IR_CMD_POP,            "pop")
DEF_IR_CMD      (IR_CMD_MOV_DOUBLE,     "movsd")
DEF_IR_CMD      (IR_CMD_MOV,            "mov")
DEF_IR_CMD      (IR_CMD_READ,           "call _MyRead")
DEF_IR_CMD      (IR_CMD_CMP,            "comisd")
DEF_IR_CMD      (IR_CMD_PRINT,          "call _MyPrint")
DEF_IR_CMD      (IR_CMD_RET,            "ret")
DEF_IR_CMD      (IR_CMD_EXIT,           "call _MyExit")
DEF_IR_CMD_JMP  (IR_CMD_JMP,            "jmp")
DEF_IR_CMD_JMP  (IR_CMD_JMP_EQUAL,      "je")
DEF_IR_CMD_JMP  (IR_CMD_JMP_NOT_EQUAL,  "jne")
DEF_IR_CMD_JMP  (IR_CMD_JMP_GREATER_EQ, "jge")
DEF_IR_CMD_JMP  (IR_CMD_JMP_LESS_EQ,    "jle")
DEF_IR_CMD_COMM (IR_CMD_COMMENT)
DEF_IR_CMD_FUNC (IR_CMD_FUNC_CALL)
DEF_IR_CMD_FUNC (IR_CMD_FUNC_START)
DEF_IR_CMD_FUNC (IR_CMD_FUNC_END)