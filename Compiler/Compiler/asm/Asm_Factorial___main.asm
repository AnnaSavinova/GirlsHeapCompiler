prolog beginFactorial___main:

push Factorial___main___framePointer;
mov Factorial___main___framePointer Factorial___main___thisPointer;
sub Factorial___main___thisPointer 0;
push EAX;
push EBX;
push ECX;
push EDX;
push ESI;
push EDI;
prolog end:

mov EAX, 4
;
mul 0
;
mov temp_33, EAX
;
mov temp_32, temp_33
;
push temp_32
;
call malloc
;
mov temp_5, temp_34
;
mov temp_35, temp_5
;
mov temp_37, 0
;
mov temp_36, temp_37
;
mov EAX, 4
;
mul 0
;
mov temp_39, EAX
;
mov temp_38, temp_39
;
push temp_38
;
push temp_36
;
push temp_35
;
call memset
;
mov temp_4, temp_40
;
mov temp_41, temp_4
;
mov temp_43, 10
;
mov temp_42, temp_43
;
push temp_42
;
push temp_41
;
call ComputeFac
;
mov temp_3, temp_44
;
mov temp_45, temp_3
;
push temp_45
;
call print
;
epilog begin:

pop EDI;
pop ESI;
pop EDX;
pop ECX;
pop EBX;
pop EAX;
add Factorial___main___thisPointer 0;
pop Factorial___main___framePointer 0;
ret;
epilog end:

