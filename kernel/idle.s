.global	pattern
pattern:
	.word	0x1000
	.word	0x2000
	.word	0x100
	.word	0x1
	.word	0x2
	.word	0x4
	.word	0x8
	.word	0x800
.global	idle_main
.text
idle_main:
	subui	$sp, $sp, 4
	sw	$6, 0($sp)
	sw	$7, 1($sp)
	sw	$12, 2($sp)
	sw	$13, 3($sp)
	addu	$6, $0, $0
	addu	$7, $0, $0
	j	L.7
L.6:
	lhi	$13, 0x7
	ori	$13, $13, 0x3004
	sw	$0, 0($13)
	lhi	$13, 0x7
	ori	$13, $13, 0x3002
	lw	$12, pattern($6)
	srai	$12, $12, 8
	sw	$12, 0($13)
	lhi	$13, 0x7
	ori	$13, $13, 0x3003
	lw	$12, pattern($6)
	sw	$12, 0($13)
	addi	$13, $6, 1
	addu	$6, $0, $13
	addu	$13, $0, $13
	addui	$12, $0, 8
	sneu	$13, $13, $12
	bnez	$13, L.9
	addu	$6, $0, $0
L.9:
	addui	$7, $0, 20000
L.11:
L.12:
	addui	$13, $0, 1
	subu	$13, $7, $13
	addu	$7, $0, $13
	sneu	$13, $13, $0
	bnez	$13, L.11
L.7:
	j	L.6
L.5:
	lw	$6, 0($sp)
	lw	$7, 1($sp)
	lw	$12, 2($sp)
	lw	$13, 3($sp)
	addui	$sp, $sp, 4
	jr	$ra
