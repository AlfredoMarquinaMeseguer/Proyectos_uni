###################
# Seccion de datos
	.data

$str1:
	.asciiz "hola \"esto es\" una prueba"
$str2:
	.asciiz "\n"
$str3:
	.asciiz "b es true porque su valor es distinto de 0\n"
$str4:
	.asciiz "El valor de b va disminuyendo en"
$str5:
	.asciiz "cada iteración\n"
$str6:
	.asciiz "hola"
$str7:
	.asciiz "El valor de b es 0\n"
_x:
	.word 0
_y:
	.word 0
_b:
	.word 0
_z:
	.word 0

###################
# Seccion de codigo
	.text
	.globl main
main:
	li $t0, 30
	sw $t0, _x
	li $t0, 10
	neg $t1, $t0
	sw $t0, _y
	li $t0, 3
	sw $t0, _b
	lw $t0, _x
	lw $t2, _y
	add $t0, $t0, $t2
	sw $t0, _z
	li $v0, 4
	la $a0, $str1
	syscall
	li $v0, 4
	la $a0, $str2
	syscall
	lw $t0, _b
	beqz $t0, $l1
	li $v0, 4
	la $a0, $str3
	syscall
	$l1:
	$l2:
	lw $t0, _b
	beqz $t0, $l3
	lw $t2, _b
	li $t3, 1
	sub $t2, $t2, $t3
	sw $t2, _b
	li $v0, 4
	la $a0, $str4
	syscall
	li $v0, 4
	la $a0, $str5
	syscall
	b $l2
	$l3:
	lw $t0, _b
	beqz $t0, $l4
	li $v0, 4
	la $a0, $str6
	syscall
	b $l5
	$l4:
	li $v0, 4
	la $a0, $str7
	syscall
	$l5:

##############
# Fin
	jr $ra

