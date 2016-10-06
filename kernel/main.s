.global	panic
.text
panic:
	subui	$sp, $sp, 4
	sw	$12, 1($sp)
	sw	$13, 2($sp)
	sw	$ra, 3($sp)
	la	$13, L.8
	sw	$13, 0($sp)
	jal	printf
	lw	$13, 4($sp)
	sw	$13, 0($sp)
	jal	printf
	j	L.10
L.9:
	lhi	$13, 0x7
	ori	$13, $13, 0x3004
	sw	$0, 0($13)
	lhi	$13, 0x7
	ori	$13, $13, 0x3002
	addui	$12, $0, 121
	sw	$12, 0($13)
	lhi	$13, 0x7
	ori	$13, $13, 0x3003
	addui	$12, $0, 80
	sw	$12, 0($13)
L.10:
	j	L.9
L.7:
	lw	$12, 1($sp)
	lw	$13, 2($sp)
	lw	$ra, 3($sp)
	addui	$sp, $sp, 4
	jr	$ra
.global	assert
assert:
	subui	$sp, $sp, 3
	sw	$13, 1($sp)
	sw	$ra, 2($sp)
	lw	$13, 3($sp)
	sne	$13, $13, $0
	bnez	$13, L.13
	la	$13, L.15
	sw	$13, 0($sp)
	jal	printf
	lw	$13, 4($sp)
	sw	$13, 0($sp)
	jal	panic
L.13:
L.12:
	lw	$13, 1($sp)
	lw	$ra, 2($sp)
	addui	$sp, $sp, 3
	jr	$ra
.global	main
main:
	subui	$sp, $sp, 10
	sw	$3, 3($sp)
	sw	$4, 4($sp)
	sw	$5, 5($sp)
	sw	$6, 6($sp)
	sw	$7, 7($sp)
	sw	$13, 8($sp)
	sw	$ra, 9($sp)
	addu	$7, $0, $0
	la	$13, L.17
	sw	$13, 0($sp)
	addui	$13, $0, 1
	sw	$13, 1($sp)
	sw	$0, 2($sp)
	jal	printf
	jal	init_proc
	la	$13, system_main
	sw	$13, 0($sp)
	sw	$0, 1($sp)
	la	$13, L.18
	sw	$13, 2($sp)
	jal	new_proc
	addu	$13, $0, $1
	addu	$7, $0, $13
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.21
	addui	$6, $0, 1
	j	L.22
L.21:
	addu	$6, $0, $0
L.22:
	sw	$6, 0($sp)
	la	$13, L.20
	sw	$13, 1($sp)
	jal	assert
	addui	$13, $0, 64
	sw	$13, 52($7)
	la	$13, idle_main
	sw	$13, 0($sp)
	addui	$13, $0, 4
	sw	$13, 1($sp)
	la	$13, L.23
	sw	$13, 2($sp)
	jal	new_proc
	addu	$13, $0, $1
	addu	$7, $0, $13
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.26
	addui	$5, $0, 1
	j	L.27
L.26:
	addu	$5, $0, $0
L.27:
	sw	$5, 0($sp)
	la	$13, L.25
	sw	$13, 1($sp)
	jal	assert
	la	$13, shell_main
	sw	$13, 0($sp)
	addui	$13, $0, 3
	sw	$13, 1($sp)
	la	$13, L.28
	sw	$13, 2($sp)
	jal	new_proc
	addu	$13, $0, $1
	addu	$7, $0, $13
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.31
	addui	$4, $0, 1
	j	L.32
L.31:
	addu	$4, $0, $0
L.32:
	sw	$4, 0($sp)
	la	$13, L.30
	sw	$13, 1($sp)
	jal	assert
	addui	$13, $0, 2
	sw	$13, 52($7)
	la	$13, parallel_main
	sw	$13, 0($sp)
	addui	$13, $0, 3
	sw	$13, 1($sp)
	la	$13, L.33
	sw	$13, 2($sp)
	jal	new_proc
	addu	$13, $0, $1
	addu	$7, $0, $13
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.36
	addui	$3, $0, 1
	j	L.37
L.36:
	addu	$3, $0, $0
L.37:
	sw	$3, 0($sp)
	la	$13, L.35
	sw	$13, 1($sp)
	jal	assert
	addui	$13, $0, 1
	sw	$13, 52($7)
	jal	init_exceptions
	jal	sched
L.16:
	lw	$3, 3($sp)
	lw	$4, 4($sp)
	lw	$5, 5($sp)
	lw	$6, 6($sp)
	lw	$7, 7($sp)
	lw	$13, 8($sp)
	lw	$ra, 9($sp)
	addui	$sp, $sp, 10
	jr	$ra
.extern	FREE_MEM_END 1
.extern	FREE_MEM_BEGIN 1
.extern	BSS_END 1
.extern	DATA_END 1
.extern	TEXT_END 1
.extern	BSS_BEGIN 1
.extern	DATA_BEGIN 1
.extern	TEXT_BEGIN 1
.extern	system_uptime 1
.extern	current_proc 1
.extern	proc_table 1640
.data
L.35:
	.asciiz	"Create parallel task"
L.33:
	.asciiz	"Parallel"
L.30:
	.asciiz	"Create shell task"
L.28:
	.asciiz	"Shell"
L.25:
	.asciiz	"Create idle task"
L.23:
	.asciiz	"IDLE"
L.20:
	.asciiz	"Create sys task"
L.18:
	.asciiz	"SYSTEM"
L.17:
	.asciiz	"\r\nWINIX v%d.%d\r\n"
L.15:
	.asciiz	"\r\nAssertion Failed"
L.8:
	.asciiz	"\r\nPanic! "
