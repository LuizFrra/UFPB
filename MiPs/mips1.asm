.data
	fMessage: .asciiz "Hello World\n"
.text
	li $v0, 4 # Digo ao Sistema que irei imprimir algo
	la $a0, fMessage 
	syscall
