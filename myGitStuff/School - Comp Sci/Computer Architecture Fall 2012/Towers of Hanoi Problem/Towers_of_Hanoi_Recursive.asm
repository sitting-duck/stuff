# CS 3340.501 - 2012
#Towers of Hanoi
#
#
# Ashley Tharp
#


.data 

#########################################################################
#atoi data
#########################################################################
enter_num_rings_prompt:		 .asciiz 	"Please enter number of rings (max = 100). \n"
note_prompt: 			 .asciiz 	"Note: 10 rings entails (2^10)-1 = 1023 moves:  "
non_int_found_prompt: 		 .asciiz 	"Invalid Input: non-integer found. Please try again.\n"
invalid_num_ring_prompt: 	 .asciiz 	"Invalid Input: You cannot have more than 100 rings.\n"
integer_output: 		 .asciiz 	"Result (reg $a0) = "
num: 				 .word 		0
buffer: 			 .space 	8


#########################################################################
#hanoi data
#########################################################################
numRings: 			 .word 		0
numMoves: 			 .word 		0
tower1: 			 .space 	400
tower2: 			 .space 	400
tower3: 			 .space 	400
platforms: 			 .asciiz 	"    #    #    #"
num_moves_prompt: 		 .ascii 	"Number of moves taken to solve: "

#########################################################################

.text

main:

jal 	getInput 		#puts the user inputted number into numRings in memory

li 	$a0, 0    		#we're going to call pad_integer array and fill the towers with zeros
li 	$a1, 100  		#I've got an array of 100 words I want to fill with zeros
la 	$a2, tower1 		#first we'll fill tower 1
jal 	pad_integer_array
la 	$a2, tower2 		#now we fill tower 2 with zeros
jal 	pad_integer_array 	#we fill the towers with zeros to indicate a space where there is no ring
la 	$a2, tower3		#now we fill tower 3 with zeros
jal 	pad_integer_array	#there cannot be a ring of size zero so this is convenient

#so now all our towers have been initialized to zeros in memory, now we're going to
#initialize the rings onto tower 1. This program will start with all the rings on 
#tower 1, and the destination tower is always tower 2.

lw 	$a0, numRings
jal 	initialize_rings

jal 	print_towers 		#note: print_towers does not take any args, it accesses what it needs from memory

#if numRings == even, then dest tower is tower 2 for the first move
#if numRings == odd, then dest tower is tower 3 for the first move
#jal determine_first_move #returns the mem addr of the proper dest tower based on num rings

#lw $a0, numRings #just settin up some args here...
#la $a1, tower1 # source tower == tower 1
#la $a2, ($v0) # dest tower == tower 2 or 3 (depending on num rings)
#la $a3, ($v1) # spare tower == tower 2 or 3 (depending on num rings)
#jal solve

lw 	$a0, numRings 		#just settin up some args here...
la 	$a1, tower1 		# source tower == tower 1
la 	$a2, tower2 		# dest tower == tower 2 
la 	$a3, tower3 		# spare tower == tower 3
jal 	solve

#calculate num moves
li 	$t3, 1			#start with one, by sll(n) we are going to get 2^n			
sllv 	$t3, $t3, $a0		# $t3 gets 2^n where n == numRings
addi 	$t3, $t3, -1		#to get (2^n) -1
sw 	$t3, numMoves		#store num moves 

li 	$v0, 4			#print out number of moves prompt
la 	$a0, num_moves_prompt
syscall

li 	$v0, 1			#print out number of moves
lw 	$a0, numMoves
syscall

#Exit Program:

li 	$v0, 10			#system code call 10 loaded for program exit
syscall

#End of exit


