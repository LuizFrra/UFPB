.text
	.globl inicio

	inicio:
		li $v0, 5 # Instrução Para Ler um Numemro
		syscall # Chamo a intruscao que ler o numero
		la $t0 , 0($v0) # Carrego esse numero em um registrador temporario
		la $a0 , ($t0) # Imrpimo o Inteiro	
		li $v0 , 1 # Instrucao para imprimir um inteiro			
		syscall # chamada da instrucao que imprime o inteiro
	
