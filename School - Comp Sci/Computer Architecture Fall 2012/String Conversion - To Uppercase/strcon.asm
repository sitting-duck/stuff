#Ashley Tharp
#CS/SE 3340.501
# N. Nguyen

.text

################# main ###########################
main:
	# get some string from the user
	la $a0, input_buff
	lw $a1, input_buff_len
	jal GetInput
	
	# number of characters read will be in $v1
	# input_buff will now contain the entered characters
	
	# convert the input to lowercase in-place
	la $t1, input_buff
	nextCh:
		# get the char
		lb $t2, ($t1)
		
		# check for null terminator or newline
		beqz $t2, strEnd
		beq $t2, 10, L1
		
		# if not an uppercase letter (between 65 and 91) then skip conversion
		slti $t4, $t2, 65
		bne $t4, $zero, L1
		slti $t4, $t2, 91
		beq $t4, $zero, L1
		
		# do the conversion
		add $t2, $t2, 32
		sb $t2, ($t1)
		sll 
		# go to next char
		L1: 
		add $t1, $t1, 1
		j nextCh
	strEnd:
	
	# print out a header before printing the answer
	la $a0, ans
	li $v0, 4
	syscall
	
	# print the converted string
	la $a0, input_buff
	li $v0,4
	syscall
	
	# print a newline for clarity
	la $a0, endl
	li $v0, 4
	syscall
	
	# return control to the OS
	li $v0, 10
	syscall

################# end main ###########################

#Ask the user for input
#args:
#	$a0 = adress of buffer to hold the input
#	$a1 = length of the buffer
#returns:
#	$v1 = length of the string read
GetInput:
	# store the input buff stuff so we don't overwrite it when doing syscalls
	move $t0, $a0
	move $t1, $a1
	# prompt user for input
	la $a0, prompt
	li $v0, 4
	syscall
	
	#call fgets
	move $a0, $t0
	move $a1, $t1
	li $v0, 8
	syscall
	
	# figure out how many characters we just read-- result goes into $v1 which is our return register
	move $a0, $t0
	sw $ra, 4($sp)
	jal strlen
	lw $ra, 4($sp)
	
	jr $ra

# calculate the length of a string
# args:
#	$a0 = address of null terminated string
# returns:
#	$v1 = length of string
strlen:
	move $t1, $a0			#store initial string address
	strlen_loop:
		lb $t0, ($a0)		#get the current letter
		beqz $t0, strlen_end	#if null, then we found the end of the string
		addi $a0, $a0, 1	#go to the next letter
		j strlen_loop
	strlen_end:
	sub $v1, $a0, $t1		#current address minus initial address = string length
	jr $ra

#--------------------End Cut-----------------------
###################################################
# data segment #
###################################################
.data
	ans: .asciiz "lowercase string: "
	prompt: .asciiz "Please enter a string that is less than 127 characters: "
	endl: .asciiz "\n"
	# putting this at the end to avoid stamping over ans, prompt, and endl
	input_buff_len: .word 128
	input_buff: .byte 0