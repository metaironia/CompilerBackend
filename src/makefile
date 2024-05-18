.PHONY: all clean
CC=g++
CFLAGS= -O2
WARNINGS=-Wshadow -Winit-self -Wcast-align -Wundef -Wfloat-equal -Winline -Wredundant-decls \
 	 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default \
	 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy \
	 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers \
	 -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
	 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE 
SOURCES= main.cpp backend_input.cpp \
	 ASTtoIR/ast_to_ir.cpp ASTtoIR/ir_log.cpp \
	 IRtoASM/ir_to_asm.cpp \
	 ../lib/tree/tree_func.cpp ../lib/tree/tree_log.cpp \
	 ../lib/tree/math_tree/math_tree_func.cpp ../lib/tree/math_tree/math_operation.cpp \
       	 ../lib/oneginlib/functions_for_input.cpp \
	 ../lib/oneginlib/functions_for_output.cpp \
		 		 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=compiler_backend

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(WARNINGS) $^ -o $@

%.o : %.cpp
	$(CC) -c $(CFLAGS) $(WARNINGS) $< -o $@

clean:
	 rm -f *.o compiler_backend.exe
	 rm -f ASTtoIR/*.o
	 rm -f ../lib/tree/*.o
	 rm -f ../lib/tree/math_tree/*.o
	 rm -f ../lib/oneginlib/*.o
	 rm -f ../lib/mystacklib/*.o

rebuild: clean all
