mov ESI, 4 ; 	mov Eax, 4
mul 0 ; 	mul 0
mov EAX, ESI ; 	mov temp_13, Eax
mov EAX, EAX ; 	mov temp_12, temp_13
push EAX ; 	push temp_12
call malloc ; 	call malloc
mov EAX, EDX ; 	mov temp_2, temp_14
mov EBX, EAX ; 	mov temp_15, temp_2
mov EAX, 0 ; 	mov temp_17, 0
mov EAX, EAX ; 	mov temp_16, temp_17
mov ESI, 4 ; 	mov Eax, 4
mul 0 ; 	mul 0
mov ECX, ESI ; 	mov temp_19, Eax
mov ECX, ECX ; 	mov temp_18, temp_19
push ECX ; 	push temp_18
push EAX ; 	push temp_16
push EBX ; 	push temp_15
call memset ; 	call memset
mov EAX, EDX ; 	mov temp_1, temp_20
mov EBX, EAX ; 	mov temp_21, temp_1
mov EAX, 10 ; 	mov temp_23, 10
mov EAX, EAX ; 	mov temp_22, temp_23
push EAX ; 	push temp_22
push EBX ; 	push temp_21
call ComputeFac ; 	call ComputeFac
mov EAX, EDX ; 	mov temp_0, temp_24
mov EAX, EAX ; 	mov temp_25, temp_0
push EAX ; 	push temp_25
call print ; 	call print
