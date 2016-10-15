.text
hole_enqueue_tail:
	subui	$sp, $sp, 2
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	lw	$13, 2($sp)
	lw	$13, 0($13)
	addu	$13, $0, $13
	sneu	$13, $13, $0
	bnez	$13, L.11
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.12
L.11:
	lw	$13, 2($sp)
	lw	$13, 1($13)
	lw	$12, 3($sp)
	sw	$12, 2($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
L.12:
	lw	$13, 3($sp)
	sw	$0, 2($13)
L.10:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 2
	jr	$ra
hole_enqueue_head:
	subui	$sp, $sp, 2
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	lw	$13, 2($sp)
	lw	$13, 0($13)
	addu	$13, $0, $13
	sneu	$13, $13, $0
	bnez	$13, L.14
	lw	$13, 3($sp)
	sw	$0, 2($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.15
L.14:
	lw	$13, 3($sp)
	lw	$12, 2($sp)
	lw	$12, 0($12)
	sw	$12, 2($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 0($13)
L.15:
L.13:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 2
	jr	$ra
hole_dequeue:
	subui	$sp, $sp, 7
	sw	$6, 2($sp)
	sw	$7, 3($sp)
	sw	$12, 4($sp)
	sw	$13, 5($sp)
	sw	$ra, 6($sp)
	lw	$13, 7($sp)
	lw	$7, 0($13)
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.17
	lw	$13, 7($sp)
	lw	$13, 1($13)
	addu	$13, $0, $13
	sneu	$13, $13, $0
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
	addu	$1, $0, $0
	j	L.16
L.17:
	lw	$13, 7($sp)
	lw	$12, 0($13)
	addu	$12, $0, $12
	lw	$13, 1($13)
	addu	$13, $0, $13
	sneu	$13, $12, $13
	bnez	$13, L.23
	lw	$13, 7($sp)
	addu	$12, $0, $0
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.24
L.23:
	lw	$13, 7($sp)
	lw	$12, 2($7)
	sw	$12, 0($13)
L.24:
	sw	$0, 2($7)
	addu	$1, $0, $7
L.16:
	lw	$6, 2($sp)
	lw	$7, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 7
	jr	$ra
.global	Scan_FREE_MEM_BEGIN
Scan_FREE_MEM_BEGIN:
	subui	$sp, $sp, 5
	sw	$12, 2($sp)
	sw	$13, 3($sp)
	sw	$ra, 4($sp)
	la	$13, BSS_END
	addu	$13, $0, $13
	sw	$13, FREE_MEM_BEGIN($0)
	lw	$13, FREE_MEM_BEGIN($0)
	addui	$12, $0, 1023
	or	$13, $13, $12
	sw	$13, FREE_MEM_BEGIN($0)
	lw	$13, FREE_MEM_BEGIN($0)
	addui	$12, $0, 1
	addu	$13, $13, $12
	sw	$13, FREE_MEM_BEGIN($0)
	la	$13, L.26
	sw	$13, 0($sp)
	lw	$13, FREE_MEM_BEGIN($0)
	sw	$13, 1($sp)
	jal	printf
L.25:
	lw	$12, 2($sp)
	lw	$13, 3($sp)
	lw	$ra, 4($sp)
	addui	$sp, $sp, 5
	jr	$ra
.global	_sbrk
_sbrk:
	subui	$sp, $sp, 3
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	lw	$13, FREE_MEM_BEGIN($0)
	sw	$13, 2($sp)
	lw	$13, FREE_MEM_END($0)
	sequ	$13, $13, $0
	bnez	$13, L.28
	lw	$13, 3($sp)
	lw	$12, FREE_MEM_BEGIN($0)
	addu	$13, $13, $12
	lw	$12, FREE_MEM_END($0)
	sleu	$13, $13, $12
	bnez	$13, L.30
	addu	$1, $0, $0
	j	L.27
L.30:
L.28:
	lw	$13, FREE_MEM_BEGIN($0)
	lw	$12, 3($sp)
	addu	$13, $13, $12
	sw	$13, FREE_MEM_BEGIN($0)
	lw	$13, 2($sp)
	addu	$1, $0, $13
L.27:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 3
	jr	$ra
.global	init_memory
init_memory:
	subui	$sp, $sp, 7
	sw	$6, 2($sp)
	sw	$7, 3($sp)
	sw	$12, 4($sp)
	sw	$13, 5($sp)
	sw	$ra, 6($sp)
	addu	$7, $0, $0
	addu	$6, $0, $0
	addu	$13, $0, $0
	sw	$13, unused_holes+1($0)
	sw	$13, unused_holes($0)
	addu	$13, $0, $0
	sw	$13, used_holes+1($0)
	sw	$13, used_holes($0)
	addu	$13, $0, $0
	sw	$13, pending_holes+1($0)
	sw	$13, pending_holes($0)
	addu	$6, $0, $0
L.36:
	addui	$13, $0, 3
	mult	$13, $13, $6
	la	$12, hole_table
	addu	$7, $13, $12
	sw	$0, 0($7)
	sw	$0, 1($7)
	sw	$0, 2($7)
	la	$13, pending_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_head
L.37:
	addi	$6, $6, 1
	slti	$13, $6, 100
	bnez	$13, L.36
L.32:
	lw	$6, 2($sp)
	lw	$7, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 7
	jr	$ra
.bss
used_holes:
	.space	2
pending_holes:
	.space	2
unused_holes:
	.space	2
.global	hole_table
hole_table:
	.space	300
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
L.26:
	.asciiz	"\r\nfree memory begin 0x%x\r\n"
L.20:
	.asciiz	"deq: tail not null"
