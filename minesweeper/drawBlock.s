	.arch msp430g2553
	.p2align 1,0
	.text

drawBlockSwitch:
	.word SW_UNMARKED
	.word SW_DEFAULT
	.word SW_FLAGGED
	.word SW_DEFAULT
	.word SW_QUESTION
	.word SW_DEFAULT
	.word SW_DEFAULT
	.word SW_DEFAULT
	.word SW_EXPOSED

	.global drawBlock
drawBlock:
	sub #2, r1
	mov.b r12, 0(r1) 	; x
	mov.b r13, 1(r1)	; y
	call #getPosition
	and.b #14, r12
	cmp.b #9, r12
	jhs SW_DEFAULT
	add r12, r12
	mov drawBlockSwitch(r12), r0
SW_UNMARKED:
SW_DEFAULT:
	mov #uncheckedSquares, r14 ; sprite
	jmp SW_END
SW_FLAGGED:
	mov #uncheckedSquares, r14 ; sprite
	add #18, r14
	jmp SW_END
SW_QUESTION:
	mov #uncheckedSquares, r14 ; sprite
	add #18, r14
	jmp SW_END
SW_EXPOSED:
	mov.b 0(r1), r12	; x
	mov.b 1(r1), r13	; y
	call #numNeighboringMines
	mov #emptySquares, r14
	;; Don't know how to call the multiply routine
	;; A loop should be fine
SW_EXPOSED_LOOP:
	cmp #0, r12
	jeq SW_EXPOSED_LOOP_END
	add #18, r14
	sub #1, r12
	jmp SW_EXPOSED_LOOP
SW_EXPOSED_LOOP_END:
SW_END:
	mov.b 0(r1), r12	; x
	mov.b 1(r1), r13	; y
	add #2, r1

	;; x *= 8
	add.b r12, r12
	add.b r12, r12
	add.b r12, r12

	;; y *= 8
	add.b r13, r13
	add.b r13, r13
	add.b r13, r13

	;; y += 16
	add.b #16, r13

	call #drawSprite8x8
	ret
