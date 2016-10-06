.global	putc
.text
putc:
	subui	$sp, $sp, 2
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	lw	$13, 2($sp)
	sw	$13, 2($sp)
L.7:
L.8:
	lhi	$13, 0x7
	ori	$13, $13, 0x3
	lw	$13, 0($13)
	andi	$13, $13, 2
	seq	$13, $13, $0
	bnez	$13, L.7
	lhi	$13, 0x7
	ori	$13, $13, 0x0
	lw	$12, 2($sp)
	sw	$12, 0($13)
	addu	$1, $0, $0
L.6:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 2
	jr	$ra
.global	getc
getc:
	subui	$sp, $sp, 1
	sw	$13, 0($sp)
L.11:
L.12:
	lhi	$13, 0x7
	ori	$13, $13, 0x3
	lw	$13, 0($13)
	andi	$13, $13, 1
	seq	$13, $13, $0
	bnez	$13, L.11
	lhi	$13, 0x7
	ori	$13, $13, 0x1
	lw	$1, 0($13)
L.10:
	lw	$13, 0($sp)
	addui	$sp, $sp, 1
	jr	$ra
.global	getc2
getc2:
	subui	$sp, $sp, 13
	sw	$7, 2($sp)
	sw	$13, 3($sp)
	sw	$ra, 4($sp)
	addu	$7, $0, $0
	addui	$13, $0, 2
	sw	$13, 6($sp)
	la	$13, L.16
	sw	$13, 0($sp)
	jal	printf
	sw	$0, 0($sp)
	addui	$13, $sp, 5
	sw	$13, 1($sp)
	jal	winix_sendrec
	addu	$13, $0, $1
	addu	$7, $0, $13
	la	$13, L.17
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	printf
	lw	$1, 7($sp)
L.14:
	lw	$7, 2($sp)
	lw	$13, 3($sp)
	lw	$ra, 4($sp)
	addui	$sp, $sp, 13
	jr	$ra
putd:
	subui	$sp, $sp, 6
	sw	$6, 1($sp)
	sw	$7, 2($sp)
	sw	$12, 3($sp)
	sw	$13, 4($sp)
	sw	$ra, 5($sp)
	lhi	$7, 0x3b9a
	ori	$7, $7, 0xca00
	lw	$13, 6($sp)
	sne	$13, $13, $0
	bnez	$13, L.20
	addui	$13, $0, 48
	sw	$13, 0($sp)
	jal	putc
	j	L.19
L.20:
	lw	$13, 6($sp)
	sge	$13, $13, $0
	bnez	$13, L.25
	addui	$13, $0, 45
	sw	$13, 0($sp)
	jal	putc
	lhi	$13, 0xffff
	ori	$13, $13, 0xffff
	lw	$12, 6($sp)
	mult	$13, $13, $12
	sw	$13, 6($sp)
	j	L.25
L.24:
	divi	$7, $7, 10
L.25:
	lw	$13, 6($sp)
	sgt	$13, $7, $13
	bnez	$13, L.24
	j	L.28
L.27:
	lw	$13, 6($sp)
	div	$6, $13, $7
	remi	$13, $6, 10
	addi	$13, $13, 48
	sw	$13, 0($sp)
	jal	putc
	divi	$7, $7, 10
L.28:
	sne	$13, $7, $0
	bnez	$13, L.27
L.19:
	lw	$6, 1($sp)
	lw	$7, 2($sp)
	lw	$12, 3($sp)
	lw	$13, 4($sp)
	lw	$ra, 5($sp)
	addui	$sp, $sp, 6
	jr	$ra
putx:
	subui	$sp, $sp, 5
	sw	$6, 1($sp)
	sw	$7, 2($sp)
	sw	$13, 3($sp)
	sw	$ra, 4($sp)
	addui	$7, $0, 28
L.31:
	lw	$13, 5($sp)
	sra	$13, $13, $7
	andi	$6, $13, 15
	sgei	$13, $6, 10
	bnez	$13, L.35
	addi	$13, $6, 48
	sw	$13, 0($sp)
	jal	putc
	j	L.36