#########################################################################
#Solve Towers of Hanoi Function
#########################################################################
#args:  $a0 = num rings
#	$a1 = memory address of tower 1
#	$a2 = memory address of tower 2
#	$a3 = memory address of tower 3
#saved regs:   	$s0 = current num rings
#		$s1 = current start tower
#		$s2 = current finish tower
#		$s3 = current spare tower		
#returns: none
#this function will recursively solve the towers of hanoi problem
#we are going to do a countdown from numrings to the last ring
#when numRings == 1, it means that we have a history on the stack
#of which towers are start, finish, and spare towers, 
#move_ring is going to pop off the stack what it needs to make the next
#move each time. 
#
#this function should follow the logic of the below pseudo code:
# N == numRings, Src == source tower, Tmp == spare tower, and
# Dst == destination tower
#
#Solve(N, Src, Dst, Tmp) 
#    if N is 0 
#      exit
#    else
#      Solve(N - 1, Src, Tmp, Dst)      
#      Move from Src to Dst
#      Solve(N - 1, Tmp, Dst, Src)      
#
#
#Basically, what's going on is, let's say we want to solve for n == numRings
# and numRings is 3 in this case. So, to solve for n = 3, we have to solve for n = 2,
# which means putting the two smaller rings on the spare tower, so now we have the one 
#big disk, disk size 3, sitting on the source tower, so we're going to call move_disk,
#and move that to the finish tower.  Now that that we have the biggst ring on bottom on
#the dest tower, we can solve for n = 2 again, but this time, the destination tower
#is the final destination tower, and not the spare tower like before.  You will see some
#swapping of src, dest, and tmp tower going on here, and that is why.  
#
#So to recap, solve for n = 2 with spare tower as dest tower, move the biggest ring 
#to dest tower, and then solve for n = 2 again with dest tower as dest tower, if you want to
#solve for n = 3.  
#
#In the spirit of recursion, the solve function solves for n = 5, by solving n = 4, moving the
#big ring, and solving for n = 4. Well, in solving for n = 4, we are going to have to solve 
#n = 3, move the big ring (the big ring for this particular recursion is ring size == 3, not 4)
#and then solve for n = 3 again. Well, in solving for n = 3, we are going to have to solve 
#n = 2, move the big ring (the big ring for this particular recursion is ring size == 2, not 3)
#and then solve for n = 2 again. And finally, to solve for n = 1, we just move the ring of size 1.
#This is why after we are down to n = 1, we just call move_ring one more time, and then leave the
# function.
#
#for an informative video on how to think of towers of hanoi recursive solution conceptually, 
#you can visit: http://www.youtube.com/watch?v=WftWSVhJ0zc
#########################################################################

solve: addi $sp, $sp -32
sw 	$a0, 0($sp)
sw 	$a1, 4($sp)
sw 	$a2, 8($sp)
sw 	$a3, 12($sp)
sw 	$s1, 16($sp)
sw 	$s2, 20($sp)
sw 	$s3, 24($sp)
sw 	$ra, 28($sp)

beq 	$a0, 1, done_stacking_for_this_solve_call 	#if numRings == 1, we are done making our memory stack

#Initializations
#Move $s0, $a0	#take a picture of current state of towers

move 	$s1, $a1	#by putting all the args into saved registers
move 	$s2, $a2	#
move 	$s3, $a3	#

#Set up args to call Solve(N - 1, Src, Tmp, Dst)

addi 	$a0, $a0 -1 	# the next call to solve will save this into $s0
move 	$a1,$s1 	# source tower = source tower
move 	$a2,$s3 	# finish tower now = spare tower
move 	$a3,$s2 	#spare tower now = finish tower

jal 	solve 		#this is the first solve for n - 1


move 	$a1, $s1	 # source tower = source tower
move 	$a2, $s2	 # destination tower = destination tower
jal 	move_ring 	 #note: this funct takes args: $a1 == src, $a2 == dest

#move ring will also take care of printing every time it makes a move
#note: if we're at this jal move_ring, we're not moving the biggest ring
#for this recursion.

#set up args to call Solve(N - 1, Tmp, Dst, Src)
#NOTE: not the same as last call above, note the order of args

move 	$a1,$s3			# start tower = temp tower
move 	$a2,$s2			# finish tower = finish tower
move 	$a3,$s1			# temp tower = source tower

jal 	solve 			#this is the second solve for n - 1.  Note: each time we call solve, it takes
				#Jumps to start of the function.


j 	now_get_me_some_stack 	#we're done with this recursion, now

