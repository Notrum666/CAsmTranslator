.386
.model flat, stdcall
.data
a dword ?
.code
main proc

push 1
pop eax
mov a, eax

push 5
pop ebx
mov eax, a
add eax, ebx
mov a, eax

ret
main endp
end main