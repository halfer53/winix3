.text
hole_enqueue_tail:
	subui	$sp, $sp, 2
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	lw	$13, 2($sp)
	lw	$13, 0($13)
	addu	$13, $0, $13
	sneu	$13, $13, $0
	bnez	$13, L.8
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.9
L.8:
	lw	$13, 2($sp)
	lw	$13, 1($13)
	lw	$12, 3($sp)
	sw	$12, 2($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
L.9:
	lw	$13, 3($sp)
	sw	$0, 2($13)
L.7:
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
	bnez	$13, L.11
	lw	$13, 3($sp)
	sw	$0, 2($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.12
L.11:
	lw	$13, 3($sp)
	lw	$12, 2($sp)
	lw	$12, 0($12)
	sw	$12, 2($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 0($13)
L.12:
L.10:
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
	bnez	$13, L.14
	lw	$13, 7($sp)
	lw	$13, 1($13)
	addu	$13, $0, $13
	sneu	$13, $13, $0
	bnez	$13, L.18
	addui	$6, $0, 1
	j	L.19
L.18:
	addu	$6, $0, $0
L.19:
	sw	$6, 0($sp)
	la	$13, L.17
	sw	$13, 1($sp)
	jal	assert
	addu	$1, $0, $0
	j	L.13
L.14:
	lw	$13, 7($sp)
	lw	$12, 0($13)
	addu	$12, $0, $12
	lw	$13, 1($13)
	addu	$13, $0, $13
	sneu	$13, $12, $13
	bnez	$13, L.20
	lw	$13, 7($sp)
	addu	$12, $0, $0
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.21
L.20:
	lw	$13, 7($sp)
	lw	$12, 2($7)
	sw	$12, 0($13)
L.21:
	sw	$0, 2($7)
	addu	$1, $0, $7
L.13:
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
	la	$13, L.23
	sw	$13, 0($sp)
	lw	$13, FREE_MEM_BEGIN($0)
	sw	$13, 1($sp)
	jal	printf
L.22:
	lw	$12, 2($sp)
	lw	$13, 3($sp)
	lw	$ra, 4($sp)
	addui	$sp, $sp, 5
	jr	$ra
.global	_sbrk
_sbrk:
	subui	$sp, $sp, 6
	sw	$12, 2($sp)
	sw	$13, 3($sp)
	sw	$ra, 4($sp)
	lw	$13, FREE_MEM_BEGIN($0)
	sw	$13, 5($sp)
	lw	$13, FREE_MEM_END($0)
	sequ	$13, $13, $0
	bnez	$13, L.25
	lw	$13, 6($sp)
	lw	$12, FREE_MEM_BEGIN($0)
	addu	$13, $13, $12
	lw	$12, FREE_MEM_END($0)
	sleu	$13, $13, $12
	bnez	$13, L.27
	addu	$1, $0, $0
	j	L.24
L.27:
L.25:
	lw	$13, FREE_MEM_BEGIN($0)
	lw	$12, 6($sp)
	addu	$13, $13, $12
	sw	$13, FREE_MEM_BEGIN($0)
	la	$13, L.29
	sw	$13, 0($sp)
	lw	$13, FREE_MEM_BEGIN($0)
	sw	$13, 1($sp)
	jal	printf
	lw	$13, 5($sp)
	addu	$1, $0, $13
L.24:
	lw	$12, 2($sp)
	lw	$13, 3($sp)
	lw	$ra, 4($sp)
	addui	$sp, $sp, 6
	jr	$ra
.global	_malloc
_malloc:
	subui	$sp, $sp, 14
	sw	$6, 4($sp)
	sw	$7, 5($sp)
	sw	$12, 6($sp)
	sw	$13, 7($sp)
	sw	$ra, 8($sp)
	addu	$6, $0, $0
	addu	$7, $0, $0
	sw	$0, 11($sp)
	sw	$0, 10($sp)
	sw	$0, 9($sp)
	addu	$13, $0, $0
	sw	$13, 13($sp)
	sw	$13, 12($sp)
L.32:
	la	$13, unused_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$7, $0, $13
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.35
	la	$13, L.37
	sw	$13, 0($sp)
	lw	$13, 0($7)
	sw	$13, 1($sp)
	lw	$13, 1($7)
	addu	$13, $0, $13
	sw	$13, 2($sp)
	jal	printf
	lw	$13, 1($7)
	lw	$12, 14($sp)
	sgeu	$13, $13, $12
	bnez	$13, L.34
	addui	$13, $sp, 12
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_head
L.39:
L.35:
L.33:
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.32
L.34:
	addui	$13, $sp, 12
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
	j	L.41
L.40:
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	hole_enqueue_head
	addui	$13, $sp, 12
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
L.41:
	addu	$13, $0, $6
	sneu	$13, $13, $0
	bnez	$13, L.40
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.43
	la	$13, L.45
	sw	$13, 0($sp)
	jal	printf
	lw	$13, 14($sp)
	sw	$13, 0($sp)
	jal	_sbrk
	addu	$13, $0, $1
	sw	$13, 11($sp)
	la	$13, L.46
	sw	$13, 0($sp)
	addui	$13, $sp, 11
	sw	$13, 1($sp)
	lw	$13, 11($sp)
	sw	$13, 2($sp)
	lw	$13, 0($13)
	sw	$13, 3($sp)
	jal	printf
	lw	$13, 11($sp)
	addu	$13, $0, $13
	sequ	$13, $13, $0
	bnez	$13, L.47
	la	$13, pending_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$7, $0, $13
	lw	$13, 11($sp)
	sw	$13, 0($7)
	lw	$13, 14($sp)
	sw	$13, 1($7)
	la	$13, L.49
	sw	$13, 0($sp)
	lw	$13, 0($7)
	sw	$13, 1($sp)
	lw	$13, 1($7)
	addu	$13, $0, $13
	sw	$13, 2($sp)
	jal	printf
	la	$13, used_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_tail
	lw	$1, 11($sp)
	j	L.30
L.47:
	addu	$1, $0, $0
	j	L.30
L.43:
	lw	$13, 1($7)
	lw	$12, 14($sp)
	sltu	$13, $13, $12
	bnez	$13, L.50
	lw	$13, 0($7)
	sw	$13, 11($sp)
	la	$13, L.52
	sw	$13, 0($sp)
	lw	$13, 0($7)
	sw	$13, 1($sp)
	lw	$13, 1($7)
	addu	$13, $0, $13
	sw	$13, 2($sp)
	jal	printf
	lw	$13, 1($7)
	lw	$12, 14($sp)
	sleu	$13, $13, $12
	bnez	$13, L.53
	la	$13, pending_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
	lw	$13, 14($sp)
	lw	$12, 0($7)
	addu	$13, $13, $12
	sw	$13, 0($6)
	lw	$13, 1($7)
	lw	$12, 14($sp)
	subu	$13, $13, $12
	sw	$13, 1($6)
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	hole_enqueue_tail
	la	$13, L.55
	sw	$13, 0($sp)
	lw	$13, 0($6)
	sw	$13, 1($sp)
	lw	$13, 1($6)
	addu	$13, $0, $13
	sw	$13, 2($sp)
	jal	printf
L.53:
	lw	$13, 14($sp)
	sw	$13, 1($7)
	la	$13, used_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_tail
	lw	$1, 11($sp)
	j	L.30
L.50:
	la	$13, L.56
	sw	$13, 0($sp)
	jal	printf
	addu	$1, $0, $0
L.30:
	lw	$6, 4($sp)
	lw	$7, 5($sp)
	lw	$12, 6($sp)
	lw	$13, 7($sp)
	lw	$ra, 8($sp)
	addui	$sp, $sp, 14
	jr	$ra
.global	_free
_free:
	subui	$sp, $sp, 14
	sw	$4, 3($sp)
	sw	$5, 4($sp)
	sw	$6, 5($sp)
	sw	$7, 6($sp)
	sw	$12, 7($sp)
	sw	$13, 8($sp)
	sw	$ra, 9($sp)
	addu	$6, $0, $0
	addu	$7, $0, $0
	addu	$5, $0, $0
	addu	$4, $0, $0
	sw	$0, 11($sp)
	sw	$0, 10($sp)
	addu	$13, $0, $0
	sw	$13, 13($sp)
	sw	$13, 12($sp)
L.59:
	la	$13, used_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$7, $0, $13
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.62
	la	$13, L.37
	sw	$13, 0($sp)
	lw	$13, 0($7)
	sw	$13, 1($sp)
	lw	$13, 1($7)
	addu	$13, $0, $13
	sw	$13, 2($sp)
	jal	printf
	lw	$13, 0($7)
	addu	$13, $0, $13
	lw	$12, 14($sp)
	addu	$12, $0, $12
	sequ	$13, $13, $12
	bnez	$13, L.61
	addui	$13, $sp, 12
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_head
L.65:
L.62:
L.60:
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.59
L.61:
	addui	$13, $sp, 12
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
	j	L.67
L.66:
	la	$13, used_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	hole_enqueue_head
	addui	$13, $sp, 12
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
L.67:
	addu	$13, $0, $6
	sneu	$13, $13, $0
	bnez	$13, L.66
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.69
	la	$13, L.71
	sw	$13, 0($sp)
	lw	$13, 0($7)
	sw	$13, 1($sp)
	lw	$13, 1($7)
	sw	$13, 2($sp)
	jal	printf
	lw	$5, 14($sp)
	addu	$4, $0, $0
	j	L.75
L.72:
	lhi	$13, 0xffff
	ori	$13, $13, 0xffff
	sw	$13, 0($5)
	addui	$5, $5, 1
L.73:
	addi	$4, $4, 1
L.75:
	addu	$13, $0, $4
	lw	$12, 1($7)
	sltu	$13, $13, $12
	bnez	$13, L.72
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_tail
L.69:
L.57:
	lw	$4, 3($sp)
	lw	$5, 4($sp)
	lw	$6, 5($sp)
	lw	$7, 6($sp)
	lw	$12, 7($sp)
	lw	$13, 8($sp)
	lw	$ra, 9($sp)
	addui	$sp, $sp, 14
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
L.80:
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
L.81:
	addi	$6, $6, 1
	slti	$13, $6, 100
	bnez	$13, L.80
L.76:
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
L.71:
	.asciiz	"found start 0x%x, length %d\n"
L.56:
	.asciiz	"this shouldn't happen h==null but h->length < size"
L.55:
	.asciiz	"remaining hole start 0x%x, size %d\n"
L.52:
	.asciiz	"new hole start 0x%x, size %d\n"
L.49:
	.asciiz	"new hole start 0x%x, size %d\n\n"
L.46:
	.asciiz	" p addr %d, point at %d, deref val %d\n"
L.45:
	.asciiz	"call sbrk\n"
L.37:
	.asciiz	"hole start 0x%x, size %d\n"
L.29:
	.asciiz	"free mem %x\n"
L.23:
	.asciiz	"\r\nfree memory begin 0x%x\r\n"
L.17:
	.asciiz	"deq: tail not null"