#we're going to pop the next frame off the stack to go onto the next recursion.
#so, by the tine we get to this jump, we've solved for the current n, moved the
#big ring for this recursion (which should be of size n) and solved for n again.
#the only point of this jump is that we we skip the move_ring bc we're at n ==1.

done_stacking_for_this_solve_call: jal move_ring 


#now we have moved everything but the big ring, so this
#move_ring call is going to move the biggest ring from the 
#source tower to the destination tower. (We have to do this every time,
#once for n = 3, n = 2, and so on down the line.
#well now we've made our big ol memory stack, for this
#recursion.  We're going to do this for each recursion.  If you look at the printed
#results yo can see this happening.  So let's say we start with n = 5.  We're going to 
#get in a loop where we keep calling the first "solve" over and over until n == 1. 
#We're going to move the current smallest ring on the src tower (which mind you, keeps
#swapping around)and then we go to done to done_stacking_for_this_solve_call and pull 
#the frame for n = 2
# off the stack. The 'jr $ra' at the end of get_me_some_stack is going to take us right back
#to the line right after the solve call last used. (if it's the first solve, we haven't
#moved the big ring yet, if it's the second solve, we have moved the big ring)
#(Note:jal move_ring does it's thing without screwing with the return address) 

#So we keep calling the first solve, and building a memory stack,
#once we get to n = 1, we can say the first part has 'unwinded', 
#So basically, we're going to move one ring, and then we're going 
#to start calling the seond solve over an over. This time, we
#pull a frame off the stack, and now n is 2 for example, move one ring, pull a frame off the
#stack, and now n is 3, move one ring, pull a frame off the stack, and now n is 4, and so
#on. The num rings keeps going back up.
  
#Once we get back to our original numRings this is going to pop off an old return address
#and we're going to the line after the other solve.  We're going to do this until we've completely
#unwinded and then we pop off the very first return address, and pretty go back to the main function, 
#
#
#now_get_me_some_stack pulls the next frame off the stack

now_get_me_some_stack: lw $a0, 0($sp)
lw 	$a1, 4($sp) 
lw 	$a2, 8($sp)
lw 	$a3, 12($sp)
lw 	$s1, 16($sp)
lw 	$s2, 20($sp)
lw 	$s3, 24($sp)
lw 	$ra, 28($sp)
addi 	$sp, $sp 32
jr 	$ra 		#this will take us to the line after the solve that was called last

#either that or we are completely done and the jr $ra will take us back to the
#main functoin

that_was_some_good_stack:	 #I say, that stack was stackin.

#########################################################################
#Determine First Move Function
#########################################################################
#args: none
#returns: the memory address of the destination tower in $v0
#	  the memory address of the spare tower in $v1
#this function will determine which tower to move to on the first move. 
#if the number of rings is even, then move to 2nd tower.
#if the number of rings is odd, then move to 3rd tower.
#########################################################################
determine_first_move: addi $sp, $sp, -4
sw 	$ra, 0($sp)

#initilizations
lw 	$t0, numRings
li 	$t1, 2			 #basically we're going to divide by 2 and then check the remainder
div 	$t0, $t1 		 #quotient goes into lo and remainder goes into hi
mfhi 	$t2			 #grab the remainder
bnez 	$t2, odd_num_rings

even_num_rings: la $v0, tower2
la 	$v1, tower3
j 	ive_decided_the_first_move_captain
odd_num_rings: la $v0, tower3
la 	$v1, tower2

ive_decided_the_first_move_captain:lw $ra, 0($sp)
addi 	$sp, $sp, 4
jr 	$ra

#########################################################################
#Move Ring Function
#########################################################################
#args:  $a1 = source tower
#	$a2 = destination tower
#temps: $t1 - used for checking rings and holding top ring from src tower
#	$t2 - used for checking rings on dest tower
#returns: none	
#this function will move the top ring from the source tower to the 
#destination tower. It's going to scan the source tower for the top ring
#by looping until it finds a zero, then it's going to grab the top ring
#(remember, the top ring is always going to be the littlest ring on that
#tower) and then put it on the destination tower. It is going to do a 
#similiar looping process to find the top ring on the destination tower.
#########################################################################
move_ring: addi $sp, $sp, -24
sw 	$a1, 0($sp)
sw 	$a2, 4($sp)
sw 	$s1, 8($sp)
sw 	$s2, 12($sp)
sw 	$s3, 16($sp)
sw 	$ra, 20($sp)

