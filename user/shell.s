.global	commands
commands:
	.word	L.1
	.word	ps
	.word	L.2
	.word	uptime
	.word	L.3
	.word	shutdown
	.word	L.4
	.word	exit
	.word	0x0
	.word	generic
.global	isPrintable
.text
isPrintable:
	subui	$sp, $sp, 4
	sw	$7, 0($sp)
	sw	$12, 1($sp)
	sw	$13, 2($sp)
	lw	$13, 4($sp)
	sw	$13, 3($sp)
	addui	$12, $0, 33
	sgt	$13, $12, $13
	bnez	$13, L.7
	lw	$13, 3($sp)
	sgti	$13, $13, 126
	bnez	$13, L.7
	addui	$7, $0, 1
	j	L.8
L.7:
	addu	$7, $0, $0
L.8:
	addu	$1, $0, $7
L.5:
	lw	$7, 0($sp)
	lw	$12, 1($sp)
	lw	$13, 2($sp)
	addui	$sp, $sp, 4
	jr	$ra
.global	ps
ps:
	subui	$sp, $sp, 3
	sw	$13, 1($sp)
	sw	$ra, 2($sp)
	la	$13, L.10
	sw	$13, 0($sp)
	jal	printf
	addu	$1, $0, $0
L.9:
	lw	$13, 1($sp)
	lw	$ra, 2($sp)
	addui	$sp, $sp, 3
	jr	$ra
.global	uptime
uptime:
	subui	$sp, $sp, 15
	sw	$4, 6($sp)
	sw	$5, 7($sp)
	sw	$6, 8($sp)
	sw	$7, 9($sp)
	sw	$11, 10($sp)
	sw	$12, 11($sp)
	sw	$13, 12($sp)
	sw	$ra, 13($sp)
	jal	sys_uptime
	addu	$13, $0, $1
	addu	$7, $0, $13
	addui	$13, $0, 60
	div	$4, $7, $13
	div	$5, $4, $13
	div	$6, $5, $13
	addui	$12, $0, 24
	div	$11, $6, $12
	sw	$11, 14($sp)
	rem	$4, $4, $13
	rem	$5, $5, $13
	rem	$6, $6, $12
	remi	$7, $7, 100
	la	$13, L.12
	sw	$13, 0($sp)
	lw	$13, 14($sp)
	sw	$13, 1($sp)
	sw	$6, 2($sp)
	sw	$5, 3($sp)
	sw	$4, 4($sp)
	sw	$7, 5($sp)
	jal	printf
	addu	$1, $0, $0
L.11:
	lw	$4, 6($sp)
	lw	$5, 7($sp)
	lw	$6, 8($sp)
	lw	$7, 9($sp)
	lw	$11, 10($sp)
	lw	$12, 11($sp)
	lw	$13, 12($sp)
	lw	$ra, 13($sp)
	addui	$sp, $sp, 15
	jr	$ra
.global	shutdown
shutdown:
	subui	$sp, $sp, 3
	sw	$13, 1($sp)
	sw	$ra, 2($sp)
	la	$13, L.14
	sw	$13, 0($sp)
	jal	printf
	addu	$1, $0, $0
L.13:
	lw	$13, 1($sp)
	lw	$ra, 2($sp)
	addui	$sp, $sp, 3
	jr	$ra
.global	exit
exit:
	subui	$sp, $sp, 3
	sw	$13, 1($sp)
	sw	$ra, 2($sp)
	la	$13, L.16
	sw	$13, 0($sp)
	jal	printf
	sw	$0, 0($sp)
	jal	sys_exit
	addu	$13, $0, $1
	addu	$1, $0, $13
L.15:
	lw	$13, 1($sp)
	lw	$ra, 2($sp)
	addui	$sp, $sp, 3
	jr	$ra
.global	generic
generic:
	subui	$sp, $sp, 4
	sw	$13, 2($sp)
	sw	$ra, 3($sp)
	lw	$13, 4($sp)
	sne	$13, $13, $0
	bnez	$13, L.18
	addu	$1, $0, $0
	j	L.17
L.18:
	la	$13, L.20
	sw	$13, 0($sp)
	lw	$13, 5($sp)
	lw	$13, 0($13)
	sw	$13, 1($sp)
	jal	printf
	lhi	$1, 0xffff
	ori	$1, $1, 0xffff
