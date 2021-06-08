.386
.model flat, stdcall
.data
a dword ?
.code
main proc

while0:
push 0
pop eax
cmp eax, 0
jz while_end0
jmp while0
while_end0:

ret
main endp
end main