find_top_of_source_tower: lw $t1, ($a1)		#grab the current level on src tower
beqz 	$t1, found_top_of_source_tower 		#if we got a zero, then we found the top
addi 	$a1, $a1, 4 				#if we didn't find a zero increment to next level on tower
j   	find_top_of_source_tower

found_top_of_source_tower: addi $a1, $a1, -4 	#scoot back one spot to get on the top ring
lw 	$t1, ($a1)				#grab the ring
sw 	$zero, ($a1) 				#put a zero where the rings was

find_top_of_destination_tower: lw $t2, ($a2)
beqz 	$t2, found_top_of_destination_tower
addi 	$a2, $a2, 4 				#if we didn't get a zero, then scoot to the next level
j 	find_top_of_destination_tower

found_top_of_destination_tower:	sw $t1, ($a2) #put the ring we're holding onto dest tower

jal 	print_towers
#annnnnnnnnd we're done.


lw 	$a1, 0($sp)
lw	$a2, 4($sp)
lw 	$s1, 8($sp)
lw 	$s2, 12($sp)
lw 	$s3, 16($sp)
lw 	$ra, 20($sp)
addi 	$sp, $sp, 24
jr 	$ra

#########################################################################
#Print Towers Function
#########################################################################
#args: none
#
#saved regs:    $s0 = num rings
#		$s1 = memory address of tower1
#		$s2 = memory address of tower2		
#		$s3 = memory address of tower3
#	 	$s4 = num levels printed
#		$s5 = holds the value -1 for multiplying
#
#temps:		$t1 = used for converting ring numbers into negative numbers.
#		$a0 is used to pass ints to print_integer
#returns: none
#
#this function will print out the current state of the towers		
#########################################################################
print_towers: addi $sp, $sp, -44
sw 	$s0, 0($sp)
sw 	$s1, 4($sp)
sw 	$s2, 8($sp)
sw 	$s3, 12($sp)
sw 	$s4, 16($sp)
sw 	$s5, 20($sp)
sw	$a0, 24($sp)
sw	$a1, 28($sp)
sw 	$a2, 32($sp)
sw	$a3, 36($sp)
sw 	$ra, 40($sp)

#initializations
lw 	$s0, numRings	#load num rings (num rings == num levels to be printed)
la 	$s1, tower1	#load memory address of tower 1
la 	$s2, tower2	#load memory address of tower 2
la	$s3, tower3	#load memory address of tower 3
li 	$s4, 0		#initialize num levels printed to zero
li 	$s5, -1		#for multipling for our little branching hack

#some setup: since we need to start at top level and print down to the bottom level, I am going to
#put all the tower addresses at the 'top' level of the highest possible tower using the value numrings.
#if we have 5 == numrings, then we have to print 5 levels, even if there are no rings on the fifth level.
#note: the tower1 label indicates the 'bottom' of tower1 in memory, so the largest ring will be there.

move 	$t0, $s0	#let's move num rings to $t0 so we can make a new number
sll 	$t0, $t0, 2 	#multiply by 4 to make a word aligned offset
addi 	$t0, $t0, -4 	#we subtract 1 so that the offset points to the BEGINNING of the last level in memory.(avoid oboe)
add 	$s1, $s1, $t0 	#put tower 1 at offset to be at highest possible level. 
add 	$s2, $s2, $t0 	#put tower 2 at offset to be at highest possible level.
add 	$s3, $s3, $t0 	#put tower 3 at offset to be at highest possible level.

jal	 print_newline

#we start at the top level and print down to the bottom level
#in order to take advantage of bgezal (branch greater than zero and link) I am going to turn all the ring
#size values into negative numbers first, that way, we print_space for a zero, and print_integer for a num
#this might seem like extra unecessary steps, but there is no beqzal pseudo instruction, so this little hack
#will have to do.

