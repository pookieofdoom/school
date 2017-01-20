.data
exponent:   .asciiz "The Exponent is "
fraction:   .asciiz "\nThe Fraction is "
storeSpace:  .word 0, 0, 0
.text

main:
   li $t1, -3   #exponent
   li $t2, 0xFFC00000 #fraction you want to normalize 
   srl $t3, $t2, 31   #check the highest bit
   andi $t3, $t3, 0x01
   srl $t4, $t2, 30   #check the second highest bit
   andi $t4, $t4, 0x01
   beq $t3, $t4, shift  #go to shift function if they are equal
   
 shift:
   sll $t2, $t2, 1   #shift the fracton left by 1
   addi $t1, $t1, -1 #adjust exponent by subtracting 1
   srl $t3, $t2, 31  #check the highest bit
   andi $t3, $t3, 0x01
   srl $t4, $t2, 30  #check the second highest bit
   andi $t4, $t4, 0x01
   beq $t3, $t4, shift  #repeat shifting until 2 highest bits are not equal
   move $t0, $t2 #store t2 since my bintohex modifies t2
   #this is the printing of the result normalized
   la $a0, exponent  
   li $v0, 4 
   syscall
   move $a0, $t1
   li $v0, 1
   syscall
   li $a0, 32
   li $v0, 11
   syscall
   move $a0, $t1
   jal bintohex
   la $a0, fraction
   li $v0, 4 
   syscall
   move $a0, $t0  #fraction stored in t0 since bintohex modified t2
   li $v0, 1
   syscall
   li $a0, 32
   li $v0, 11
   syscall
   move $a0, $t0
   jal bintohex
   li $v0, 10
   syscall
   
bintohex:
   la $a1, storeSpace
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