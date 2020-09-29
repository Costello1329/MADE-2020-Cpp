.globl count_det

count_det:
.fnstart

push {r5}
push {r6}

mov r1, $0

ldr r2, [r0, $16]
ldr r3, [r0, $32]
mul r6, r2, r3
ldr r4, [r0, $20]
ldr r5, [r0, $28]
mul r3, r4, r5
sub r2, r6, r3

ldr r3, [r0]
mul r3, r2, r3
add r1, r1, r3

ldr r2, [r0, $12]
ldr r3, [r0, $32]
mul r6, r2, r3
ldr r4, [r0, $24]
ldr r5, [r0, $20]
mul r3, r4, r5
sub r2, r6, r3

ldr r3, [r0, $4]
mul r3, r2, r3
sub r1, r1, r3

ldr r2, [r0, $12]
ldr r3, [r0, $28]
mul r6, r2, r3
ldr r4, [r0, $24]
ldr r5, [r0, $16]
mul r3, r4, r5
sub r2, r6, r3

ldr r3, [r0, $8]
mul r3, r2, r3
add r1, r1, r3

mov r0, r1

pop {r6}
pop {r5}

bx lr
.fnend
