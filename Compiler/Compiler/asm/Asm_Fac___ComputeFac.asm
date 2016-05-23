mov EAX, ECX ; 	mov Eax, Fac___ComputeFac___framePointer
add 4 ; 	add 4
mov EAX, EAX ; 	mov temp_3, Eax
mov ECX, [EAX] ; 	mov temp_5, [temp_3]
mov EAX, 1 ; 	mov temp_6, 1
cmp ECX, EAX ; 	cmp temp_5, temp_6
jle label_3 ; 	jle label_3
label_4:
mov EAX, 2 ; 	mov temp_7, 2
mov [ECX+8], EAX ; 	mov [Fac___ComputeFac___framePointer+8], temp_7
label_5:
mov EAX, ECX ; 	mov Eax, Fac___ComputeFac___framePointer
add 8 ; 	add 8
mov EAX, EAX ; 	mov temp_8, Eax
mov EAX, [EAX] ; 	mov temp_10, [temp_8]
mov EAX, EAX ; 	mov Fac___ComputeFac___returnValue, temp_10
jmp DoneLabel ; 	jmp DoneLabel
label_3:
mov EAX, 1 ; 	mov temp_11, 1
mov [ECX+8], EAX ; 	mov [Fac___ComputeFac___framePointer+8], temp_11
