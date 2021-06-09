.386
.model flat, stdcall
.data
a dword ?
.code
main proc
push 5
pop eax
mov a, eax


ret
main endp
end main