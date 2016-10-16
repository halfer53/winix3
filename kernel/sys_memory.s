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
	lhi	$1, 0xffff
	ori	$1, $1, 0xffff
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
	addu	$12, $0, $0
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.38
L.37:
	lw	$13, 2($7)
	sw	$13, 2($6)
L.38:
	addui	$1, $0, 1
	j	L.24
L.35:
	lhi	$1, 0xffff
	ori	$1, $1, 0xffff
L.24:
	lw	$5, 2($sp)
	lw	$6, 3($sp)
	lw	$7, 4($sp)
	lw	$12, 5($sp)
	lw	$13, 6($sp)
	lw	$ra, 7($sp)
	addui	$sp, $sp, 9
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
	la	$13, L.40
	sw	$13, 0($sp)
	lw	$13, FREE_MEM_BEGIN($0)
	sw	$13, 1($sp)
	jal	printf
L.39:
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
	bnez	$13, L.42
	lw	$13, 3($sp)
	lw	$12, FREE_MEM_BEGIN($0)
	addu	$13, $13, $12
	lw	$12, FREE_MEM_END($0)
	sleu	$13, $13, $12
	bnez	$13, L.44
	addu	$1, $0, $0
	j	L.41
L.44:
L.42:
	lw	$13, FREE_MEM_BEGIN($0)
	lw	$12, 3($sp)
	addu	$13, $13, $12
	sw	$13, FREE_MEM_BEGIN($0)
	lw	$13, 2($sp)
	addu	$1, $0, $13
L.41:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 3
	jr	$ra
.global	_malloc
_malloc:
	subui	$sp, $sp, 12
	sw	$6, 2($sp)
	sw	$7, 3($sp)
	sw	$12, 4($sp)
	sw	$13, 5($sp)
	sw	$ra, 6($sp)
	addu	$6, $0, $0
	addu	$7, $0, $0
	sw	$0, 9($sp)
	sw	$0, 8($sp)
	sw	$0, 7($sp)
	lw	$13, 12($sp)
	sneu	$13, $13, $0
	bnez	$13, L.47
	addu	$1, $0, $0
	j	L.46
L.47:
	addu	$13, $0, $0
	sw	$13, 11($sp)
	sw	$13, 10($sp)
L.50:
	la	$13, unused_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$7, $0, $13
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.53
	lw	$13, 1($7)
	lw	$12, 12($sp)
	sgeu	$13, $13, $12
	bnez	$13, L.52
	addui	$13, $sp, 10
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_head
L.56:
L.53:
L.51:
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.50
L.52:
	addui	$13, $sp, 10
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
	j	L.58
L.57:
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	hole_enqueue_head
	addui	$13, $sp, 10
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
L.58:
	addu	$13, $0, $6
	sneu	$13, $13, $0
	bnez	$13, L.57
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.60
	lw	$13, 12($sp)
	sw	$13, 0($sp)
	jal	_sbrk
	addu	$13, $0, $1
	sw	$13, 9($sp)
	lw	$13, 9($sp)
	addu	$13, $0, $13
	sequ	$13, $13, $0
	bnez	$13, L.62
	la	$13, pending_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$7, $0, $13
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.64
	lw	$13, 9($sp)
	sw	$13, 0($7)
	lw	$13, 12($sp)
	sw	$13, 1($7)
	la	$13, used_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_head
	lw	$1, 9($sp)
	j	L.46
L.64:
	addu	$1, $0, $0
	j	L.46
L.62:
	addu	$1, $0, $0
	j	L.46
L.60:
	lw	$13, 1($7)
	lw	$12, 12($sp)
	sltu	$13, $13, $12
	bnez	$13, L.66
	lw	$13, 0($7)
	sw	$13, 9($sp)
	lw	$13, 1($7)
	lw	$12, 12($sp)
	sleu	$13, $13, $12
	bnez	$13, L.68
	la	$13, pending_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
	lw	$13, 12($sp)
	lw	$12, 0($7)
	addu	$13, $13, $12
	sw	$13, 0($6)
	lw	$13, 1($7)
	lw	$12, 12($sp)
	subu	$13, $13, $12
	sw	$13, 1($6)
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	hole_enqueue_tail
L.68:
	lw	$13, 12($sp)
	sw	$13, 1($7)
	lw	$1, 9($sp)
	j	L.46
