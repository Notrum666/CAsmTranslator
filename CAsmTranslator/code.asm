.386
.model flat, stdcall
.data
a dword ?
.code
main proc

push 1
pop eax
mov a, eax

push 3
pop ebx
mov eax, a
add eax, ebx
mov a, eax
push eax
pop ebx
mov eax, a
add eax, ebx
mov a, eax

ret
main endp
end main