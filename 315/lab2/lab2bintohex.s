#Anthony Dinh
#CPE 315-03 / 315-04
#4/8/2016

.data	      # this starts the data area

   storeSpace:  .word 0, 0, 0

.text       # this starts the code area

main:
   la $a1, storeSpace   #result table address loaded
   move $t5, $a1        #save the address of the result table
   jal bintohex         #jump to the function
   sb $zero, 0($a1)     #the terminating 0 ('\0') for string purposes
   move $a0, $t5        #load the starting address of result table to a0
   li $v0, 4            #printing string syscall
   syscall
   li	$v0, 10		      # TRAP HALT
   syscall			      # enditol (end it all)


bintohex:
   li $t2, 28           #the shifting amount
   li $t6, -4           #keep shifting until -4 (break loop condition)
   li $a0, 2147483647   #this number is the one you want to convert
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
   jr $ra               #jump back to return address in main

sum_less_9:
  addi $t1, $t1, 0x30   #add value by 0x30 to get ASCII value if value <=9
  j end_conditional     #return back
