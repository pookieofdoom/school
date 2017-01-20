#Anthony Dinh
#CPE 315-03 / 315-04
#4/8/2016

.data

   storeSpace:  .word 0, 0, 0
 .text

 main:
   li $a0, 0x1C31  	#assigning ahi
   li $a1, 0xBFFCF000   #assigning alo
   li $a2, 0x1C31	#assigning bhi
   li $a3, 0xBFFCF000	#assigning blo
   jal add64
   la $a1, storeSpace
   move $a0, $v0         #this number is the one you want to convert
   jal bintohex
   move $a0, $v1		#this number is the one you want to convert
   jal bintohex
   li	$v0, 10		      # TRAP HALT
   syscall			      # enditol (end it all)



add64:
   addu $v1, $a1, $a3   #adding alo + blo
   sltu $t1, $v1, $a3   #check to see if there is a carry t1 < a3 or t1 <a1 (doesn't matter) than there was a carry
   addu $v0, $a0, $a2   #adding ahi +bhi
   addu $v0, $v0, $t1   #add carry (can be 0 or 1)
   jr $ra



bintohex:
   li $t2, 28           #the shifting amount
   li $t6, -4           #keep shifting until -4 (break loop condition)
   move $t5, $a1        #save the address of the result table

loop:
   srlv $t1, $a0, $t2   #shift right by t2 amount (multiple of 4 starting at 28)
   andi $t1, 0xF        #mask the bits with 0xF to focus on the lower 4 bits
   addi $t2, $t2, -4    #decrement the shift amount by 4 bits
   ble $t1, 9, sum_less_9  #conditional (if t1 <= 9)
   addi $t1, $t1, 0x37  #add value by 0x37 to get ASCII value if value > 9

end_conditional:
   sb $t1, 0($a1)       #store the byte into the result table
   addi $a1, $a1, 1     #shift the result table to the next available byte
   bne $t2, $t6, loop  #repeat function until all bits are checked (-4)
   sb $zero, 0($a1)     #the terminating 0 ('\0') for string purposes
   move $a0, $t5        #load the starting address of result table to a0

print_setup:
   li $v0, 4            #printing string syscall
   syscall
   jr $ra               #jump back to return address in main

sum_less_9:
  addi $t1, $t1, 0x30   #add value by 0x30 to get ASCII value if value <=9
  j end_conditional     #return back
