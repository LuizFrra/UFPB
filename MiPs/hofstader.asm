# Luiz Alexsandro / Stenio == 2016018565 / 2016068763 == 5*7 + 6*6 + 5*3 == 35 + 36 + 15 == 86
#int hof(int n)
#if(n <=2)
	#return 1;
#return hof(hof(n-1)) + hof(n - hof(n-1);


.data
	welcome: .asciiz "Hofstadter-Conway $10000 sequence\n"

.text  

	main:
		jal welcomenssage
		jal printnumber
		jal getN
		add $a1, $zero, $a0
		continue:
		blt $a1, 30, loop
		jal exit
	loop:
		jal sequence
		li $v0, 1
		syscall
		addi $a1, $a1, 1
		la $a0, ($a1)
		jal continue

	sequence:
		bgt $a0, 2, recursive
		li $a0, 1
		addi $v0, $zero, 1 # return 
		jr $ra
	
	recursive:
		sub $sp, $sp, 16
		sw $ra, 0($sp)
		sw $a0, 4($sp)
		
		addi $a0, $a0, -1 # n  - 1
		jal sequence  # hof ( n - 1 )
		
		sw $v0, 8($sp) # save return hof ( n - 1 )
		add $a0, $zero, $v0
		jal sequence # hof ( hof ( n - 1 ) )
		
		sw $v0, 12($sp) # save return hof ( hof ( n - 1 ) )
		
		#now we need hof( n - hof ( n - 1 ) )
		
		lw $a0, 4($sp) # n
		lw $t1, 8($sp) # hof ( n - 1 )
		
		sub $a0, $a0, $t1 # n = n - hof ( n - 1)
		jal sequence # hof ( n - hof ( n - 1 ) )
		
		#now hof ( hof ( n - 1 ) ) + hof ( n - hof ( n - 1 ) )
		lw $t1, 12($sp) # load hof( hof ( n - 1 ) )
		add $a0, $v0, $t1 # hof ( hof ( n - 1 ) ) + hof ( n - hof ( n - 1 ) )
		add $v0, $zero, $a0
		lw $ra, 0($sp) # load last call 
		add $sp, $sp, 16 # free memory
		jr $ra # return
		
		
	getN:
		li $v0, 5
		syscall
		add $a0, $zero, $v0
		jr $ra
	
	welcomenssage:
		la $a0, welcome
		li $v0, 4
		syscall
		jr $ra
	
	printnumber:
		li $a0,2
		li $v0, 1
		syscall
		jr $ra
	
	exit:
		li $v0, 10
		syscall