L.66:
	la	$13, L.70
	sw	$13, 0($sp)
	jal	printf
	addu	$1, $0, $0
L.46:
	lw	$6, 2($sp)
	lw	$7, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 12
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
L.73:
	la	$13, used_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$7, $0, $13
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.76
	lw	$13, 0($7)
	addu	$13, $0, $13
	lw	$12, 14($sp)
	addu	$12, $0, $12
	sequ	$13, $13, $12
	bnez	$13, L.75
	addui	$13, $sp, 12
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_head
L.79:
L.76:
L.74:
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.73
L.75:
	addui	$13, $sp, 12
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
	j	L.81
L.80:
	la	$13, used_holes
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	hole_enqueue_head
	addui	$13, $sp, 12
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
L.81:
	addu	$13, $0, $6
	sneu	$13, $13, $0
	bnez	$13, L.80
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.83
	la	$13, L.85
	sw	$13, 0($sp)
	lw	$13, 0($7)
	sw	$13, 1($sp)
	lw	$13, 1($7)
	sw	$13, 2($sp)
	jal	printf
	lw	$5, 14($sp)
	addu	$4, $0, $0
	j	L.89
L.86:
	lhi	$13, 0xffff
	ori	$13, $13, 0xffff
	sw	$13, 0($5)
	addui	$5, $5, 1
L.87:
	addi	$4, $4, 1
L.89:
	addu	$13, $0, $4
	lw	$12, 1($7)
	sltu	$13, $13, $12
	bnez	$13, L.86
	sw	$7, 0($sp)
	jal	merge_holes
	addu	$13, $0, $1
	lhi	$12, 0xffff
	ori	$12, $12, 0xffff
	seq	$13, $13, $12
	bnez	$13, L.90
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_head
L.90:
L.83:
L.71:
	lw	$4, 3($sp)
	lw	$5, 4($sp)
	lw	$6, 5($sp)
	lw	$7, 6($sp)
	lw	$12, 7($sp)
	lw	$13, 8($sp)
	lw	$ra, 9($sp)
	addui	$sp, $sp, 14
	jr	$ra
.global	merge_holes
merge_holes:
	subui	$sp, $sp, 9
	sw	$5, 2($sp)
	sw	$6, 3($sp)
	sw	$7, 4($sp)
	sw	$11, 5($sp)
	sw	$12, 6($sp)
	sw	$13, 7($sp)
	sw	$ra, 8($sp)
	lw	$7, unused_holes($0)
	j	L.94
L.93:
	lw	$13, 1($7)
	lw	$12, 0($7)
	addu	$5, $13, $12
	lw	$13, 9($sp)
	lw	$12, 1($13)
	lw	$13, 0($13)
	addu	$6, $12, $13
	addu	$13, $0, $6
	lw	$12, FREE_MEM_BEGIN($0)
	sneu	$13, $13, $12
	bnez	$13, L.96
	lw	$13, 9($sp)
	lw	$12, FREE_MEM_BEGIN($0)
	lw	$11, 1($13)
	subu	$12, $12, $11
	sw	$12, FREE_MEM_BEGIN($0)
	la	$12, pending_holes
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	jal	hole_enqueue_tail
	lhi	$1, 0xffff
	ori	$1, $1, 0xffff
	j	L.92
L.96:
	addu	$13, $0, $5
	lw	$12, 9($sp)
	lw	$12, 0($12)
	addu	$12, $0, $12
	sneu	$13, $13, $12
	bnez	$13, L.98
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_delete
	addu	$13, $0, $1
	lhi	$12, 0xffff
	ori	$12, $12, 0xffff
	seq	$13, $13, $12
	bnez	$13, L.100
	lw	$13, 9($sp)
	lw	$12, 0($13)
	lw	$11, 1($7)
	subu	$12, $12, $11
	sw	$12, 0($13)
	lw	$13, 9($sp)
	addui	$13, $13, 1
	lw	$12, 0($13)
	lw	$11, 1($7)
	addu	$12, $12, $11
	sw	$12, 0($13)
	sw	$0, 0($7)
	sw	$0, 1($7)
	la	$13, pending_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_head
	j	L.95
