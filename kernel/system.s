.global	FREE_MEM_BEGIN
FREE_MEM_BEGIN:
	.word	0x0
.global	FREE_MEM_END
FREE_MEM_END:
	.word	0x0
.text
scan_memory:
	subui	$sp, $sp, 4
	sw	$12, 1($sp)
	sw	$13, 2($sp)
	sw	$ra, 3($sp)
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
	lw	$13, FREE_MEM_BEGIN($0)
	sw	$13, FREE_MEM_END($0)
L.8:
	lw	$13, FREE_MEM_END($0)
	addu	$12, $0, $13
	sw	$13, 0($12)
	lw	$13, FREE_MEM_END($0)
	addu	$12, $0, $13
	lw	$12, 0($12)
	sequ	$13, $12, $13
	bnez	$13, L.12
	j	L.10
L.12:
	lw	$13, FREE_MEM_END($0)
	addui	$12, $0, 8191
	and	$13, $13, $12
	sneu	$13, $13, $0
	bnez	$13, L.14
	addui	$13, $0, 46
	sw	$13, 0($sp)
	jal	putc
L.14:
L.9:
	lw	$13, FREE_MEM_END($0)
	addui	$12, $0, 1
	addu	$13, $13, $12
	sw	$13, FREE_MEM_END($0)
	j	L.8
L.10:
	lw	$13, FREE_MEM_END($0)
	lhi	$12, 0xffff
	ori	$12, $12, 0xfc00
	addu	$12, $0, $12
	and	$13, $13, $12
	sw	$13, FREE_MEM_END($0)
	lw	$13, FREE_MEM_END($0)
	addui	$12, $0, 1
	subu	$13, $13, $12
	sw	$13, FREE_MEM_END($0)
L.7:
	lw	$12, 1($sp)
	lw	$13, 2($sp)
	lw	$ra, 3($sp)
	addui	$sp, $sp, 4
	jr	$ra
.global	system_main
system_main:
	subui	$sp, $sp, 18
	sw	$6, 4($sp)
	sw	$7, 5($sp)
	sw	$12, 6($sp)
	sw	$13, 7($sp)
	sw	$ra, 8($sp)
	la	$13, L.17
	sw	$13, 0($sp)
	jal	printf
	jal	scan_memory
	la	$13, L.18
	sw	$13, 0($sp)
	lw	$13, FREE_MEM_END($0)
	lw	$12, FREE_MEM_BEGIN($0)
	subu	$13, $13, $12
	srli	$13, $13, 10
	sw	$13, 1($sp)
	jal	printf
	la	$13, L.19
	sw	$13, 0($sp)
	la	$13, TEXT_BEGIN
	sw	$13, 1($sp)
	la	$13, TEXT_END
	sw	$13, 2($sp)
	jal	printf
	la	$13, L.20
	sw	$13, 0($sp)
	la	$13, DATA_BEGIN
	sw	$13, 1($sp)
	la	$13, DATA_END
	sw	$13, 2($sp)
	jal	printf
	la	$13, L.21
	sw	$13, 0($sp)
	la	$13, BSS_BEGIN
	sw	$13, 1($sp)
	la	$13, BSS_END
	sw	$13, 2($sp)
	jal	printf
	la	$13, L.22
	sw	$13, 0($sp)
	lw	$13, FREE_MEM_BEGIN($0)
	sw	$13, 1($sp)
	lw	$13, FREE_MEM_END($0)
	sw	$13, 2($sp)
	jal	printf
	j	L.24
L.23:
	addui	$13, $sp, 10
	sw	$13, 0($sp)
	jal	winix_receive
	lw	$7, 10($sp)
	addui	$13, $0, 82
	mult	$13, $13, $7
	la	$12, proc_table
	addu	$6, $13, $12
	lw	$13, 11($sp)
	sw	$13, 9($sp)
	seqi	$13, $13, 2
	bnez	$13, L.29
	lw	$13, 9($sp)
	seqi	$13, $13, 4
	bnez	$13, L.31
	lw	$13, 9($sp)
	seqi	$13, $13, 5
	bnez	$13, L.33
	j	L.26
L.29:
	la	$13, L.30
	sw	$13, 0($sp)
	jal	printf
	j	L.27
L.31:
	lw	$13, system_uptime($0)
	sw	$13, 12($sp)
	sw	$7, 0($sp)
	addui	$13, $sp, 10
	sw	$13, 1($sp)
	jal	winix_send
	j	L.27
L.33:
	la	$13, L.34
	sw	$13, 0($sp)
	addui	$13, $6, 59
	sw	$13, 1($sp)
	lw	$13, 81($6)
	sw	$13, 2($sp)
	lw	$13, 12($sp)
	sw	$13, 3($sp)
	jal	printf
	sw	$6, 0($sp)
	jal	end_process
	j	L.27
L.26:
	la	$13, L.36
	sw	$13, 0($sp)
	addui	$13, $6, 59
	sw	$13, 1($sp)
	lw	$13, 81($6)
	sw	$13, 2($sp)
	lw	$13, 11($sp)
	sw	$13, 3($sp)
	jal	printf
	sw	$6, 0($sp)
	jal	end_process
L.27:
L.24:
	j	L.23
L.16:
	lw	$6, 4($sp)
	lw	$7, 5($sp)
	lw	$12, 6($sp)
	lw	$13, 7($sp)
	lw	$ra, 8($sp)
	addui	$sp, $sp, 18
	jr	$ra
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
L.36:
	.asciiz	"\r\n[SYSTEM] Process \"%s (%d)\" performed unknown system call %d\r\n"
L.34:
	.asciiz	"\r\n[SYSTEM] Process \"%s (%d)\" exited with code %d\r\n"
L.30:
	.asciiz	"\r\n[SYSTEM] Got syscall 2!\r\n"
L.22:
	.asciiz	"Unallocated:  0x%x - 0x%x\r\n"
L.21:
	.asciiz	"BSS Segment:  0x%x - 0x%x\r\n"
L.20:
	.asciiz	"Data Segment: 0x%x - 0x%x\r\n"
L.19:
	.asciiz	"Text Segment: 0x%x - 0x%x\r\n"
L.18:
	.asciiz	" %d kWords Free\r\n"
L.17:
	.asciiz	"Scanning Memory"
