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

mov EAX, 4;
mul 0;
mov temp_32, EAX;
mov temp_31, temp_32;
mov EAX, 4;
mul 0;
mov temp_34, EAX;
mov temp_33, temp_34;
push temp_33;
push temp_31;
call malloc;
mov temp_1, EAX;
mov temp_35, temp_1;
mov temp_37, 0;
mov temp_36, temp_37;
push temp_36;
push temp_35;
call memset;
mov temp_38, temp_1;
mov temp_40, 10;
mov temp_39, temp_40;
push temp_39;
push temp_38;
call ComputeFac;
mov temp_5, EAX;
mov temp_41, temp_5;
push temp_41;
call print;
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

