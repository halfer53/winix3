.text
enqueue_tail:
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
	sw	$12, 54($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
L.9:
	lw	$13, 3($sp)
	sw	$0, 54($13)
L.7:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 2
	jr	$ra
enqueue_head:
	subui	$sp, $sp, 2
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	lw	$13, 2($sp)
	lw	$13, 0($13)
	addu	$13, $0, $13
	sneu	$13, $13, $0
	bnez	$13, L.11
	lw	$13, 3($sp)
	sw	$0, 54($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 1($13)
	sw	$12, 0($13)
	j	L.12
L.11:
	lw	$13, 3($sp)
	lw	$12, 2($sp)
	lw	$12, 0($12)
	sw	$12, 54($13)
	lw	$13, 2($sp)
	lw	$12, 3($sp)
	sw	$12, 0($13)
L.12:
L.10:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 2
	jr	$ra
dequeue:
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
	lw	$12, 54($7)
	sw	$12, 0($13)
L.21:
	sw	$0, 54($7)
	addu	$1, $0, $7
L.13:
	lw	$6, 2($sp)
	lw	$7, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 7
	jr	$ra
get_free_proc:
	subui	$sp, $sp, 6
	sw	$6, 1($sp)
	sw	$7, 2($sp)
	sw	$12, 3($sp)
	sw	$13, 4($sp)
	sw	$ra, 5($sp)
	la	$13, free_proc
	sw	$13, 0($sp)
	jal	dequeue
	addu	$13, $0, $1
	addu	$6, $0, $13
	addu	$13, $0, $6
	sequ	$13, $13, $0
	bnez	$13, L.23
	addu	$7, $0, $0
L.25:
	addu	$13, $7, $6
	lhi	$12, 0xffff
	ori	$12, $12, 0xffff
	sw	$12, 0($13)
L.26:
	addi	$7, $7, 1
	slti	$13, $7, 13
	bnez	$13, L.25
	addu	$7, $0, $0
L.29:
	addui	$13, $0, 200
	lw	$12, 81($6)
	mult	$13, $13, $12
	la	$12, proc_stacks
	addu	$13, $13, $12
	addu	$13, $7, $13
	lhi	$12, 0xffff
	ori	$12, $12, 0xffff
	sw	$12, 0($13)
L.30:
	addi	$7, $7, 1
	slti	$13, $7, 200
	bnez	$13, L.29
	addui	$13, $0, 200
	lw	$12, 81($6)
	mult	$13, $13, $12
	la	$12, proc_stacks
	addu	$13, $13, $12
	sw	$13, 13($6)
	addui	$13, $6, 13
	lw	$12, 0($13)
	addui	$12, $12, 200
	sw	$12, 0($13)
	sw	$0, 14($6)
	sw	$0, 15($6)
	sw	$0, 16($6)
	sw	$0, 17($6)
	addui	$13, $0, 4089
	sw	$13, 18($6)
	sw	$0, 51($6)
	addui	$13, $0, 100
	sw	$13, 52($6)
	sw	$0, 53($6)
	sw	$0, 58($6)
	addui	$13, $0, 1
	sw	$13, 79($6)
	sw	$0, 80($6)
	sw	$0, 55($6)
	sw	$0, 56($6)
	sw	$0, 57($6)
L.23:
	addu	$1, $0, $6
L.22:
	lw	$6, 1($sp)
	lw	$7, 2($sp)
	lw	$12, 3($sp)
	lw	$13, 4($sp)
	lw	$ra, 5($sp)
	addui	$sp, $sp, 6
	jr	$ra
pick_proc:
	subui	$sp, $sp, 5
	sw	$7, 1($sp)
	sw	$12, 2($sp)
	sw	$13, 3($sp)
	sw	$ra, 4($sp)
	addu	$7, $0, $0
L.34:
	slli	$13, $7, 1
	lw	$13, ready_q($13)
	addu	$13, $0, $13
	sequ	$13, $13, $0
	bnez	$13, L.38
	slli	$13, $7, 1
	la	$12, ready_q
	addu	$13, $13, $12
	sw	$13, 0($sp)
	jal	dequeue
	addu	$13, $0, $1
	addu	$1, $0, $13
	j	L.33
L.38:
L.35:
	addi	$7, $7, 1
	slti	$13, $7, 5
	bnez	$13, L.34
	addu	$1, $0, $0
L.33:
	lw	$7, 1($sp)
	lw	$12, 2($sp)
	lw	$13, 3($sp)
	lw	$ra, 4($sp)
	addui	$sp, $sp, 5
	jr	$ra
.global	new_proc
new_proc:
	subui	$sp, $sp, 8
	sw	$6, 2($sp)
	sw	$7, 3($sp)
	sw	$12, 4($sp)
	sw	$13, 5($sp)
	sw	$ra, 6($sp)
	addu	$6, $0, $0
	lw	$13, 9($sp)
	sw	$13, 7($sp)
	sgt	$13, $0, $13
	bnez	$13, L.43
	lw	$13, 7($sp)
	slti	$13, $13, 5
	bnez	$13, L.41
L.43:
	addu	$1, $0, $0
	j	L.40
L.41:
	jal	get_free_proc
	addu	$13, $0, $1
	addu	$6, $0, $13
	addu	$13, $0, $13
	sequ	$13, $13, $0
	bnez	$13, L.44
	lw	$13, 9($sp)
	sw	$13, 51($6)
	lw	$13, 8($sp)
	sw	$13, 15($6)
	addu	$7, $0, $0
L.46:
	addui	$13, $6, 59
	addu	$13, $7, $13
	lw	$12, 10($sp)
	lw	$12, 0($12)
	sw	$12, 0($13)
	lw	$13, 10($sp)
	addui	$12, $13, 1
	sw	$12, 10($sp)
	lw	$13, 0($13)
	sne	$13, $13, $0
	bnez	$13, L.50
	j	L.48
L.50:
L.47:
	addi	$7, $7, 1
	slti	$13, $7, 20
	bnez	$13, L.46
L.48:
	addui	$13, $6, 19
	sw	$13, 17($6)
	addu	$7, $0, $0
L.52:
	addui	$13, $6, 19
	addu	$13, $7, $13
	lhi	$12, 0xffff
	ori	$12, $12, 0xffff
	sw	$12, 0($13)
L.53:
	addi	$7, $7, 1
	slti	$13, $7, 32
	bnez	$13, L.52
	addui	$13, $0, 2
	sw	$13, 79($6)
	lw	$13, 9($sp)
	slli	$13, $13, 1
	la	$12, ready_q
	addu	$13, $13, $12
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	enqueue_tail
L.44:
	addu	$1, $0, $6
L.40:
	lw	$6, 2($sp)
	lw	$7, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 8
	jr	$ra
.global	end_process
end_process:
	subui	$sp, $sp, 4
	sw	$13, 2($sp)
	sw	$ra, 3($sp)
	lw	$13, 4($sp)
	sw	$0, 79($13)
	la	$13, free_proc
	sw	$13, 0($sp)
	lw	$13, 4($sp)
	sw	$13, 1($sp)
	jal	enqueue_tail
L.56:
	lw	$13, 2($sp)
	lw	$ra, 3($sp)
	addui	$sp, $sp, 4
	jr	$ra
.global	sched
sched:
	subui	$sp, $sp, 8
	sw	$7, 2($sp)
	sw	$11, 3($sp)
	sw	$12, 4($sp)
	sw	$13, 5($sp)
	sw	$ra, 6($sp)
	lw	$13, current_proc($0)
	sw	$13, 7($sp)
	addu	$12, $0, $13
	sequ	$13, $12, $0
	bnez	$13, L.58
	lw	$13, 7($sp)
	lw	$13, 80($13)
	sne	$13, $13, $0
	bnez	$13, L.58
	lw	$13, current_proc($0)
	addui	$13, $13, 58
	lw	$12, 0($13)
	addi	$12, $12, 1
	sw	$12, 0($13)
	lw	$13, current_proc($0)
	addui	$13, $13, 53
	lw	$12, 0($13)
	subi	$12, $12, 1
	sw	$12, 0($13)
	seq	$13, $12, $0
	bnez	$13, L.60
	lw	$13, current_proc($0)
	lw	$12, 51($13)
	slli	$12, $12, 1
	la	$11, ready_q
	addu	$12, $12, $11
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	jal	enqueue_head
	j	L.61
L.60:
	lw	$13, current_proc($0)
	lw	$12, 51($13)
	slli	$12, $12, 1
	la	$11, ready_q
	addu	$12, $12, $11
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	jal	enqueue_tail
L.61:
L.58:
	jal	pick_proc
	addu	$13, $0, $1
	sw	$13, current_proc($0)
	lw	$13, current_proc($0)
	addu	$13, $0, $13
	sequ	$13, $13, $0
	bnez	$13, L.64
	addui	$7, $0, 1
	j	L.65
L.64:
	addu	$7, $0, $0
L.65:
	sw	$7, 0($sp)
	la	$13, L.63
	sw	$13, 1($sp)
	jal	assert
	lw	$13, current_proc($0)
	lw	$13, 53($13)
	sne	$13, $13, $0
	bnez	$13, L.66
	lw	$13, current_proc($0)
	lw	$12, 52($13)
	sw	$12, 53($13)
L.66:
	jal	wramp_load_context
L.57:
	lw	$7, 2($sp)
	lw	$11, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 8
	jr	$ra
.global	get_proc
get_proc:
	subui	$sp, $sp, 4
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	lw	$13, 4($sp)
	sw	$13, 3($sp)
	sgt	$13, $0, $13
	bnez	$13, L.69
	lw	$13, 3($sp)
	sgei	$13, $13, 20
	bnez	$13, L.69
	addui	$13, $0, 82
	lw	$12, 4($sp)
	mult	$13, $13, $12
	la	$12, proc_table
	addu	$13, $13, $12
	sw	$13, 2($sp)
	lw	$13, 2($sp)
	lw	$13, 79($13)
	seq	$13, $13, $0
	bnez	$13, L.71
	lw	$1, 2($sp)
	j	L.68
L.71:
L.69:
	addu	$1, $0, $0
L.68:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 4
	jr	$ra
.global	wini_send
wini_send:
	subui	$sp, $sp, 10
	sw	$7, 2($sp)
	sw	$8, 3($sp)
	sw	$9, 4($sp)
	sw	$10, 5($sp)
	sw	$11, 6($sp)
	sw	$12, 7($sp)
	sw	$13, 8($sp)
	sw	$ra, 9($sp)
	lw	$13, current_proc($0)
	lw	$12, 11($sp)
	sw	$12, 57($13)
	lw	$13, 10($sp)
	sw	$13, 0($sp)
	jal	get_proc
	addu	$13, $0, $1
	addu	$7, $0, $13
	addu	$13, $0, $13
	sequ	$13, $13, $0
	bnez	$13, L.74
	lw	$13, 80($7)
	andi	$13, $13, 2
	seq	$13, $13, $0
	bnez	$13, L.76
	lw	$13, 57($7)
	lw	$9, 11($sp)
	lw	$8, 0($9)
	lw	$10, 1($9)
	sw	$8, 0($13)
	sw	$10, 1($13)
	lw	$8, 2($9)
	lw	$10, 3($9)
	sw	$8, 2($13)
	sw	$10, 3($13)
	lw	$8, 4($9)
	lw	$10, 5($9)
	sw	$8, 4($13)
	sw	$10, 5($13)
	lw	$8, 6($9)
	lw	$10, 7($9)
	sw	$8, 6($13)
	sw	$10, 7($13)
	addui	$13, $7, 80
	lw	$12, 0($13)
	lhi	$11, 0xffff
	ori	$11, $11, 0xfffd
	and	$12, $12, $11
	sw	$12, 0($13)
	lw	$13, 51($7)
	slli	$13, $13, 1
	la	$12, ready_q
	addu	$13, $13, $12
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	enqueue_head
	j	L.77
L.76:
	lw	$13, current_proc($0)
	addui	$13, $13, 80
	lw	$12, 0($13)
	ori	$12, $12, 1
	sw	$12, 0($13)
	lw	$13, current_proc($0)
	lw	$12, 55($7)
	sw	$12, 56($13)
	lw	$13, current_proc($0)
	sw	$13, 55($7)
L.77:
	addu	$1, $0, $0
	j	L.73
L.74:
	lhi	$1, 0xffff
	ori	$1, $1, 0xffff
L.73:
	lw	$7, 2($sp)
	lw	$8, 3($sp)
	lw	$9, 4($sp)
	lw	$10, 5($sp)
	lw	$11, 6($sp)
	lw	$12, 7($sp)
	lw	$13, 8($sp)
	lw	$ra, 9($sp)
	addui	$sp, $sp, 10
	jr	$ra
.global	wini_receive
wini_receive:
	subui	$sp, $sp, 10
	sw	$7, 2($sp)
	sw	$8, 3($sp)
	sw	$9, 4($sp)
	sw	$10, 5($sp)
	sw	$11, 6($sp)
	sw	$12, 7($sp)
	sw	$13, 8($sp)
	sw	$ra, 9($sp)
	lw	$13, current_proc($0)
	lw	$7, 55($13)
	addu	$13, $0, $7
	sequ	$13, $13, $0
	bnez	$13, L.79
	lw	$13, current_proc($0)
	lw	$12, 56($7)
	sw	$12, 55($13)
	lw	$13, 10($sp)
	lw	$9, 57($7)
	lw	$8, 0($9)
	lw	$10, 1($9)
	sw	$8, 0($13)
	sw	$10, 1($13)
	lw	$8, 2($9)
	lw	$10, 3($9)
	sw	$8, 2($13)
	sw	$10, 3($13)
	lw	$8, 4($9)
	lw	$10, 5($9)
	sw	$8, 4($13)
	sw	$10, 5($13)
	lw	$8, 6($9)
	lw	$10, 7($9)
	sw	$8, 6($13)
	sw	$10, 7($13)
	addui	$13, $7, 80
	lw	$12, 0($13)
	lhi	$11, 0xffff
	ori	$11, $11, 0xfffe
	and	$12, $12, $11
	sw	$12, 0($13)
	lw	$13, 51($7)
	slli	$13, $13, 1
	la	$12, ready_q
	addu	$13, $13, $12
	sw	$13, 0($sp)
	sw	$7, 1($sp)
	jal	enqueue_head
	j	L.80
L.79:
	lw	$13, current_proc($0)
	lw	$12, 10($sp)
	sw	$12, 57($13)
	lw	$13, current_proc($0)
	addui	$13, $13, 80
	lw	$12, 0($13)
	ori	$12, $12, 2
	sw	$12, 0($13)
L.80:
	addu	$1, $0, $0
L.78:
	lw	$7, 2($sp)
	lw	$8, 3($sp)
	lw	$9, 4($sp)
	lw	$10, 5($sp)
	lw	$11, 6($sp)
	lw	$12, 7($sp)
	lw	$13, 8($sp)
	lw	$ra, 9($sp)
	addui	$sp, $sp, 10
	jr	$ra
.global	init_proc
init_proc:
	subui	$sp, $sp, 7
	sw	$6, 2($sp)
	sw	$7, 3($sp)
	sw	$12, 4($sp)
	sw	$13, 5($sp)
	sw	$ra, 6($sp)
	addu	$7, $0, $0
L.82:
	slli	$13, $7, 1
	sw	$0, ready_q($13)
	slli	$13, $7, 1
	sw	$0, ready_q+1($13)
L.83:
	addi	$7, $7, 1
	slti	$13, $7, 5
	bnez	$13, L.82
	addu	$13, $0, $0
	sw	$13, free_proc+1($0)
	sw	$13, free_proc($0)
	addu	$7, $0, $0
L.88:
	addui	$13, $0, 82
	mult	$13, $13, $7
	la	$12, proc_table
	addu	$6, $13, $12
	sw	$0, 79($6)
	la	$13, free_proc
	sw	$13, 0($sp)
	sw	$6, 1($sp)
	jal	enqueue_tail
	addui	$13, $0, 82
	mult	$13, $13, $7
	sw	$7, proc_table+81($13)
L.89:
	addi	$7, $7, 1
	slti	$13, $7, 20
	bnez	$13, L.88
	sw	$0, current_proc($0)
L.81:
	lw	$6, 2($sp)
	lw	$7, 3($sp)
	lw	$12, 4($sp)
	lw	$13, 5($sp)
	lw	$ra, 6($sp)
	addui	$sp, $sp, 7
	jr	$ra
.bss
proc_stacks:
	.space	4000
free_proc:
	.space	2
ready_q:
	.space	10
.extern	FREE_MEM_END 1
.extern	FREE_MEM_BEGIN 1
.extern	BSS_END 1
.extern	DATA_END 1
.extern	TEXT_END 1
.extern	BSS_BEGIN 1
.extern	DATA_BEGIN 1
.extern	TEXT_BEGIN 1
.extern	system_uptime 1
.global	current_proc
current_proc:
	.space	1
.global	proc_table
proc_table:
	.space	1640
.data
L.63:
	.asciiz	"sched: current_proc null"
L.17:
	.asciiz	"deq: tail not null"
