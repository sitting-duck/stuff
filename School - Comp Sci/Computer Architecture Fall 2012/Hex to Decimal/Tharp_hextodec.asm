
#Ashley Tharp

.data 

prompt: .asciiz "Please enter a hexidecimal string no longer than 8 characters: \n"
non_int_found_prompt: .asciiz "Invalid Input: non-hex found. Please try again. \n"
integer_output: .asciiz "Result (reg $a0) = "

buffer: .space 10 # buff size = 8 chars + '\n' + '\0'

.text

main:

#prompt user to enter number string
li $v0, 4
la $a0, prompt
syscall

#get string from user and store into buffer (max of 256 chars)
li $v0, 8
la $a0, buffer
li $a1, 8
syscall

la $a0, buffer
jal htoi
move $s0, $v0		# save the result to keep syscalls from clobbering it

#print the result
li $v0, 4
la $a0, integer_output
syscall

li $v0, 1
move $a0, $s0	#move final int to $a0 to print
syscall

#exit program
li $v0, 10	#system code call 10 loaded for program exit
syscall

###############################################################################
#args: $a0 = address of buffer of hex characters (asciiz)
#return: $v0 = equivalent integer value of given hex string
htoi:
	addiu $t1,$a0, 0			#save address so we don't blow it away
	xor $v0, $v0, $v0			#set $v0 to zero
	li $t3, 16				#set t3 to 16 for mult
	
	htoi_begin_loop:
	lb $t0, ($t1)				#load current buffer char into $t0	
	beq $t0, 10, htoi_end_loop		#if newline char found stop converting string
	beqz $t0, htoi_end_loop			#if null char found then stop converting string
	
	mult $v0, $t3				#mult last digit by ten before adding next digit
	mflo $v0				#moves multiplied value from 64bit LO register
	
	#convert
	sge $t7, $t0, 65			# if ($t1 >= 65 && $t1 <= 70) go to htoi_DoUpperCase
	sle $t6, $t0, 70
	beq $t6, $t7, htoi_DoUpperCase 
		
	sge $t7, $t0, 97			# if ($t1 >= 97 && $t1 <= 102) go to htoi_DoUpperCase
	sle $t6, $t0, 102
	beq $t6, $t7, htoi_DoLowerCase
	
	j htoi_not_alpha			#assume that if it's not upper/lowercase hex that it's a number
	
	htoi_DoUpperCase:
	subi $t0, $t0, 7			# back us up to where '0' -> '9' leave off
	j htoi_not_alpha			# it's not an alphabetical hex char anymore

	htoi_DoLowerCase:
	subi $t0, $t0, 39
			
	htoi_not_alpha:
	subi $t0, $t0, 48			# $t1 = $t1 - '0'
	add $v0, $v0, $t0			# add the converted value
	addiu $t1, $t1, 1			#increment array index for char string
	
	j htoi_begin_loop	#go back to beginning of loop
	htoi_end_loop:
	
	jr $ra
