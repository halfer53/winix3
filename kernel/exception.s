handlers:
	.word	no_handler
	.word	no_handler
	.word	no_handler
	.word	no_handler
	.word	no_handler
	.word	button_handler
	.word	timer_handler
	.word	parallel_handler
	.word	serial1_handler
	.word	serial2_handler
	.word	no_handler
	.word	no_handler
	.word	gpf_handler
	.word	syscall_handler
	.word	break_handler
	.word	arith_handler
.global	system_uptime
system_uptime:
	.word	0x0
.text
button_handler:
	subui	$sp, $sp, 1
	sw	$13, 0($sp)
	lhi	$13, 0x7
	ori	$13, $13, 0xf000
	sw	$0, 0($13)
L.7:
	lw	$13, 0($sp)
	addui	$sp, $sp, 1
	jr	$ra
timer_handler:
	subui	$sp, $sp, 2
	sw	$13, 0($sp)
	sw	$ra, 1($sp)
	lhi	$13, 0x7
	ori	$13, $13, 0x2003
	sw	$0, 0($13)
	lw	$13, system_uptime($0)
	addi	$13, $13, 1
	sw	$13, system_uptime($0)
	jal	sched
L.8:
	lw	$13, 0($sp)
	lw	$ra, 1($sp)
	addui	$sp, $sp, 2
	jr	$ra
parallel_handler:
	subui	$sp, $sp, 1
	sw	$13, 0($sp)
	lhi	$13, 0x7
	ori	$13, $13, 0x3005
	sw	$0, 0($13)
L.9:
	lw	$13, 0($sp)
	addui	$sp, $sp, 1
	jr	$ra
serial1_handler:
	subui	$sp, $sp, 1
	sw	$13, 0($sp)
	lhi	$13, 0x7
	ori	$13, $13, 0x4
	sw	$0, 0($13)
L.10:
	lw	$13, 0($sp)
	addui	$sp, $sp, 1
	jr	$ra
serial2_handler:
	subui	$sp, $sp, 1
	sw	$13, 0($sp)
	lhi	$13, 0x7
	ori	$13, $13, 0x1004
	sw	$0, 0($13)
L.11:
	lw	$13, 0($sp)
	addui	$sp, $sp, 1
	jr	$ra
gpf_handler:
	subui	$sp, $sp, 7
	sw	$12, 4($sp)
	sw	$13, 5($sp)
	sw	$ra, 6($sp)
	la	$13, L.13
	sw	$13, 0($sp)
	lw	$13, current_proc($0)
	addui	$12, $13, 59
	sw	$12, 1($sp)
	lw	$12, 81($13)
	sw	$12, 2($sp)
	lw	$13, 15($13)
	sw	$13, 3($sp)
	jal	printf
	lw	$13, current_proc($0)
	sw	$13, 0($sp)
	jal	end_process
	sw	$0, current_proc($0)
	jal	sched
L.12:
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 7
	jr	$ra
syscall_handler:
	subui	$sp, $sp, 11
	sw	$11, 2($sp)
	sw	$12, 3($sp)
	sw	$13, 4($sp)
	sw	$ra, 5($sp)
	lw	$13, current_proc($0)
	addui	$12, $13, 13
	lw	$11, 0($12)
	lw	$11, 0($11)
	addu	$11, $0, $11
	sw	$11, 10($sp)
	lw	$11, 0($12)
	lw	$11, 1($11)
	addu	$11, $0, $11
	sw	$11, 7($sp)
	lw	$12, 0($12)
	lw	$12, 2($12)
	sw	$12, 9($sp)
	lw	$12, 9($sp)
	lw	$13, 81($13)
	sw	$13, 0($12)
	lw	$13, current_proc($0)
	sw	$13, 8($sp)
	lw	$13, 8($sp)
	lhi	$12, 0xffff
	ori	$12, $12, 0xffff
	sw	$12, 0($13)
	lw	$13, 10($sp)
	sw	$13, 6($sp)
	lhi	$12, 0x1337
	ori	$12, $12, 0x1
	seq	$13, $13, $12
	bnez	$13, L.18
	lhi	$13, 0x1337
	ori	$13, $13, 0x2
	lw	$12, 6($sp)
	seq	$13, $12, $13
	bnez	$13, L.19
	lhi	$13, 0x1337
	ori	$13, $13, 0x3
	lw	$12, 6($sp)
	seq	$13, $12, $13
	bnez	$13, L.17
	j	L.16