print_loop: jal print_space #we print a big space in between each tower
jal 	print_space
jal 	print_space
jal 	print_space

#print one spot for tower 1
lw 	$t1, ($s1)					#get first thing in tower 1
move 	$a0, $t1					#put it in  $a0 to pass to print integer (note: this num is still positive, we want to print the positive num)
mult 	$t1, $s5					#multiply it by -1
mflo 	$t1						#$t1 now holds the negative version (for the branch and link, neg num is not for printing)
bgezal  $t1, print_space				#if zero, then branch  and link and print a space
bltzal  $t1, print_integer 				#if a negative number, then branch and link and print the (positive) number
jal 	check_num_digits_and_print_space_between_towers

#print one spot for tower 2
lw 	$t1, ($s2)					#get first thing in tower 2
move 	$a0, $t1					#put it in  $a0 to pass to print integer (note: this num is still positive, we want to print the positive num)
mult 	$t1, $s5					#multiply it by -1
mflo 	$t1						#$t1 now holds the negative version (for the branch and link, neg num is not for printing)
bgezal 	$t1, print_space				#if zero, then branch  and link and print a space
bltzal 	$t1, print_integer 				#if a negative number, then branch and link and print the (positive) number

jal check_num_digits_and_print_space_between_towers

#print one spot for tower 3
lw 	$t1, ($s3)					#get first thing in tower 3
move 	$a0, $t1					#put it in  $a0 to pass to print integer (note: this num is still positive, we want to print the positive num)
mult 	$t1, $s5					#multiply it by -1
mflo 	$t1						#$t1 now holds the negative version (for the branch and link, neg num is not for printing)
bgezal	$t1, print_space				#if zero, then branch  and link and print a space
bltzal 	$t1, print_integer 				#if a negative number, then branch and link and print the (positive) number

#looping stuff
addi 	$s4, $s4, 1 					#we have printed one level :)

#remember we are starting at top level going down to print from top to bottom.

addi 	$s1, $s1, -4 					#increment to previous (word aligned) spot in tower 1 for when we come to print the next level
addi 	$s2, $s2, -4 					#increment to previous (word aligned) spot in tower 2 for when we come to print the next level
addi 	$s3, $s3, -4 					#increment to previous (word aligned) spot in tower 3 for when we come to print the next level
jal 	print_newline 					#add a newline between each level
beq 	$s4, $s0, done_printing_towers 			#when num levels printed == numRings, we are done and we exit loop

j 	print_loop

done_printing_towers:
jal 	print_platforms

jal 	print_newline

lw 	$s0, 0($sp)
lw 	$s1, 4($sp)
lw 	$s2, 8($sp)
lw 	$s3, 12($sp)
lw 	$s4, 16($sp)
lw 	$s5, 20($sp)
lw 	$a0, 24($sp)
lw 	$a1, 28($sp)
lw 	$a2, 32($sp)
lw 	$a3, 36($sp)
lw 	$ra, 40($sp)
addi	$sp, $sp, 44
jr 	$ra

#########################################################################
#Check Number of Digits and Print Space Between Towers Function 
#########################################################################
#this is basically for making sure everything is pretty, if we try to print
#a two digit number on tower, it offsets the other towers with an ugly
#mismatch and we can't have that, so, if we have a 10 for example, instead 
#of printing 4 spaces in between each tower, we're just to print 3.
#########################################################################
check_num_digits_and_print_space_between_towers: addi $sp, $sp, -52
sw 	$s0, 0($sp)
sw 	$s1, 4($sp)
sw 	$s2, 8($sp)
sw 	$s3, 12($sp)
sw 	$s4, 16($sp)
sw 	$s5, 20($sp)
sw 	$s6, 24($sp)
sw 	$s7, 28($sp)
sw 	$a0, 32($sp)
sw 	$a1, 36($sp)
sw 	$a2, 40($sp)
sw 	$a3, 44($sp)
sw 	$ra, 48($sp)

blt 	$a0, 10, one_digit
bgt 	$a0, 99, three_digits

two_digits:
li 	$v0, 2
jal	print_three_spaces
j 	done_checking_digits_and_watnat