L.100:
	la	$13, L.102
	sw	$13, 0($sp)
	jal	printf
	lhi	$1, 0xffff
	ori	$1, $1, 0xffff
	j	L.92
L.98:
	addu	$13, $0, $6
	lw	$12, 0($7)
	addu	$12, $0, $12
	sneu	$13, $13, $12
	bnez	$13, L.103
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_delete
	addu	$13, $0, $1
	lhi	$12, 0xffff
	ori	$12, $12, 0xffff
	seq	$13, $13, $12
	bnez	$13, L.105
	lw	$13, 9($sp)
	addui	$13, $13, 1
	lw	$12, 0($13)
	lw	$11, 1($7)
	addu	$12, $12, $11
	sw	$12, 0($13)
	sw	$0, 0($7)
	sw	$0, 1($7)
	la	$13, pending_holes
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	hole_enqueue_head
	j	L.95
L.105:
	la	$13, L.102
	sw	$13, 0($sp)
	jal	printf
	lhi	$1, 0xffff
	ori	$1, $1, 0xffff
	j	L.92
L.103:
L.94:
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.93
L.95:
	addui	$1, $0, 1
L.92:
	lw	$5, 2($sp)
	lw	$6, 3($sp)
	lw	$7, 4($sp)
	lw	$11, 5($sp)
	lw	$12, 6($sp)
	lw	$13, 7($sp)
	lw	$ra, 8($sp)
	addui	$sp, $sp, 9
	jr	$ra
.global	hole_overview
hole_overview:
	subui	$sp, $sp, 6
	sw	$7, 3($sp)
	sw	$13, 4($sp)
	sw	$ra, 5($sp)
	lw	$13, 6($sp)
	lw	$7, 0($13)
	j	L.109
L.108:
	la	$13, L.111
	sw	$13, 0($sp)
	lw	$13, 0($7)
	sw	$13, 1($sp)
	lw	$13, 1($7)
	sw	$13, 2($sp)
	jal	printf
	lw	$7, 2($7)
L.109:
	addu	$13, $0, $7
	sneu	$13, $13, $0
	bnez	$13, L.108
L.107:
	lw	$7, 3($sp)
	lw	$13, 4($sp)
	lw	$ra, 5($sp)
	addui	$sp, $sp, 6
	jr	$ra
.global	used_hole_overview
used_hole_overview:
	subui	$sp, $sp, 4
	sw	$13, 2($sp)
	sw	$ra, 3($sp)
	la	$13, L.113
	sw	$13, 0($sp)
	lw	$13, 4($sp)
	sw	$13, 1($sp)
	jal	printf
	la	$13, used_holes
	sw	$13, 0($sp)
	jal	hole_overview
L.112:
	lw	$13, 2($sp)
	lw	$ra, 3($sp)
	addui	$sp, $sp, 4
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
	bnez	$13, L.115
	lw	$13, 6($sp)
	addui	$12, $0, 1
	addu	$13, $13, $12
	sw	$13, 6($sp)
	j	L.118
L.117:
	addu	$13, $0, $7
	addui	$7, $13, 1
	addu	$12, $0, $6
	addui	$6, $12, 1
	lw	$12, 0($12)
	sw	$12, 0($13)
L.118:
	lw	$13, 6($sp)
	addui	$12, $0, 1
	subu	$13, $13, $12
	sw	$13, 6($sp)
	sneu	$13, $13, $0
	bnez	$13, L.117
L.115:
	lw	$1, 4($sp)
L.114:
	lw	$6, 0($sp)
	lw	$7, 1($sp)
	lw	$12, 2($sp)
	lw	$13, 3($sp)
	addui	$sp, $sp, 4
	jr	$ra
.global	wipe_mem
wipe_mem:
	subui	$sp, $sp, 9
	sw	$5, 3($sp)
	sw	$6, 4($sp)
	sw	$7, 5($sp)
	sw	$12, 6($sp)
	sw	$13, 7($sp)
	sw	$ra, 8($sp)
	addu	$5, $0, $0
	addu	$7, $0, $0
	lw	$6, 9($sp)
	la	$13, L.121
	sw	$13, 0($sp)
	lw	$13, 9($sp)
	sw	$13, 1($sp)
	lw	$13, 10($sp)
	sw	$13, 2($sp)
	jal	printf
	addu	$7, $0, $0
	j	L.125