L.17:
	lw	$13, 2($sp)
	lw	$ra, 3($sp)
	addui	$sp, $sp, 4
	jr	$ra
.global	shell_main
shell_main:
	subui	$sp, $sp, 11
	sw	$4, 2($sp)
	sw	$5, 3($sp)
	sw	$6, 4($sp)
	sw	$7, 5($sp)
	sw	$12, 6($sp)
	sw	$13, 7($sp)
	sw	$ra, 8($sp)
	addu	$5, $0, $0
	j	L.23
L.22:
	la	$13, L.25
	sw	$13, 0($sp)
	jal	printf
	addu	$6, $0, $0
L.26:
	jal	getc
	addu	$13, $0, $1
	sw	$13, buf($6)
	lw	$13, buf($6)
	snei	$13, $13, 13
	bnez	$13, L.30
	j	L.28
L.30:
	lw	$13, buf($6)
	sw	$13, 0($sp)
	jal	putc
L.27:
	addi	$6, $6, 1
	slti	$13, $6, 99
	bnez	$13, L.26
L.28:
	addi	$13, $6, 1
	addu	$6, $0, $13
	sw	$0, buf($13)
	la	$13, L.32
	sw	$13, 0($sp)
	jal	printf
	addu	$4, $0, $0
	la	$7, buf
	j	L.34
L.36:
	addui	$7, $7, 1
L.37:
	lw	$13, 0($7)
	sw	$13, 10($sp)
	seq	$13, $13, $0
	bnez	$13, L.39
	lw	$13, 10($sp)
	sw	$13, 0($sp)
	jal	isPrintable
	addu	$13, $0, $1
	seq	$13, $13, $0
	bnez	$13, L.36
L.39:
	lw	$13, 0($7)
	seq	$13, $13, $0
	bnez	$13, L.43
	addu	$13, $0, $4
	addi	$4, $13, 1
	sw	$7, tokens($13)
	j	L.43
L.42:
	addui	$7, $7, 1
L.43:
	lw	$13, 0($7)
	sw	$13, 9($sp)
	seq	$13, $13, $0
	bnez	$13, L.45
	lw	$13, 9($sp)
	sw	$13, 0($sp)
	jal	isPrintable
	addu	$13, $0, $1
	sne	$13, $13, $0
	bnez	$13, L.42
L.45:
	lw	$13, 0($7)
	seq	$13, $13, $0
	bnez	$13, L.46
	addu	$13, $0, $7
	addui	$7, $13, 1
	sw	$0, 0($13)
L.46:
L.34:
	lw	$13, 0($7)
	sne	$13, $13, $0
	bnez	$13, L.37
	la	$5, commands
	j	L.49
L.48:
	addui	$5, $5, 2
L.49:
	lw	$13, 0($5)
	sw	$13, 10($sp)
	addu	$12, $0, $13
	sequ	$13, $12, $0
	bnez	$13, L.51
	lw	$13, tokens($0)
	sw	$13, 0($sp)
	lw	$13, 10($sp)
	sw	$13, 1($sp)
	jal	strcmp
	addu	$13, $0, $1
	sne	$13, $13, $0
	bnez	$13, L.48
L.51:
	sw	$4, 0($sp)
	la	$13, tokens
	sw	$13, 1($sp)
	lw	$13, 1($5)
	jalr	$13
L.23:
	j	L.22
L.21:
	lw	$4, 2($sp)
	lw	$5, 3($sp)
	lw	$6, 4($sp)
	lw	$7, 5($sp)
	lw	$12, 6($sp)
	lw	$13, 7($sp)
	lw	$ra, 8($sp)
	addui	$sp, $sp, 11
	jr	$ra
.bss
tokens:
	.space	50
buf:
	.space	100
.data
L.32:
	.asciiz	"\r\n"
L.25:
	.asciiz	"WINIX> "
L.20:
	.asciiz	"Unknown command '%s'\r\n"
L.16:
	.asciiz	"Bye!\r\n"
L.14:
	.asciiz	"Placeholder for SHUTDOWN\r\n"
L.12:
	.asciiz	"Uptime is %dd %dh %dm %d.%ds\r\n"
L.10:
	.asciiz	"Placeholder for PS\r\n"
L.4:
	.asciiz	"exit"
L.3:
	.asciiz	"shutdown"
L.2:
	.asciiz	"uptime"
L.1:
	.asciiz	"ps"
