.global	strcmp
.text
strcmp:
	subui	$sp, $sp, 3
	sw	$12, 0($sp)
	sw	$13, 1($sp)
	j	L.3
L.2:
	lw	$13, 3($sp)
	lw	$13, 0($13)
	lw	$12, 4($sp)
	lw	$12, 0($12)
	seq	$13, $13, $12
	bnez	$13, L.5
	j	L.4
L.5:
	lw	$13, 3($sp)
	addui	$13, $13, 1
	sw	$13, 3($sp)
	lw	$13, 4($sp)
	addui	$13, $13, 1
	sw	$13, 4($sp)
L.3:
	addu	$13, $0, $0
	sw	$13, 2($sp)
	lw	$12, 3($sp)
	lw	$12, 0($12)
	seq	$13, $12, $13
	bnez	$13, L.7
	lw	$13, 4($sp)
	lw	$13, 0($13)
	lw	$12, 2($sp)
	sne	$13, $13, $12
	bnez	$13, L.2
L.7:
L.4:
	lw	$13, 3($sp)
	lw	$13, 0($13)
	lw	$12, 4($sp)
	lw	$12, 0($12)
	sub	$1, $13, $12
L.1:
	lw	$12, 0($sp)
	lw	$13, 1($sp)
	addui	$sp, $sp, 3
	jr	$ra
.global	strlen
strlen:
	subui	$sp, $sp, 3
	sw	$7, 0($sp)
	sw	$12, 1($sp)
	sw	$13, 2($sp)
	addu	$7, $0, $0
	j	L.10
L.9:
	addi	$7, $7, 1
L.10:
	lw	$13, 3($sp)
	addui	$12, $13, 1
	sw	$12, 3($sp)
	lw	$13, 0($13)
	sne	$13, $13, $0
	bnez	$13, L.9
	addu	$1, $0, $7
L.8:
	lw	$7, 0($sp)
	lw	$12, 1($sp)
	lw	$13, 2($sp)
	addui	$sp, $sp, 3
	jr	$ra
