# Backend часть компилятора Rap language, преобразующая AST в код ассемблера архитектуры x86-64

Сергей Кулагин, 1 курс ФРКТ МФТИ

## Сборка и запуск

### Для сборки:

1. Клонируйте репозиторий: 
    ```console
    $ git clone https://github.com/metaironia/CompilerBackend
    ```

2. Перейдите в папку с исходниками:

    ```console
    $ cd CompilerBackend/src
    ```

3. Соберите backend-часть:
    ```console
    $ make
    ```

### Для запуска:

```console
$ compiler_backend <input_file> <output_file>
```

## Описание репозитория

В этом репозитории содержится модель backend части компилятора языка Rap language. Подробнее про Rap language можно узнать по ссылке: https://github.com/metaironia/MyProgrammingLanguage.

Работу этой модели можно описать так:

1. AST (Abstract Syntax Tree) преобразуется в IR (Intermediate Representation);

2. IR преобразуется в код NASM x86-64.

> [!IMPORTANT] 
> Код NASM x86-64, генерируемый этой моделью, будет работать **только** под Win64.

## Преобразование AST в IR

IR - промежуточное представление исходного кода. Преимущество IR перед AST в том, что это линейное представление (например, оно легко представляется в виде массива). Это облегчает оптимизацию кода, поскольку в таком случае из IR ячейки можно свободно удалять и добавлять (с древовидной структурой было бы не все так просто).

Преобразование AST в IR в этой модели backend части компилятора Rap language производится с помощью рекурсивного спуска по AST.

## Реализация IR

Реализация структуры IR такая:

```c
struct IntRepr {

    IntReprCell *cell;     // указатель на первую ячейку IR
    int64_t      size;     // количество занятых ячеек в IR
    int64_t      capacity; // количество ячеек, которое может вместить IR
};
```

Реализация структуры ячейки IR выглядит так:

```c
struct IntReprCell {

    const char  *cmd_name;         // имя команды
    CommandType  cmd_type;         // тип команды

    IntReprOperand dest_operand;   // операнд назначения
    IntReprOperand src_operand;    // операнд-источник

    IntReprCell *jump_ptr;         // указатель на ячейку IR для прыжка
    int64_t      jump_cell_index;  // номер ячейки IR для прыжка
    int64_t      jump_addr;        // адрес команды в x86-64 для прыжка
    bool         is_jumpable_here; // истина, если на эту ячейку выполняется прыжок, иначе ложь
    bool         need_patch;       // истина, если ячейке требуется патч, иначе ложь
};
```

`CommandType` - это enum, содержащий в себе доступные к использованию типы команд. Они приведены в таблице ниже:

| Тип команды в ячейке IR (CommandType) | Аналогичная команда в intel-syntax x86-64 |
| :---------------------: | :----------: |
| `IR_CMD_ADD` | add |
| `IR_CMD_ADD_DOUBLE` | addsd |
| `IR_CMD_SUB_DOUBLE` | subsd |
| `IR_CMD_MUL_DOUBLE` | mulsd |
| `IR_CMD_DIV_DOUBLE` | divsd |
| `IR_CMD_PUSH` | push |
| `IR_CMD_POP` | pop |
| `IR_CMD_MOV_DOUBLE` | movsd |
| `IR_CMD_MOV` | mov |
| `IR_CMD_CMP` | comisd |
| `IR_CMD_JMP` | jmp |
| `IR_CMD_JMP_EQUAL` | je |
| `IR_CMD_JMP_NOT_EQUAL` | jne |
| `IR_CMD_JMP_GREATER_EQ` | jge |
| `IR_CMD_JMP_LESS_EQ` | jl |
| `IR_CMD_JMP_GREATER` | jg |
| `IR_CMD_JMP_LESS` | jl |
| `IR_CMD_FUNC_CALL` | call |
| `IR_CMD_RET` | ret |
| `IR_CMD_READ` | - |
| `IR_CMD_PRINT` | - |
| `IR_CMD_EXIT` | - |
| `IR_CMD_FUNC_START` | - |
| `IR_CMD_FUNC_END` | - |
| `IR_CMD_COMMENT` | - |  

`IR_CMD_READ` читает значение из консоли в `IR_OP_REG_XMM4`. `IR_CMD_PRINT` печатает значение, которое находится в `IR_OP_REG_XMM4`. `IR_CMD_EXIT` завершает работу программы.

Каждое объявление функции должно начинаться ячейкой с `IR_CMD_FUNC_START`, и поле `cmd_name` этой ячейки должно содержать имя функции. Помимо этого, каждое объявление функции должно заканчиваться ячейкой с `IR_CMD_FUNC_END`.

`IR_CMD_COMMENT` делает ячейку комментарием. В таком случае поле `cmd_name` содержит сам комментарий.

Для удобства записи этих команд в ячейки IR был разработан DSL ([ir_dsl.h](src\ASTtoIR\ir_dsl.h)).

`IntReprOperand` - это структура с полной информацией об операнде (в качестве аналогии, операндом в NASM x86-64 может быть rax, [rcx] и т.д.)

