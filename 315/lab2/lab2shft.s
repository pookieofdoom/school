#Anthony Dinh
#CPE 315-03 / 315-04
#4/8/2016

.data

error: .asciiz "Specified 0 fields are non-zero."
mask: .word 0x19F70FFF
storeSpace:  .word 0, 0, 0

.text

main:
   li $a0, 0xC2008001      #load the parameter you want to shift
   jal  errorCheck         #check if parameter is valid sequence
   bne $v1, $zero, formatError   #if error, print error
   jal store_bytes         #if no error, start the functon
   li $v0, 10              #ending program
   syscall


errorCheck:
	la $v1, mask           #load the mask that will be used to check valid
	lw $v1, 0($v1)
	and $v1, $a0, $v1      #AND the parameter and mask (0 == good)
	jr $ra

formatError:
	li $v0, 4              #setup to print ascii message
	la, $a0, error
	syscall
	li $v0, 10             #end program cause it was an error
	syscall

store_bytes:
   addi $sp, $sp, -4      #initializing stack
   sw $ra, 0($sp)         #storing the return address
   addi $sp, $sp, -4
   sw $fp 0($sp)          #store the frame pointer
   move $fp, $sp          #set frame pointer to stack pointer
   li $t0, 28             #loop counter
   li $t2, -4             #loop ending condition

store_loop:
   srlv $t1, $a0, $t0      #shift the focused byte to the very right
   andi $t1, 0xF           #negating every bit other than the bottom 4
   addi $t0, $t0, -4       #decrement counter
   addi $sp, $sp, -4
   sw $t1, 0($sp)          #storing the byte into the stack
   bne $t0, $t2, store_loop   #keep looping until -4
   jal create_seq          #after storing all the bytes, go make sequence


create_seq:
   lw $a0, -20($fp)     #use the frame pointer to reference all the bytes
   sll $a0, $a0, 12     #shift the focused bytes into their place
   lw $a1, -16($fp)     #getting second byte
   sll $a1, $a1, 5      #shift to its position
   or $a0, $a0, $a1     #combine it to the result register
   lw $a1, -8($fp)      #getting the 3rd byte
   srl $a1, $a1, 1      #shift to its position
   or $a0, $a0, $a1     #combine it to the result register
   lw $a1, -4($fp)      #last byte
   sll $a1, $a1, 3      #shift to its position
   or $a0, $a0, $a1     #combine to get the final result
   jal bintohex         #print result in hex
   lw $ra, 4($fp)       #extract return address
   jr $ra               #go back to main


bintohex:               #this converts a number stored in $a0
   li $t2, 28           #the shifting amount
   li $t6, -4           #keep shifting until -4 (break loop condition)
   la $a1, storeSpace
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
