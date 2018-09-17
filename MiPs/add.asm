.text
.globl main

main:
	jal read
	jal adiciona
	jal read
	jal adiciona
	jal imprime
	jal fim
	
imprime:
	la $a0, 0($t0) # Coloca o Valor em $a0 para ser impresso
	li $v0, 1
	syscall
	jr $ra # retorna para a funcao que chamou ( main )

read:
	li $v0, 5 # Ler Um Valor
	syscall #
	la $a0, ($v0) # Armazeno esse valor em a0
	jr $ra # retorna para a funcao que chamou ( main )

fim:
	li $v0, 10 # Encerro o programa
	syscall

adiciona:
	add $t0, $t0, $a0 # t0 = t0 + a0
	jr $ra #retorna para a funcao que chamou ( main )
	