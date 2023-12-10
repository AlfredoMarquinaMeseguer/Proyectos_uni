###################
# Seccion de datos
	.data

$str1:
	.asciiz "Primer do while"
$str2:
	.asciiz "\n"
$str3:
	.asciiz "El valor de a es "
$str4:
	.asciiz "\n"
$str5:
	.asciiz "\nSegundo do while\n"
$str6:
	.asciiz "El valor de a es "
$str7:
	.asciiz "\n"
_a:
	.word 0

###################
# Seccion de codigo
	.text
	.globl main
main:
	li $t0, 3
	sw $t0, _a
	li $v0, 4
	la $a0, $str1
	syscall
	lw $t0, _a
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 4
	la $a0, $str2
	syscall
	lw $t0, _a
	$l1:
	li $v0, 4
	la $a0, $str3
	syscall
	lw $t0, _a
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 4
	la $a0, $str4
	syscall
	lw $t0, _a
	li $t1, 1
	sub $t0, $t0, $t1
	sw $t0, _a
	lw $t0, _a
	bnez $t0, $l1
	li $v0, 4
	la $a0, $str5
	syscall
	li $t0, 5
	sw $t0, _a
	$l2:
	lw $t0, _a
	beqz $t0, $l3
	li $v0, 4
	la $a0, $str6
	syscall
	lw $t1, _a
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 4
	la $a0, $str7
	syscall
	lw $t1, _a
	li $t2, 1
	sub $t1, $t1, $t2
	sw $t1, _a
	b $l2
	$l3:

##############
# Fin
	jr $ra

