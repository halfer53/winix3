_mode:
	.word	0x0
.global	printHex
.text
printHex:
	subui	$sp, $sp, 2
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	lhi	$13, 0x7
	ori	$13, $13, 0x3002
	lw	$12, 2($sp)
	srai	$12, $12, 4
	andi	$12, $12, 15
	sw	$12, 0($13)
	lhi	$13, 0x7
	ori	$13, $13, 0x3003
	lw	$12, 2($sp)
	andi	$12, $12, 15
	sw	$12, 0($13)
L.6:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 2
	jr	$ra
.global	printDec
printDec:
	subui	$sp, $sp, 3
	sw	$11, 0($sp)
	sw	$12, 1($sp)
	sw	$13, 2($sp)
	addui	$13, $0, 10
	lhi	$12, 0x7
	ori	$12, $12, 0x3002
	lw	$11, 3($sp)
	div	$11, $11, $13
	rem	$13, $11, $13
	sw	$13, 0($12)
	lhi	$13, 0x7
	ori	$13, $13, 0x3003
	lw	$12, 3($sp)
	remi	$12, $12, 10
	sw	$12, 0($13)
L.7:
	lw	$11, 0($sp)
	lw	$12, 1($sp)
	lw	$13, 2($sp)
	addui	$sp, $sp, 3
	jr	$ra
.global	parallel_main
parallel_main:
	subui	$sp, $sp, 7
	sw	$5, 1($sp)
	sw	$6, 2($sp)
	sw	$7, 3($sp)
	sw	$12, 4($sp)
	sw	$13, 5($sp)
	sw	$ra, 6($sp)
	lhi	$13, 0x7
	ori	$13, $13, 0x3004
	addui	$12, $0, 1
	sw	$12, 0($13)
	j	L.10
L.9:
	addui	$13, $0, 100
	lhi	$12, 0x7
	ori	$12, $12, 0x3000
	lw	$12, 0($12)
	div	$7, $13, $12
	lhi	$13, 0x7
	ori	$13, $13, 0x3001
	lw	$6, 0($13)
	seqi	$13, $6, 1
	bnez	$13, L.15
	seqi	$13, $6, 2
	bnez	$13, L.16
	seqi	$13, $6, 3
	bnez	$13, L.17
	j	L.12
L.15:
	sw	$0, _mode($0)
	j	L.13
L.16:
	addui	$13, $0, 1
	sw	$13, _mode($0)
	j	L.13
L.17:
	sw	$0, 0($sp)
	jal	sys_exit
	j	L.8
L.12:
L.13:
	lw	$5, _mode($0)
	seq	$13, $5, $0
	bnez	$13, L.21
	seqi	$13, $5, 1
	bnez	$13, L.22
	j	L.18
L.21:
	sw	$7, 0($sp)
	jal	printHex
	j	L.19
L.22:
	sw	$7, 0($sp)
	jal	printDec
L.18:
L.19:
L.10:
	j	L.9
L.8:
	lw	$5, 1($sp)
	lw	$6, 2($sp)
	lw	$7, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 7
	jr	$ra
