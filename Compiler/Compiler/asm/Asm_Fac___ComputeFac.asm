mov EAX, Fac___ComputeFac___framePointer;
add 4;
mov temp_6, EAX;
mov temp_8, [temp_6];
mov temp_9, 1;
cmp temp_8, temp_9;
jle label_3;
label_4:

mov EAX, Fac___ComputeFac___framePointer;
add 8;
mov temp_10, EAX;
mov temp_12, [temp_10];
mov temp_2, temp_12;
mov EAX, Fac___ComputeFac___framePointer;
add 4;
mov temp_13, EAX;
mov temp_15, [temp_13];
mov temp_1, temp_15;
mov EAX, Fac___ComputeFac___framePointer;
add 0;
mov temp_17, EAX;
mov temp_19, [temp_17];
mov temp_16, temp_19;
mov EAX, Fac___ComputeFac___framePointer;
add 4;
mov temp_22, EAX;
mov temp_24, [temp_22];
mov EAX, temp_24;
sub 1;
mov temp_21, EAX;
mov temp_20, temp_21;
push temp_20;
push temp_16;
call ComputeFac;
mov temp_0, temp_25;
mov temp_27, temp_0;
mov EAX, temp_1;
mul temp_27;
mov temp_26, EAX;
mov temp_2, temp_26;
label_5:

mov EAX, Fac___ComputeFac___framePointer;
add 8;
mov temp_28, EAX;
mov temp_30, [temp_28];
mov Fac___ComputeFac___returnValue, temp_30;
jmp DoneLabel;
label_3:

mov temp_31, 1;
mov [Fac___ComputeFac___framePointer+8], temp_31;