L.17:
	lw	$13, current_proc($0)
	addui	$13, $13, 80
	lw	$12, 0($13)
	ori	$12, $12, 2
	sw	$12, 0($13)
L.18:
	lw	$13, 7($sp)
	sw	$13, 0($sp)
	lw	$13, 9($sp)
	sw	$13, 1($sp)
	jal	wini_send
	addu	$13, $0, $1
	lw	$12, 8($sp)
	sw	$13, 0($12)
	j	L.16
L.19:
	lw	$13, 9($sp)
	sw	$13, 0($sp)
	jal	wini_receive
	addu	$13, $0, $1
	lw	$12, 8($sp)
	sw	$13, 0($12)
L.16:
	jal	sched
L.14:
	lw	$11, 2($sp)
	lw	$12, 3($sp)
	lw	$13, 4($sp)
	lw	$ra, 5($sp)
	addui	$sp, $sp, 11
	jr	$ra
break_handler:
L.20:
	jr	$ra
arith_handler:
	subui	$sp, $sp, 7
	sw	$12, 4($sp)
	sw	$13, 5($sp)
	sw	$ra, 6($sp)
	la	$13, L.22
	sw	$13, 0($sp)
	lw	$13, current_proc($0)
	addui	$12, $13, 59
	sw	$12, 1($sp)
	lw	$12, 81($13)
	sw	$12, 2($sp)
	lw	$13, 15($13)
	sw	$13, 3($sp)
	jal	printf
	lw	$13, current_proc($0)
	sw	$13, 0($sp)
	jal	end_process
	sw	$0, current_proc($0)
	jal	sched
L.21:
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 7
	jr	$ra
no_handler:
	subui	$sp, $sp, 3
	sw	$13, 1($sp)
	sw	$ra, 2($sp)
	la	$13, L.24
	sw	$13, 0($sp)
	jal	panic
L.23:
	lw	$13, 1($sp)
	lw	$ra, 2($sp)
	addui	$sp, $sp, 3
	jr	$ra
exception_handler:
	subui	$sp, $sp, 4
	sw	$7, 0($sp)
	sw	$12, 1($sp)
	sw	$13, 2($sp)
	sw	$ra, 3($sp)
	addui	$7, $0, 16
L.26:
	lw	$13, 4($sp)
	addui	$12, $0, 1
	sll	$12, $12, $7
	and	$13, $13, $12
	seq	$13, $13, $0
	bnez	$13, L.30
	lw	$13, handlers($7)
	jalr	$13
L.30:
L.27:
	subi	$7, $7, 1
	sne	$13, $7, $0
	bnez	$13, L.26
L.25:
	lw	$7, 0($sp)
	lw	$12, 1($sp)
	lw	$13, 2($sp)
	lw	$ra, 3($sp)
	addui	$sp, $sp, 4
	jr	$ra
.global	init_exceptions
init_exceptions:
	subui	$sp, $sp, 4
	sw	$12, 1($sp)
	sw	$13, 2($sp)
	sw	$ra, 3($sp)
	la	$13, exception_handler
	sw	$13, 0($sp)
	jal	wramp_set_handler
	lhi	$13, 0x7
	ori	$13, $13, 0x2001
	addui	$12, $0, 40
	sw	$12, 0($13)
	lhi	$13, 0x7
	ori	$13, $13, 0x2000
	addui	$12, $0, 3
	sw	$12, 0($13)
L.32:
	lw	$12, 1($sp)
	lw	$13, 2($sp)
	lw	$ra, 3($sp)
	addui	$sp, $sp, 4
	jr	$ra
.extern	FREE_MEM_END 1
.extern	FREE_MEM_BEGIN 1
.extern	BSS_END 1
.extern	DATA_END 1
.extern	TEXT_END 1
.extern	BSS_BEGIN 1
.extern	DATA_BEGIN 1
.extern	TEXT_BEGIN 1
.extern	current_proc 1
.extern	proc_table 1640
.data
L.24:
	.asciiz	"Unhandled Exception"
L.22:
	.asciiz	"\r\n[SYSTEM] Process \"%s (%d)\" ARITH: PC=%x.\r\n"
L.13:
	.asciiz	"\r\n[SYSTEM] Process \"%s (%d)\" GPF: PC=%x.\r\n"
