.386
.model flat, stdcall
option casemap :none
include \masm32\include\windows.inc
include \masm32\include\masm32.inc
include \masm32\include\msvcrt.inc
include \masm32\macros\macros.asm
includelib \masm32\lib\masm32.lib
includelib \masm32\lib\msvcrt.lib

.data
tpt db '%d ',0
a1 dd 0
a2 dd 0
a3 dd 0
a dd 0
i dd 0


.code
start :
mov eax, 1
mov a1, eax

mov eax, 20
mov a2, eax

mov eax, 20
mov a3, eax

b_1 equ 10

mov eax, 0
mov a, eax

push a1

push a2

pop eax
pop ebx
mov i, ebx
for_begin_0:
mov edx, i
mov eax, a2
cmp edx, eax
jg for_end_0

push 5

push 7

push 8

push 16

push 4

pop ecx
pop eax
xor ebx, ebx
cdq
div ecx
push eax


pop eax
pop ebx
sub ebx, eax
push ebx


pop eax
pop ebx
imul ebx, eax
push ebx


push 2

push 5

push 2

push 43

pop eax
pop ebx
add ebx, eax
push ebx


pop eax
pop ebx
imul ebx, eax
push ebx


pop eax
pop ebx
imul ebx, eax
push ebx


pop eax
pop ebx
sub ebx, eax
push ebx


pop eax
pop ebx
add ebx, eax
push ebx

pop eax
mov a, eax

push a

pop eax
invoke  crt_printf, ADDR tpt, eax

add i, 1
jmp for_begin_0
for_end_0:



end start