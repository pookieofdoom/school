########################################################
# Derek Nguyen
# CPE 315 - 05
# Lab 2 : Problem 2 Fibonacci Sequence
########################################################
# C Function Representation:
# int fibonacci(int term){
#     if(term < 2)
#        return term;
#     return fibonacci(term - 1) + fibonacci(term - 2);
# }
########################################################

.text

main:
	li $a0, 9	# the nth term th at we want to find
	jal fibonacci

	move $a0, $v1
	li $v0, 1
	syscall
	li $v0, 10
	syscall


fibonacci:
	bgt $a0, 1, fib_recursive	# for case of (n < 2)
	move $v1, $a0				# move the result to return register
	jr $ra						# return n

fib_recursive:
	sub $sp, $sp, 12			# allocate stack
	sw $ra, 0($sp)				# save the return address to stack

	sw $a0, 4($sp)				# save n
	add $a0, $a0, -1				# n - 1 case
	jal fibonacci				# recursive call n - 1

	lw $a0, 4($sp)				# load the previous n value
	sw $v1, 8($sp)				# store result of n - 1 recursive call

	add $a0, $a0, -2			# n - 2 case
	jal fibonacci				# recursive call n - 2

	lw $t0, 8($sp)				# get n - 1 result
	add $v1, $t0, $v1			# fib(n-1) + fib(n-2)

	lw $ra, 0($sp)				# load the original return address
	add $sp, $sp, 12			# free stack
	jr $ra						# return back to main
