.text
hole_enqueue_tail:
	subui	$sp, $sp, 2
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	lw	$13, 2($sp)
	lw	$13, 0($13)
	addu	$13, $0, $13
	sneu	$13, $13, $0
	bnez	$13, L.10
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.11
L.10:
	lw	$13, 2($sp)
	lw	$13, 1($13)
	lw	$12, 3($sp)
	sw	$12, 2($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
L.11:
	lw	$13, 3($sp)
	sw	$0, 2($13)
L.9:
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
	bnez	$13, L.13
	lw	$13, 3($sp)
	sw	$0, 2($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.14
L.13:
	lw	$13, 3($sp)
	lw	$12, 2($sp)
	lw	$12, 0($12)
	sw	$12, 2($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 0($13)
L.14:
L.12:
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
	bnez	$13, L.16
	lw	$13, 7($sp)
	lw	$13, 1($13)
	addu	$13, $0, $13
	sneu	$13, $13, $0
	bnez	$13, L.20
	addui	$6, $0, 1
	j	L.21
L.20:
	addu	$6, $0, $0
L.21:
	sw	$6, 0($sp)
	la	$13, L.19
	sw	$13, 1($sp)
	jal	assert
	addu	$1, $0, $0
	j	L.15
L.16:
	lw	$13, 7($sp)
	lw	$12, 0($13)
	addu	$12, $0, $12
	lw	$13, 1($13)
	addu	$13, $0, $13
	sneu	$13, $12, $13
	bnez	$13, L.22
	lw	$13, 7($sp)
	addu	$12, $0, $0
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.23
L.22:
	lw	$13, 7($sp)
	lw	$12, 2($7)
	sw	$12, 0($13)
L.23:
	sw	$0, 2($7)
	addu	$1, $0, $7
L.15:
	lw	$6, 2($sp)
	lw	$7, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 7
	jr	$ra
hole_delete:
	subui	$sp, $sp, 9
	sw	$5, 2($sp)
	sw	$6, 3($sp)
	sw	$7, 4($sp)
	sw	$12, 5($sp)
	sw	$13, 6($sp)
	sw	$ra, 7($sp)
	lw	$13, 9($sp)
	lw	$7, 0($13)
	addu	$6, $0, $0
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.32
	lw	$13, 9($sp)
	lw	$13, 1($13)
	addu	$13, $0, $13
	sneu	$13, $13, $0
	bnez	$13, L.29
	addui	$5, $0, 1
	j	L.30
L.29:
	addu	$5, $0, $0
L.30:
	sw	$5, 0($sp)
	la	$13, L.28
	sw	$13, 1($sp)
	jal	assert
	addu	$1, $0, $0
	j	L.24
L.31:
	addu	$6, $0, $7
	lw	$7, 2($7)
L.32:
	addu	$13, $0, $7
	sw	$13, 8($sp)
	lw	$12, 10($sp)
	addu	$12, $0, $12
	sequ	$13, $13, $12
	bnez	$13, L.34
	lw	$13, 8($sp)
	sneu	$13, $13, $0
	bnez	$13, L.31
L.34:
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.35
	addu	$13, $0, $6
	sneu	$13, $13, $0
	bnez	$13, L.37
	lw	$13, 9($sp)
	lw	$12, 0($13)
	addu	$12, $0, $12
	lw	$13, 1($13)
	addu	$13, $0, $13
	sneu	$13, $12, $13
	bnez	$13, L.39
	lw	$13, 9($sp)
	addu	$12, $0, $0
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.38
L.39:
	lw	$13, 9($sp)
	lw	$12, 2($7)
	sw	$12, 0($13)
	j	L.38
L.37:
	lw	$13, 2($7)
	sw	$13, 2($6)
L.38:
	addui	$1, $0, 1
	j	L.24
L.35:
	addu	$1, $0, $0
L.24:
	lw	$5, 2($sp)
	lw	$6, 3($sp)
	lw	$7, 4($sp)
	lw	$12, 5($sp)
	lw	$13, 6($sp)
	lw	$ra, 7($sp)
	addui	$sp, $sp, 9
	jr	$ra
hole_delete2:
	subui	$sp, $sp, 2
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	lw	$13, 4($sp)
	addu	$13, $0, $13
	sequ	$13, $13, $0
	bnez	$13, L.42
	lw	$13, 3($sp)
	addu	$13, $0, $13
	sneu	$13, $13, $0
	bnez	$13, L.44
	lw	$13, 2($sp)
	lw	$12, 0($13)
	addu	$12, $0, $12
	lw	$13, 1($13)
	addu	$13, $0, $13
	sneu	$13, $12, $13
	bnez	$13, L.46
	lw	$13, 2($sp)
	addu	$12, $0, $0
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.45
L.46:
	lw	$13, 2($sp)
	lw	$12, 4($sp)
	lw	$12, 2($12)
	sw	$12, 0($13)
	j	L.45
L.44:
	lw	$13, 3($sp)
	lw	$12, 4($sp)
	lw	$12, 2($12)
	sw	$12, 2($13)
L.45:
	addui	$1, $0, 1
	j	L.41
L.42:
	addu	$1, $0, $0
L.41:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 2
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
	la	$13, L.49
	sw	$13, 0($sp)
	lw	$13, FREE_MEM_BEGIN($0)
	sw	$13, 1($sp)
	jal	printf
L.48:
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
	bnez	$13, L.51
	lw	$13, 3($sp)
	lw	$12, FREE_MEM_BEGIN($0)
	addu	$13, $13, $12
	lw	$12, FREE_MEM_END($0)
	sleu	$13, $13, $12
	bnez	$13, L.53
	addu	$1, $0, $0
	j	L.50
L.53:
L.51:
	lw	$13, FREE_MEM_BEGIN($0)
	lw	$12, 3($sp)
	addu	$13, $13, $12
	sw	$13, FREE_MEM_BEGIN($0)
	lw	$13, 2($sp)
	addu	$1, $0, $13
L.50:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 3
	jr	$ra
.global	_malloc
_malloc:
	subui	$sp, $sp, 11
	sw	$6, 3($sp)
	sw	$7, 4($sp)
	sw	$11, 5($sp)
	sw	$12, 6($sp)
	sw	$13, 7($sp)
	sw	$ra, 8($sp)
	addu	$7, $0, $0
	lw	$6, unused_holes($0)
	sw	$0, 9($sp)
	sw	$0, 10($sp)
	lw	$13, 11($sp)
	sneu	$13, $13, $0
	bnez	$13, L.59
	addu	$1, $0, $0
	j	L.55
L.58:
	addu	$7, $0, $6
	lw	$6, 2($6)
L.59:
	addu	$13, $0, $6
	sequ	$13, $13, $0
	bnez	$13, L.61
	lw	$13, 1($6)
	lw	$12, 11($sp)
	sltu	$13, $13, $12
	bnez	$13, L.58
L.61:
	addu	$13, $0, $6
	sequ	$13, $13, $0
	bnez	$13, L.62
	lw	$13, 0($6)
	sw	$13, 10($sp)
	lw	$13, 1($6)
	lw	$12, 11($sp)
	sneu	$13, $13, $12
	bnez	$13, L.64
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	sw	$6, 2($sp)
	jal	hole_delete2
	la	$13, used_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	merge_holes
	j	L.65
L.64:
	lw	$13, 11($sp)
	lw	$12, 0($6)
	addu	$13, $13, $12
	sw	$13, 0($6)
	addui	$13, $6, 1
	lw	$12, 0($13)
	lw	$11, 11($sp)
	subu	$12, $12, $11
	sw	$12, 0($13)
	la	$13, pending_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
	lw	$13, 10($sp)
	sw	$13, 0($6)
	lw	$13, 11($sp)
	sw	$13, 1($6)
	la	$13, used_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	hole_enqueue_head
L.65:
	lw	$1, 10($sp)
	j	L.55
L.62:
	lw	$13, 11($sp)
	sw	$13, 0($sp)
	jal	_sbrk
	addu	$13, $0, $1
	sw	$13, 9($sp)
	addu	$13, $0, $13
	sequ	$13, $13, $0
	bnez	$13, L.66
	la	$13, pending_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
	addu	$13, $0, $13
	sequ	$13, $13, $0
	bnez	$13, L.68
	lw	$13, 9($sp)
	sw	$13, 0($6)
	lw	$13, 11($sp)
	sw	$13, 1($6)
	la	$13, used_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	hole_enqueue_head
	lw	$1, 9($sp)
	j	L.55
L.68:
L.66:
	addu	$1, $0, $0
L.55:
	lw	$6, 3($sp)
	lw	$7, 4($sp)
	lw	$11, 5($sp)
	lw	$12, 6($sp)
	lw	$13, 7($sp)
	lw	$ra, 8($sp)
	addui	$sp, $sp, 11
	jr	$ra
.global	_free
_free:
	subui	$sp, $sp, 10
	sw	$5, 2($sp)
	sw	$6, 3($sp)
	sw	$7, 4($sp)
	sw	$12, 5($sp)
	sw	$13, 6($sp)
	sw	$ra, 7($sp)
	lw	$7, 10($sp)
	lw	$6, used_holes($0)
	addu	$5, $0, $0
	sw	$0, 9($sp)
	sw	$0, 8($sp)
	j	L.72
L.71:
	lw	$6, 2($6)
L.72:
	addu	$13, $0, $6
	sequ	$13, $13, $0
	bnez	$13, L.74
	lw	$13, 0($6)
	addu	$13, $0, $13
	addu	$12, $0, $7
	sneu	$13, $13, $12
	bnez	$13, L.71
L.74:
	addu	$13, $0, $6
	sequ	$13, $13, $0
	bnez	$13, L.75
	addu	$5, $0, $0
	j	L.80
L.77:
	lhi	$13, 0xffff
	ori	$13, $13, 0xffff
	sw	$13, 0($7)
	addui	$7, $7, 1
L.78:
	addi	$5, $5, 1
L.80:
	addu	$13, $0, $5
	lw	$12, 1($6)
	sltu	$13, $13, $12
	bnez	$13, L.77
	la	$13, used_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	hole_delete
	addu	$13, $0, $1
	seq	$13, $13, $0
	bnez	$13, L.76
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	merge_holes
	addu	$13, $0, $1
	seq	$13, $13, $0
	bnez	$13, L.76
	j	L.76
L.75:
	la	$13, L.85
	sw	$13, 0($sp)
	lw	$13, 10($sp)
	sw	$13, 1($sp)
	jal	printf
L.76:
L.70:
	lw	$5, 2($sp)
	lw	$6, 3($sp)
	lw	$7, 4($sp)
	lw	$12, 5($sp)
	lw	$13, 6($sp)
	lw	$ra, 7($sp)
	addui	$sp, $sp, 10
	jr	$ra
.global	merge_holes
merge_holes:
	subui	$sp, $sp, 7
	sw	$7, 2($sp)
	sw	$11, 3($sp)
	sw	$12, 4($sp)
	sw	$13, 5($sp)
	sw	$ra, 6($sp)
	lw	$13, 7($sp)
	lw	$7, 0($13)
	lw	$13, 8($sp)
	lw	$12, 1($13)
	lw	$13, 0($13)
	addu	$13, $12, $13
	addu	$13, $0, $13
	lw	$12, FREE_MEM_BEGIN($0)
	addu	$12, $0, $12
	addu	$12, $0, $12
	sneu	$13, $13, $12
	bnez	$13, L.90
	lw	$13, 8($sp)
	lw	$12, FREE_MEM_BEGIN($0)
	lw	$11, 1($13)
	subu	$12, $12, $11
	sw	$12, FREE_MEM_BEGIN($0)
	la	$12, pending_holes
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	jal	hole_enqueue_head
	addui	$1, $0, 1
	j	L.86
L.89:
	lw	$13, 1($7)
	lw	$12, 0($7)
	addu	$13, $13, $12
	addu	$13, $0, $13
	lw	$12, 8($sp)
	lw	$12, 0($12)
	addu	$12, $0, $12
	sneu	$13, $13, $12
	bnez	$13, L.92
	addui	$13, $7, 1
	lw	$12, 0($13)
	lw	$11, 8($sp)
	lw	$11, 1($11)
	addu	$12, $12, $11
	sw	$12, 0($13)
	j	L.91
L.92:
	lw	$13, 8($sp)
	lw	$12, 1($13)
	lw	$13, 0($13)
	addu	$13, $12, $13
	addu	$13, $0, $13
	lw	$12, 0($7)
	addu	$12, $0, $12
	sneu	$13, $13, $12
	bnez	$13, L.94
	lw	$13, 0($7)
	lw	$12, 8($sp)
	lw	$12, 1($12)
	subu	$13, $13, $12
	sw	$13, 0($7)
	addui	$13, $7, 1
	lw	$12, 0($13)
	lw	$11, 8($sp)
	lw	$11, 1($11)
	addu	$12, $12, $11
	sw	$12, 0($13)
	j	L.91
L.94:
	lw	$7, 2($7)
L.90:
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.89
L.91:
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.96
	la	$13, pending_holes
	sw	$13, 0($sp)
	lw	$13, 8($sp)
	sw	$13, 1($sp)
	jal	hole_enqueue_head
	addui	$1, $0, 1
	j	L.86
L.96:
	lw	$13, 7($sp)
	sw	$13, 0($sp)
	lw	$13, 8($sp)
	sw	$13, 1($sp)
	jal	hole_enqueue_head
	addu	$1, $0, $0
L.86:
	lw	$7, 2($sp)
	lw	$11, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 7
	jr	$ra
.global	hole_list_overview
hole_list_overview:
	subui	$sp, $sp, 6
	sw	$7, 3($sp)
	sw	$13, 4($sp)
	sw	$ra, 5($sp)
	lw	$7, unused_holes($0)
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.103
	la	$13, L.101
	sw	$13, 0($sp)
	jal	printf
	j	L.103
L.102:
	la	$13, L.105
	sw	$13, 0($sp)
	lw	$13, 0($7)
	sw	$13, 1($sp)
	lw	$13, 1($7)
	sw	$13, 2($sp)
	jal	printf
	lw	$7, 2($7)
L.103:
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.102
	lw	$7, used_holes($0)
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.110
	la	$13, L.108
	sw	$13, 0($sp)
	jal	printf
	j	L.110
L.109:
	la	$13, L.112
	sw	$13, 0($sp)
	lw	$13, 0($7)
	sw	$13, 1($sp)
	lw	$13, 1($7)
	sw	$13, 2($sp)
	jal	printf
	lw	$7, 2($7)
L.110:
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.109
L.98:
	lw	$7, 3($sp)
	lw	$13, 4($sp)
	lw	$ra, 5($sp)
	addui	$sp, $sp, 6
	jr	$ra
.global	memcpy
memcpy:
	subui	$sp, $sp, 4
	sw	$6, 0($sp)
	sw	$7, 1($sp)
	sw	$12, 2($sp)
	sw	$13, 3($sp)
	lw	$7, 4($sp)
	lw	$6, 5($sp)
	lw	$13, 6($sp)
	sequ	$13, $13, $0
	bnez	$13, L.114
	lw	$13, 6($sp)
	addui	$12, $0, 1
	addu	$13, $13, $12
	sw	$13, 6($sp)
	j	L.117
L.116:
	addu	$13, $0, $7
	addui	$7, $13, 1
	addu	$12, $0, $6
	addui	$6, $12, 1
	lw	$12, 0($12)
	sw	$12, 0($13)
L.117:
	lw	$13, 6($sp)
	addui	$12, $0, 1
	subu	$13, $13, $12
	sw	$13, 6($sp)
	sneu	$13, $13, $0
	bnez	$13, L.116
L.114:
	lw	$1, 4($sp)
L.113:
	lw	$6, 0($sp)
	lw	$7, 1($sp)
	lw	$12, 2($sp)
	lw	$13, 3($sp)
	addui	$sp, $sp, 4
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
L.123:
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
L.124:
	addi	$6, $6, 1
	slti	$13, $6, 100
	bnez	$13, L.123
L.119:
	lw	$6, 2($sp)
	lw	$7, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 7
	jr	$ra
.global	sizeof_hole_t
sizeof_hole_t:
	subui	$sp, $sp, 9
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	addui	$13, $sp, 6
	addu	$13, $0, $13
	addui	$12, $sp, 3
	addu	$12, $0, $12
	subu	$13, $13, $12
	addu	$13, $0, $13
	sw	$13, 2($sp)
	lw	$1, 2($sp)
L.127:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 9
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
.extern	proc_table 1680
.data
L.112:
	.asciiz	"used hole start %x, length %d\n"
L.108:
	.asciiz	"used holes empty\n"
L.105:
	.asciiz	"unused hole start %x, length %d\n"
L.101:
	.asciiz	"unused hole empty\n"
L.85:
	.asciiz	"nothing found to be freed at addr %x\n"
L.49:
	.asciiz	"\r\nfree memory begin 0x%x\r\n"
L.28:
	.asciiz	"delete: tail not null"
L.19:
	.asciiz	"deq: tail not null"