one_digit: 
li 	$v0, 1
jal 	print_four_spaces
j 	done_checking_digits_and_watnat

three_digits:
li 	$v0, 3
jal 	print_two_spaces
j 	done_checking_digits_and_watnat

done_checking_digits_and_watnat:
lw 	$s0, 0($sp)
lw 	$s1, 4($sp)
lw 	$s2, 8($sp)
lw 	$s3, 12($sp)
lw 	$s4, 16($sp)
lw 	$s5, 20($sp)
lw 	$s6, 24($sp)
lw 	$s7, 28($sp)
lw	$a0, 32($sp)
lw 	$a1, 36($sp)
lw 	$a2, 40($sp)
lw	$a3, 44($sp)
lw 	$ra, 48($sp)
addi 	$sp, $sp, 52
jr 	$ra
#########################################################################
#Print Platforms Function
#########################################################################
#prints some pretty little platforms to go under the towers
#########################################################################
print_platforms: addi $sp, $sp, -36 
sw 	$a0, 0($sp)
sw 	$v0, 4($sp)
sw 	$s0, 8($sp)
sw 	$s1, 12($sp)
sw 	$s2, 16($sp)
sw 	$s3, 20($sp)
sw 	$s4, 24($sp)
sw 	$s5, 28($sp)
sw 	$ra, 32($sp)

li 	$v0, 4 		# 4 == syscall code for print string
la 	$a0, platforms 	# platforms looks like " # # #\n"
syscall

 
lw 	$a0, 0($sp)
lw 	$v0, 4($sp)
lw 	$s0, 8($sp)
lw 	$s1, 12($sp)
lw 	$s2, 16($sp)
lw 	$s3, 20($sp)
lw 	$s4, 24($sp)
lw 	$s5, 28($sp)
lw 	$ra, 32($sp)
addi 	$sp, $sp, 36

jr 	$ra

#########################################################################
#Print Integer Function
#########################################################################
#args:  $a0 = integer to print.
#temps: $t0 = -1, for converting to positive int
#this function will first convert the int to positive int, and then print it
#########################################################################
print_integer: addi $sp, $sp, -8 
sw 	$a0, 0($sp)
sw 	$v0, 4($sp)

li	 $v0, 1		# 1 == syscall for print integer
syscall

lw 	$a0, 0($sp)
lw 	$v0, 4($sp)
addi 	$sp, $sp, 8 

jr $ra
#########################################################################
#Print Space Function
#########################################################################
print_space: addi $sp, $sp, -8 
sw 	$a0, 0($sp)
sw 	$v0, 4($sp)

li 	$v0, 11		# 11 == syscall for print character
li 	$a0, 32		#32 == space ascii code
syscall

lw 	$a0, 0($sp)
lw 	$v0, 4($sp)
addi 	$sp, $sp, 8 

jr 	$ra
#########################################################################
#Print Two Spaces Function
#########################################################################
print_two_spaces: addi $sp, $sp, -8 
sw 	$a0, 0($sp)
sw 	$v0, 4($sp)

li 	$v0, 11		# 11 == syscall for print character
li 	$a0, 32		#32 == space ascii code
syscall

li 	$v0, 11		# 11 == syscall for print character
li 	$a0, 32		#32 == space ascii code
syscall

lw 	$a0, 0($sp)
lw 	$v0, 4($sp)
addi 	$sp, $sp, 8 

jr 	$ra

#########################################################################
#Print Three Spaces Function
#########################################################################
print_three_spaces: addi $sp, $sp, -8 
sw 	$a0, 0($sp)
sw 	$v0, 4($sp)

li 	$v0, 11		# 11 == syscall for print character
li 	$a0, 32		#32 == space ascii code
syscall

li 	$v0, 11		# 11 == syscall for print character
li 	$a0, 32		#32 == space ascii code
syscall

li 	$v0, 11		# 11 == syscall for print character
li 	$a0, 32		#32 == space ascii code
syscall

lw 	$a0, 0($sp)
lw 	$v0, 4($sp)
addi 	$sp, $sp, 8 

jr 	$ra

