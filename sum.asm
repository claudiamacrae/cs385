	mov		r2, #0 @start sum at 0
	mov		r3, #0
1:
	ldr		r4, [r0]
	ldr  	r5, [r0, #4]
	add		r3, #2
	add		r6, r4, r5 @add elements
	sub		r7, r4, r5	@subtract elements
	add		r2, mul r6, r7
	cmp		r3, r1
	ble		1b
mov r0, r2
bx	lr