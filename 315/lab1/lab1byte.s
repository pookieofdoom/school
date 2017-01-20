#Anthony Dinh
#CPE 315-03 / 315-04
#4/1/2016

.data				# this starts the data area

table2:         .byte   40, 33, -127, 122, 4, 0, 16, 24, 32, -5, 123

.text				# this starts the code area

   #t4 stores the table1
   #t3 is the loop counter
   #t1 is the total number
   #t0 is the current number from table1


main:				# this is a label on a line by itself
   la $t4, table2    #load address
   li $t3, 11         #this is the total number of things in table
   move $t1, $zero   #initialize total amount to 0

loop:
   lb $t0, 0($t4)    #load number from table 1
   add $t1, $t0, $t1 #add the loaded number with the total number
   addi $t4, $t4, 1  #move the pointer at the table by 1 byte
   addi $t3, $t3, -1 #decrement the counter
   bne $t3, $zero, loop #branch to loop if counter is not 0
   move $a0, $t1 #will be printing out a0
   li $v0, 1 #set up system call to print int
   syscall
	li	$v0, 10		# TRAP HALT
	syscall			# enditol (end it all)
