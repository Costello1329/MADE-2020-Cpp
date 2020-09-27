.globl count_det

count_det:
.fnstart

mov r1, $0

ldr r2, [r0, $16]
ldr r3, [r0, $32]
mul r6, r2, r3
ldr r4, [r0, $20]
ldr r5, [r0, $28]
mul r7, r4, r5
sub r2, r6, r7

ldr r8, [r0]
mul r8, r2, r8
add r1, r1, r8

ldr r2, [r0, $12]
ldr r3, [r0, $32]
mul r6, r2, r3
ldr r4, [r0, $24]
ldr r5, [r0, $20]
mul r7, r4, r5
sub r2, r6, r7

ldr r8, [r0, $4]
mul r8, r2, r8
sub r1, r1, r8

ldr r2, [r0, $12]
ldr r3, [r0, $28]
mul r6, r2, r3
ldr r4, [r0, $24]
ldr r5, [r0, $16]
mul r7, r4, r5
sub r2, r6, r7

ldr r8, [r0, $8]
mul r8, r2, r8
add r1, r1, r8

mov r0, r1
bx lr
.fnend
