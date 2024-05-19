; 64-bit standart lib for Windows 

extern GetStdHandle  ; kernel32.dll
extern WriteConsoleA ; kernel32.dll

global _MyPrint

section .text

PRINT_BUFFER_CAPACITY equ 4d
INT_BUFFER_CAPACITY   equ 20d
PRINT_PRECISION       equ 1000d

;------------------------------------------------
; _MyPrint (prints double number to 3 decimal places)
; Entry: low xmm4 quadword = value to print
; Return: number in console
; Destructs: rax
;------------------------------------------------

_MyPrint:   movsd xmm6, xmm4                 ; xmm6 is non-volatile register

            push rbx                         ; 
            push rdi                         ; saving non-volatile registers MyPrintf destructs
            push rsi                         ; 

            mov rcx, -11                     ; STD_OUTPUT_HANDLE = -11
            call GetStdHandle                ; stdout = GetStdHandle (-11)           

            mov rdi, rax                     ; rdi = stdout
            lea rsi, [rel print_buffer]      ; rsi = addr to buffer
            xor r10, r10                     ; size of printbuffer = 0 

            roundsd xmm7, xmm6, 0b1011       ; xmm7 = round toward zero

            cvtsd2si rbx, xmm7
            call _PrintDec                   ; prints integer part of number

            mov al, '.'                 
            call _BufferCharAdd              ; add decimal dot to buffer

            subsd xmm6, xmm7

            mov rax, PRINT_PRECISION
            cvtsi2sd xmm7, rax               ; xmm7 = PRINT_PRECISION

            mulsd xmm6, xmm7                 ; xmm6 = 3 decimals digits of number
            cvtsd2si rbx, xmm6               ; rbx = 3-digit number

            mov eax, ebx
            call _AbsVal
            mov ebx, eax                     ; abs (ebx)         

            call _PrintDec                   ; prints 3 decimal digits

            test r10, r10                    ; if buffer size is 0
            je _EndPrint

            call _CmdFlush                   ; calling cmd flush if the buffer is not empty   

_EndPrint:  pop rsi                          ; 
            pop rdi                          ; popping non-volatile registers    
            pop rbx                          ;

            ret

;------------------------------------------------
; _PrintDec (prints decimal number)
; Entry: rbx = number to decimal print
; Return: -
; Destructs: rax, rcx
; Note: number should be 32-bit
;------------------------------------------------

_PrintDec:      push rdx                    ; saving rdx because div destructs it
                push rcx                    ; saving rcx

                mov eax, ebx                ; eax = number to dec print

                rol ebx, 1d                 ; sign bit is least bit now
                and bl, 1h                  ; bl = 1 if signed

                test bl, bl                 ; bl = sign of num
                je _NotSigned

                mov rbx, rax                ; saving al
                mov al, '-'                 
                call _BufferCharAdd
                mov rax, rbx                ; restoring al

                not eax                     ;
                inc eax                     ; abs of signed num

_NotSigned:     xor rcx, rcx                ; symbol counter

                mov r9, 10d          

                lea rbx, [rel buffer_to_int]

_DecNextSymbol: xor rdx, rdx                ; rdx:rax = signed number

                div r9                      ; rdx = remainder, rax = result

                inc rbx                     ; rbx = addr to empty cell in buffer to int               
                add dl, '0'                 ; dl = ascii code of current symbol
                mov [rbx], dl               ; add symbol to buffer

                inc rcx

                test rax, rax
                jne _DecNextSymbol

_PrintBufFill:  mov al, [rbx]
                dec rbx                     ; dec pos in buffer to int 

                call _BufferCharAdd

                loop _PrintBufFill

                pop rcx                     ; popping rcx
                pop rdx                     ; popping rdx

                ret
                
;------------------------------------------------
; _BufferCharAdd
; Note: if buffer is full, _BufferCharAdd flushes buffer to console
; Entry: al = symbol
; Assumes: rsi = buffer addr, rdx = pos in printable string
; Return: -
;------------------------------------------------

_BufferCharAdd: mov [rsi], al                    ; filling buffer

                inc r10                          ; buffer_size++
                inc rsi                          ; inc pos in buffer

                cmp r10, PRINT_BUFFER_CAPACITY                        
                jne _NoFlush

                push rcx                         ; saving rest str length
                call _CmdFlush
                pop rcx                          ; popping rest str length

_NoFlush:       ret

;------------------------------------------------
; _CmdFlush (prints buffer to cmd)
; Entry: rdi = stdout 
; Return: printed buffer 
; Destructs: rcx, rdx, r8, r9
;------------------------------------------------

_CmdFlush:      mov rcx, rdi                     ; rcx = stdout
                mov rdx, print_buffer            ; rdx = print_buffer addr
                mov r8, r10                      ; r8 = buffer size
                xor r9, r9                       ; r9 = 0 (offset to char ptr) 
                push qword 0                     ; reserved         

                call WriteConsoleA               ; WriteConsole (stdout, print_buffer, buffer_size, NULL, 0)
                add rsp, 8                       ; clears the arguments stored in stack 

                xor r10, r10                     ; buffer_size = 0
                lea rsi, [rel print_buffer]      ; rsi = addr to buffer

                ret      

;------------------------------------------------
; _AbsVal
; Entry: eax = number
; Return: eax = abs of number
; Destructs: ecx
;------------------------------------------------

_AbsVal:    mov ecx, eax                     ; ecx = number

            rol ecx, 1d                      ; sign bit is least bit now
            and cl, 1h                       ; al = 1 if signed

            test cl, cl                      ; al = sign of num
            je _AbsEnd
            
            not eax                          ;
            inc eax                          ; abs of signed num         

_AbsEnd:    ret

; _MyExit:
; _MyRead:

section .data

                                         db "PRINT<<<"          ; buffer start
print_buffer times PRINT_BUFFER_CAPACITY db 0
                                         db ">>>"               ; buffer end

hex_letters                              db "0123456789ABCDEF"

                                         db "INT<<<"            ; buffer start
buffer_to_int times INT_BUFFER_CAPACITY  db 0
                                         db ">>>"               ; buffer end

