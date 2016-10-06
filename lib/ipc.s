.global	winix_send
.text
winix_send:
	subui	$sp, $sp, 5
	sw	$13, 3($sp)
	sw	$ra, 4($sp)
	lhi	$13, 0x1337
	ori	$13, $13, 0x1
	sw	$13, 0($sp)
	lw	$13, 5($sp)
	sw	$13, 1($sp)
	lw	$13, 6($sp)
	sw	$13, 2($sp)
	jal	wramp_syscall
	addu	$13, $0, $1
	addu	$1, $0, $13
L.2:
	lw	$13, 3($sp)
	lw	$ra, 4($sp)
	addui	$sp, $sp, 5
	jr	$ra
.global	winix_receive
winix_receive:
	subui	$sp, $sp, 5
	sw	$13, 3($sp)
	sw	$ra, 4($sp)
	lhi	$13, 0x1337
	ori	$13, $13, 0x2
	sw	$13, 0($sp)
	sw	$0, 1($sp)
	lw	$13, 5($sp)
	sw	$13, 2($sp)
	jal	wramp_syscall
	addu	$13, $0, $1
	addu	$1, $0, $13
L.3:
	lw	$13, 3($sp)
	lw	$ra, 4($sp)
	addui	$sp, $sp, 5
	jr	$ra
.global	winix_sendrec
winix_sendrec:
	subui	$sp, $sp, 5
	sw	$13, 3($sp)
	sw	$ra, 4($sp)
	lhi	$13, 0x1337
	ori	$13, $13, 0x3
	sw	$13, 0($sp)
	lw	$13, 5($sp)
	sw	$13, 1($sp)
	lw	$13, 6($sp)
	sw	$13, 2($sp)
	jal	wramp_syscall
	addu	$13, $0, $1
	addu	$1, $0, $13
L.4:
	lw	$13, 3($sp)
	lw	$ra, 4($sp)
	addui	$sp, $sp, 5
	jr	$ra