L.35:
	subi	$13, $6, 10
	addi	$13, $13, 65
	sw	$13, 0($sp)
	jal	putc
L.36:
L.32:
	subi	$7, $7, 4
	sge	$13, $7, $0
	bnez	$13, L.31
L.30:
	lw	$6, 1($sp)
	lw	$7, 2($sp)
	lw	$13, 3($sp)
	lw	$ra, 4($sp)
	addui	$sp, $sp, 5
	jr	$ra
puts:
	subui	$sp, $sp, 4
	sw	$12, 1($sp)
	sw	$13, 2($sp)
	sw	$ra, 3($sp)
	j	L.39
L.38:
	lw	$13, 4($sp)
	addui	$12, $13, 1
	sw	$12, 4($sp)
	lw	$13, 0($13)
	sw	$13, 0($sp)
	jal	putc
L.39:
	lw	$13, 4($sp)
	lw	$13, 0($13)
	sne	$13, $13, $0
	bnez	$13, L.38
L.37:
	lw	$12, 1($sp)
	lw	$13, 2($sp)
	lw	$ra, 3($sp)
	addui	$sp, $sp, 4
	jr	$ra
.global	printf
printf:
	subui	$sp, $sp, 7
	sw	$6, 1($sp)
	sw	$7, 2($sp)
	sw	$12, 3($sp)
	sw	$13, 4($sp)
	sw	$ra, 5($sp)
	addui	$7, $sp, 7
	addui	$7, $7, 1
	j	L.43
L.42:
	lw	$13, 7($sp)
	lw	$13, 0($13)
	snei	$13, $13, 37
	bnez	$13, L.45
	lw	$13, 7($sp)
	addui	$13, $13, 1
	sw	$13, 7($sp)
	lw	$13, 7($sp)
	lw	$6, 0($13)
	addui	$13, $0, 115
	sw	$13, 6($sp)
	seq	$13, $6, $13
	bnez	$13, L.52
	lw	$13, 6($sp)
	sgt	$13, $6, $13
	bnez	$13, L.54
L.53:
	seqi	$13, $6, 100
	bnez	$13, L.50
	j	L.47
L.54:
	seqi	$13, $6, 120
	bnez	$13, L.51
	j	L.47
L.50:
	lw	$13, 0($7)
	sw	$13, 0($sp)
	jal	putd
	addui	$7, $7, 1
	lw	$13, 7($sp)
	addui	$13, $13, 1
	sw	$13, 7($sp)
	j	L.46
L.51:
	lw	$13, 0($7)
	sw	$13, 0($sp)
	jal	putx
	addui	$7, $7, 1
	lw	$13, 7($sp)
	addui	$13, $13, 1
	sw	$13, 7($sp)
	j	L.46
L.52:
	lw	$13, 0($7)
	sw	$13, 0($sp)
	jal	puts
	addui	$7, $7, 1
	lw	$13, 7($sp)
	addui	$13, $13, 1
	sw	$13, 7($sp)
	j	L.46
L.47:
	lw	$13, 7($sp)
	addui	$12, $13, 1
	sw	$12, 7($sp)
	lw	$13, 0($13)
	sw	$13, 0($sp)
	jal	putc
	j	L.46
L.45:
	lw	$13, 7($sp)
	addui	$12, $13, 1
	sw	$12, 7($sp)
	lw	$13, 0($13)
	sw	$13, 0($sp)
	jal	putc
L.46:
L.43:
	lw	$13, 7($sp)
	lw	$13, 0($13)
	sne	$13, $13, $0
	bnez	$13, L.42
	addu	$1, $0, $0
L.41:
	lw	$6, 1($sp)
	lw	$7, 2($sp)
	lw	$12, 3($sp)
	lw	$13, 4($sp)
	lw	$ra, 5($sp)
	addui	$sp, $sp, 7
	jr	$ra
.data
L.17:
	.asciiz	"Response: %d\r\n"
L.16:
	.asciiz	"Sending Message...\r\n"