#########################################################################
#Print Four Spaces Function
#########################################################################
print_four_spaces: addi $sp, $sp, -8 
sw 	$a0, 0($sp)
sw 	$v0, 4($sp)

li 	$v0, 11		# 11 == syscall for print character
li 	$a0, 32		#32 == space ascii code
syscall

li 	$v0, 11		# 11 == syscall for print character
li 	$a0, 32		#32 == space ascii code
syscall

li 	$v0, 11		# 11 == syscall for print character
li	 $a0, 32	#32 == space ascii code
syscall

li 	$v0, 11		# 11 == syscall for print character
li 	$a0, 32		#32 == space ascii code
syscall

lw 	$a0, 0($sp)
lw 	$v0, 4($sp)
addi 	$sp, $sp, 8 

jr 	$ra

#########################################################################
#Print Newline Function
#########################################################################
print_newline: addi $sp, $sp, -8 
sw 	$a0, 0($sp)
sw 	$v0, 4($sp)

li	$v0, 11		# 11 == syscall for print character
li 	$a0, 10		#10 == newline asci code
syscall

lw 	$a0, 0($sp)
lw 	$v0, 4($sp)
addi 	$sp, $sp, 8 

jr 	$ra
#########################################################################
#Initialize Rings Function
#########################################################################
#args:  $a0 = num rings
#temps: $t0 = num rings currently initialized
#	$t1 = current address in tower1 in memory
#	$t2 = current ring size
#returns: nothing
#this function will put the number of rings entered by the user onto
#tower 1. So, if the user entered 3 for 3 rings, the tower will look like
# 3, 2, 1, 0, 0, 0 in memory, where 0 indicates an empty space. 
#note: the largest ring always starts on bottom, and the rings decrease in
#size going up the tower.
#########################################################################
initialize_rings: addi $sp, $sp, -8
sw 	$a0, 0($sp)
sw 	$ra, 4($sp)

#initializations
la 	$t1, tower1						#we only initialize onto tower 1, bc that is the start tower
li 	$t0, 0							#$t0 = num rings initialized. We start with zero.
move 	$t2, $a0						#$t2 is current ring size, we start with numrings and go down

#when ring size == 0, we have initialized all the rings, so we exit loop.
initialize_rings_loop: beqz $t2, done_initializing_rings 
sw 	$t2, ($t1)						#put the current size ring on the tower in memory
addi 	$t1, $t1, 4						#go to the next spot on the tower (1 word == 1 int)
addi 	$t2, $t2, -1						#the next ring initialized will be size - 1.
j 	initialize_rings_loop

done_initializing_rings: lw $a0, 0($sp)
lw 	$ra, 4($sp)
addi 	$sp, $sp, 8

jr 	$ra
#########################################################################
#Pad Integer Array Function
#########################################################################
#args:  $a0 = num to fill array with (turn array into 000000 for example)
#	$a1 = size of array (in words)
#	$a2 = memory address of array
#temps: $t1 = num words currently padded.
#returns: nothing
#it can be convienient to fill an array with zeros for example when 
#dealing with strings.
#########################################################################
pad_integer_array: addi $sp, $sp, -16
sw 	$a0, 0($sp)
sw 	$a1, 4($sp) 		 #store everything that will be used during the function on 
sw 	$a2, 8($sp) 		 #the stack
sw 	$ra, 12($sp) 

#initializations
li 	$t1, 0			#$t1 is num words padded, we start with zero
addi 	$a1, $a1, -1 		#in order to avoid off by one error, we fill up to numwords -1

padding_loop: beq $t1, $a1, done_padding_array #when words padded == num words, we're done
sw 	$a0, ($a2)		#we put the number into the current memory address
addi 	$a2, $a2, 4		#we increment by 1 word
addi 	$t1, $t1, 1		#we have padded one word
j	padding_loop

done_padding_array: lw $a0, 0($sp)
lw 	$a1, 4($sp) 		 #put all the args and watnat back so the calling function
lw 	$a2, 8($sp) 		 #gets everything back like before it called this function
lw 	$ra, 12($sp)
addi 	$sp, $sp, 16

