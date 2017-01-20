.data

storeSpace:  .word 0, 0, 0
signed_bit: .asciiz "The Signed bit is "
exponent:   .asciiz "\nThe Exponent is "
fraction:   .asciiz "\nThe Fraction is "
zero:       .asciiz "The value is 0, therefore everything is zero"
.text

main:
   li $a0, 0xC1080000 #-8.5
   beq $a0, $zero, check_zero #if zero, everything is zero
   move $t3, $a0     #save the value since it will be modified
   jal extract_float
   li $v0, 10
   syscall

check_zero:
   li $v0, 4
   la $a0, zero
   syscall
   li $v0, 10
   syscall
   
extract_float:
   addi $sp, $sp, -4    #initializing stack
   sw $ra, 0($sp)       #storing the return address

extract_sign:
   srl $t0, $a0, 31     #extracting the sign bit which is the top bit
   li $v0, 4              #setup to print ascii message
   la $a0, signed_bit
   syscall              #printed out the message
   move $a0, $t0
   li $v0, 1
   syscall              #print out the sign value (0 or 1)

extract_exp:
   move $a0, $t3
   srl $t1, $a0, 23     #extracting the exponent (8 bits)
   andi $t1, 0xFF       #mask to get only the lower 8 bits
   li $v0, 4            #setup to print ascii message
   la $a0, exponent     #print out message for exponent
   syscall
   addi $t1, $t1, -127  #subtract the bias off of exponent
   addi $t1, $t1, 1     #add 1 to exponent to compensate the right shift of fraction
   move $a0, $t1
   jal bintohex         #print out the exponent in hex (2's complement)

extract_fraction:       #needs to be fixed
   li $v0, 4            #set up to print message for fraction
   la $a0, fraction     #print out fraction message
   syscall
   move $a0, $t3        #restore the orignal value
   sll $t2, $a0, 7      #shift the fraction until its starting at the 29th position
   li $t4, 0x3FFFFFFF   #load in the mask to only keep the fraction part
   and $t2, $t2, $t4    #and the mask with the fraction
   lui $t4, 0x4000      #insert the hidden 1 into the 30th position
   or $t2, $t2, $t4     #or the fraction with hidden 1 to insert
   beq $t0, $zero, skip_negate  #if sign bit is 0, then don't negate
   neg $t2, $t2         #negate if sign bit is 1
skip_negate:
   move $a0, $t2        #setup for bintohex
   jal bintohex         #print out hex(2's complement)
   lw $ra, 0($sp)       #extract return address
   jr $ra               #go back to main

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
