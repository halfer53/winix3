.global	sys_uptime
.text
sys_uptime:
	subui	$sp, $sp, 13
	sw	$13, 2($sp)
	sw	$ra, 3($sp)
	sw	$0, 4($sp)
	addui	$13, $0, 4
	sw	$13, 6($sp)
	sw	$0, 0($sp)
	addui	$13, $sp, 5
	sw	$13, 1($sp)
	jal	winix_sendrec
	addu	$13, $0, $1
	sw	$13, 4($sp)
	lw	$1, 7($sp)
L.2:
	lw	$13, 2($sp)
	lw	$ra, 3($sp)
	addui	$sp, $sp, 13
	jr	$ra
.global	sys_exit
sys_exit:
	subui	$sp, $sp, 13
	sw	$13, 2($sp)
	sw	$ra, 3($sp)
	sw	$0, 4($sp)
	addui	$13, $0, 5
	sw	$13, 6($sp)
	lw	$13, 13($sp)
	sw	$13, 7($sp)
	sw	$0, 0($sp)
	addui	$13, $sp, 5
	sw	$13, 1($sp)
	jal	winix_sendrec
	addu	$13, $0, $1
	sw	$13, 4($sp)
	lw	$1, 7($sp)
L.5:
	lw	$13, 2($sp)
	lw	$ra, 3($sp)
	addui	$sp, $sp, 13
	jr	$ra