jr 	$ra
#########################################################################
#atoi stuff
#prompt user to enter number string
#########################################################################
#Get Input Function
#args: none
#this function will get appropriate number input from the user
#and put the desired number of rings into numRings in memory as well as
#return the entered num rings in $v0
#########################################################################
getInput: addi $sp, $sp, -16
sw 	$a0, 0($sp)
sw 	$a1, 4($sp)
sw 	$v0, 8($sp)
sw 	$ra, 12($sp)

li 	$v0, 4
la 	$a0, enter_num_rings_prompt
syscall

li 	$v0, 4
la 	$a0, note_prompt
syscall

#get num rings from user
li 	$v0, 8
la 	$a0, buffer
li 	$a1, 256
syscall

jal 	check_input_for_non_int

la 	$a0, buffer
jal 	convert_string_to_integer 	#returns integer value in $v0

#make sure numRings is not > 100
bgt 	$v0, 100, invalidNumRings
j 	end_get_input

invalidNumRings:
li 	$v0, 4
la 	$a0, invalid_num_ring_prompt
syscall
j 	getInput

end_get_input:
sw 	$v0, numRings			#put stored num from user into numRings

lw 	$a0, 0($sp)
lw 	$a1, 4($sp)
lw 	$v0, 8($sp)
lw 	$ra, 12($sp)
addi 	$sp, $sp, -16

jr 	$ra
#########################################################################
#function definitions for atoi
#########################################################################

check_input_for_non_int:
	la	 $t1, buffer				#load address of the buffer into t1. $t1 = current buffer index
	#loop begins here
check_input_for_non_int_loop:
	lb 	$t0, ($t1)				#load char at current index in buffer into $t0 ($t0 = current char)
	beq	$t0, 10, exit_check_for_non_int_loop	#if newline char found exit loop
	beqz	$t0, exit_check_for_non_int_loop	#if null char found exit loop
	bltu 	$t0, 48, non_int_found			#if ascii val less than 48 = '0', then non-integer found
	bgt 	$t0, 57, non_int_found			#if ascii value greater than 57 = '9' then non-integer found 
	
	addi 	$t1, $t1, 1				#move to the next byte in the buffer (1 byte = 1 char)
	j 	check_input_for_non_int_loop		#go to beginning of the loop
	
exit_check_for_non_int_loop:				#exit loop
	jr 	$ra
		
non_int_found:
	li 	$v0, 4					#system code call 4 for print string
	la 	$a0, non_int_found_prompt		#"Invalid Input: non-integer found..."
	syscall
	
	
	li 	$v0, 4					#system code call 4 for print string
	la 	$a0, enter_num_rings_prompt		#"Please enter string of integers..."
	syscall

	li 	$v0, 8					#system code call 8 for read string
	la 	$a0, buffer				#load buffer addr to put string in
	li 	$a1, 256				#load length of buffer
	syscall						#note null char already included in string	
	

	j 	check_input_for_non_int

#############################################################################################
#args: $a0 = address of character buffer (asciiz)
#returns: $v0 = an integer equivalent of the character string of numbers

convert_string_to_integer:
	xor 	$t1, $t1, $t1				#set $t1 = to zero
	addiu 	$t1,$a0, 0				#put address of buffer in a temp reg to reserve original arg
	xor 	$v0, $v0, $v0				#set $v0 to zero
	li 	$t3, 10					#set t3 to 10 for mult
convert_string_to_integer_begin_loop:
	lb 	$t0, ($t1)				#load current buffer char into $t0	
	beq 	$t0, 10, endstring			#if newline char found stop converting string
	beqz 	$t0, endstring				#if null char found then stop converting string
	mult 	$v0, $t3				#mult last digit by ten before adding next digit
	mflo 	$v0					#moves multiplied value from 64bit LO register
	subiu 	$t0, $t0, 48				#do the ascii conversion from char to integer
	add 	$v0, $t0, $v0				#v0 = t0 + v0											
	addiu 	$t1, $t1, 1				#increment array index for char string
	j 	convert_string_to_integer_begin_loop	#go back to beginning of loop
endstring:
	jr 	$ra
#############################################################################################
#end atoi function definitions
#############################################################################################