```c
struct IntReprOperand {

    OperandType  operand_type;       // тип операнда     
    double       operand_value;      // поле используется, если операнд - непосредственное значение
    ValueType    operand_value_type; // тип непосредственного значения операнда 
    int64_t      operand_disp;       // поле используется, если типом операнда является "память" 
    bool         is_operand_mem;     // истина, если типом операнда является "память" "
};
```

`OperandType` - это enum, который содержит все типы возможных операндов. Типы операндов приведены в таблице ниже:

| Тип операнды в ячейке IR (OperandType) | Аналогичный операнд в intel-syntax x86-64 |
| :---------------------: | :----------: |
| `IR_OP_IMMEDIATE` | число |
| `IR_OP_NO_OPERAND` | - |
| `IR_OP_REG_RAX` | rax |
| `IR_OP_REG_RBX` | rbx |
| `IR_OP_REG_RCX` | rcx |
| `IR_OP_REG_RDX` | rdx |
| `IR_OP_REG_R10` | r10 |
| `IR_OP_REG_R11` | r11 |
| `IR_OP_REG_R12` | r12 |
| `IR_OP_REG_R13` | r13 |
| `IR_OP_REG_R14` | r14 |
| `IR_OP_REG_RBP` | rbp |
| `IR_OP_REG_RSP` | rsp |
| `IR_OP_REG_XMM0` | xmm0 |
| `IR_OP_REG_XMM1` | xmm1 |
| `IR_OP_REG_XMM2` | xmm2 |
| `IR_OP_REG_XMM3` | xmm3 |
| `IR_OP_REG_XMM4` | xmm4 |

`IR_OP_NO_OPERAND` используется, если команда не имеет данного (dest и/или src) операнда.

`ValueType` - это enum, в котором содержится тип числа. Всего доступно 3 типа числа: `VALUE_TYPE_INT`, `VALUE_TYPE_DOUBLE` и `NOT_A_VALUE`.

`VALUE_TYPE_INT` и `VALUE_TYPE_DOUBLE` показывают, что число является целочисленным и вещественным соответственно.

`NOT_A_VALUE` используется, если операнд (src и/или dest) не является числом (не является `IR_OP_IMMEDIATE`).

## Преобразование IR в x86-64

Чтобы преобразовать IR в код на языке NASM x86-64, производится один линейный проход по всем ячейкам IR, начиная с нулевой ячейки.

Ячейка IR преобразуется в:
* ассемблерный комментарий, если команда в ячейке - это `IR_CMD_COMMENT`;
* текст поля `cmd_name` ячейки и двоеточие, если команда в ячейке - это `IR_CMD_FUNC_START`;
* `ret`, если команда в ячейке - это `IR_CMD_FUNC_END`;
* `call _MyRead`, если команда в ячейке - это `IR_CMD_READ`;
* `call _MyPrint`, если команда в ячейке - это `IR_CMD_PRINT`;
* `call _MyExit`, если команда в ячейке - это `IR_CMD_EXIT`;
* аналогичную ассемблерную команду, приведенную в таблице с описанием `CommandType`, для неперечисленных выше команд в ячейке IR.

Про функции `_MyRead`, `_MyPrint` и `_MyExit` речь пойдет в следующем разделе.

Так как в NASM нельзя использовать вещественные числа в командах, возникает проблема преобразования таких чисел на язык ассемблера.

Проблема была решена таким образом. На том месте, где должно быть число, находится адресация по метке, которая содержит нужное число через db. Эта метка находится в секции data. 

Пример решения проблемы для вещественного числа 1.5, которое нужно переместить в регистр xmm0: 

```asm
section .data

    ; какой-то код

    movsd xmm0, [rel _DOUBLE__1_5]

    ; какой-то код

section .data
    _DOUBLE__1_5: dq 1.5
```

## Стандартная библиотека 

В ассемблере не предусмотрено функций чтения и печати вещественного числа. В связи с этим были разработаны функции `_MyRead` и `_MyPrint` соответственно.

`_MyRead` читает одно вещественное число с консоли, после чего кладет его в нижнюю половину регистра xmm4.

`_MyPrint` печатает вещественное число, находящееся в нижней половине регистра xmm4, в консоль.

Также была разработана функция `_MyExit`, которая завершает работу программы.

Все эти функции находятся в файле [mystdlib.asm](src\mystdlib\mystdlib.asm).

> [!CAUTION]
> `_MyRead`, `_MyPrint` и `_MyExit` из этого файла используют 64-битные функции из [libkernel32.a](src\mystdlib\libkernel32.a). Это означает, что они **не** будут работать под Linux и Win32, а будут работать только под Win64.

[mystdlib.asm](src\mystdlib\mystdlib.asm) будем называть стандартной библиотекой языка Rap language для Win64.

## Получение исполняемого exe-файла из кода на NASM

Чтобы получить исполняемый exe-файл из файла с кодом на NASM, полученным в результате работы этой модели backend части компилятора, из корневой папки репозитория введите в консоль:

```console
$ cd CompilerBackend/src
$ nasm "file_name" -fwin64 -o "file_name.o"
$ ld "file_name.o" -o "file_name.exe" mystdlib/libkernel32.a
```

Здесь `file_name` - это имя вашего NASM-файла. 

