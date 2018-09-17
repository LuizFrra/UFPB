.data
	isEqual: .asciiz "The numbers are equals\n"
.text
.globl main

main:
	li $v0, 5
	syscall
	la $s0, 0($v0)
	li $v0, 5
	syscall
	la $s1, 0($v0)
	beq $s0, $s1, printMessage
	beq_1:
	jal fim

printMessage:
	li $v0, 4
	la $a0, isEqual
	syscall
	jal beq_1

fim:
	li $v0, 10
	syscall
