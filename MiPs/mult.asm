#16 bits unsigned
#max value : 65536
#chamada de procedimentos ok
#passagem por parametros a0 - a3 ok
#validar 16 bits 65536
#negativo ok

.data
	options: .asciiz "Welcome to mult\n"
	multiplicando: .asciiz "Digite o Multiplicando\n"
	multiplicador: .asciiz "Digite o Multiplicador\n"
	printMultiplicando: .asciiz "Multiplicando e : \n"
	printMultiplicador: .asciiz "\nMultiplicador e :  \n"
	result: .asciiz "\n O resultado e : \n"
	over: .asciiz "\nOverflow\n"

.text
	jal welcome # indo para o endereço do label print e salvado pc + 4 em $ra
	addi $sp, $zero, -8 # adjust stack to 2(multiplicando e multiplicador) + 16 item 2.5 pag101
	jal getMultiplicando
	jal getMultiplicador
	jal exibeNumbers
	jal mult16
	jal validacao
	jal resultado
	j exit
	
welcome:
	la $a0, options
	li $v0, 4
	syscall
	jr $ra	
exit:
	li $v0, 10
	syscall

getMultiplicando:
	la $a0, multiplicando
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	sw $v0, 0($sp)
	jr $ra
	
getMultiplicador:
	la $v0, multiplicador
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	#addi $sp, $zero, -4 # adjust stack to more 1 item -> duvida : porque se eu fizer isso aqui e na outra get da erro ?
	sw $v0, 4($sp)
	jr $ra
	
exibeNumbers:
	la $a0, printMultiplicando
	li $v0, 4
	syscall
	lw $a0, 0($sp)
	li $v0, 1
	syscall
	
	la $a0, printMultiplicador
	li $v0, 4
	syscall
	lw $a0, 4($sp)
	li $v0, 1
	syscall
	jr $ra

mult16 :
	lhu $s0, 0($sp) # s0 = multiplicando
	lhu $s1, 4($sp) # s1 = multiplicador
	beq $s0, $zero, exit
	beq $s1, $zero, exit # se um dos dois for igual a zero o resultado sera zero
	
	add $t0, $zero, 0
	addi $t0, $zero, 16 # $t0 = 15 -> quantidade de lopp (16) 0 - 15
	
	loop:
	beq $t0, 0, pulo
	addi $t0,$t0, -1
	#primeiro : verificar se o bit menos significado do meu multiplicador é 1
	sll $t1, $s1, 31 # deslocando 16 bits para esquerda para pegar o menos significado
	
	bne $t1, -2147483648, desloca # Quando eu deslocar 31bits a esquerda terei apenas o mais significado que é 0x80000000
	add $a1, $a1, $s0 # somando
	
	desloca:
		sll $s0, $s0, 1 # multiplicando para esquerda
		srl $s1, $s1, 1 # multiplicador para a direita
		j loop
		
	pulo:
		jr $ra
		
resultado:
	la $a0, result
	li $v0, 4
	syscall
	la $a0,0($a1)
	li $v0, 1
	syscall 
	jr $ra

validacao:
	add $t4, $zero, 65537
	slt $t3, $a1,$t4 
	beq $t3, 0, overflow
	jr $ra		

overflow: 
	la $a0, over
	li $v0, 4
	syscall
	j exit
	
	