L.122:
	lhi	$13, 0xffff
	ori	$13, $13, 0xffff
	sw	$13, 0($6)
	addui	$6, $6, 1
L.123:
	addi	$7, $7, 1
L.125:
	addu	$13, $0, $7
	lw	$12, 10($sp)
	sltu	$13, $13, $12
	bnez	$13, L.122
	la	$13, pending_holes
	sw	$13, 0($sp)
	jal	hole_dequeue
	addu	$13, $0, $1
	addu	$5, $0, $13
	lw	$13, 9($sp)
	sw	$13, 0($5)
	lw	$13, 10($sp)
	sw	$13, 1($5)
	la	$13, L.126
	sw	$13, 0($sp)
	lw	$13, 9($sp)
	sw	$13, 1($sp)
	lw	$13, 10($sp)
	sw	$13, 2($sp)
	jal	printf
	sw	$5, 0($sp)
	jal	merge_holes
	addu	$13, $0, $1
	lhi	$12, 0xffff
	ori	$12, $12, 0xffff
	seq	$13, $13, $12
	bnez	$13, L.127
	la	$13, unused_holes
	sw	$13, 0($sp)
	sw	$5, 1($sp)
	jal	hole_enqueue_head
L.127:
L.120:
	lw	$5, 3($sp)
	lw	$6, 4($sp)
	lw	$7, 5($sp)
	lw	$12, 6($sp)
	lw	$13, 7($sp)
	lw	$ra, 8($sp)
	addui	$sp, $sp, 9
	jr	$ra
.global	load_BinRecord_Mem
load_BinRecord_Mem:
	subui	$sp, $sp, 9
	sw	$5, 3($sp)
	sw	$6, 4($sp)
	sw	$7, 5($sp)
	sw	$12, 6($sp)
	sw	$13, 7($sp)
	sw	$ra, 8($sp)
	addu	$7, $0, $0
	addu	$5, $0, $0
	lw	$13, 10($sp)
	sw	$13, 0($sp)
	jal	_malloc
	addu	$13, $0, $1
	addu	$6, $0, $13
	la	$13, L.130
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	lw	$13, 10($sp)
	sw	$13, 2($sp)
	jal	printf
	addu	$5, $0, $6
	addu	$7, $0, $0
	j	L.134
L.131:
	lw	$13, 9($sp)
	addu	$13, $7, $13
	lw	$13, 0($13)
	sw	$13, 0($6)
	addui	$6, $6, 1
L.132:
	addi	$7, $7, 1
L.134:
	addu	$13, $0, $7
	lw	$12, 10($sp)
	sltu	$13, $13, $12
	bnez	$13, L.131
	addu	$1, $0, $5
L.129:
	lw	$5, 3($sp)
	lw	$6, 4($sp)
	lw	$7, 5($sp)
	lw	$12, 6($sp)
	lw	$13, 7($sp)
	lw	$ra, 8($sp)
	addui	$sp, $sp, 9
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
L.139:
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
L.140:
	addi	$6, $6, 1
	slti	$13, $6, 100
	bnez	$13, L.139
L.135:
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
L.143:
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
L.130:
	.asciiz	"new malloced start %x, length %d\n"
L.126:
	.asciiz	"wipe hole start %x length %d\n"
L.121:
	.asciiz	"wipe start %x length %d\n"
L.113:
	.asciiz	"%s\n"
L.111:
	.asciiz	"hole start %x, length %d\n"
L.102:
	.asciiz	"delete unsuccessful\n"
L.85:
	.asciiz	"free: found start 0x%x, length %d\n\n"
L.70:
	.asciiz	"this shouldn't happen h==null but h->length < size"
L.40:
	.asciiz	"\r\nfree memory begin 0x%x\r\n"
L.28:
	.asciiz	"delete: tail not null"
L.19:
	.asciiz	"deq: tail not null"
