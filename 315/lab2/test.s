#Anthony Dinh
#CPE 315-03 / 315-04
#4/8/2016

.data	      # this starts the data area


   #shift upper to the very end to look at it
   #add 0x30 (0-9) 0x41 (A-F)
   # or you can have byte table from 0-F

   #push
   #addi $sp, $sp, -4
   #sw $ra, 0($sp)

   #pop
   #lw $ra, 0($sp)
   #addi $sp, $sp, 4
   #jr $ra
   
   #double percision #use v0 and v1
   A  ahi (a0)  alo(a1)
   B  bhi (a2)  blo(a3)
   
   
   1) addu t1, a1, a3
   #now need to find out if there is a carry
   #if t1 < a1 or t1 < a3, then there was a carry
   2) sltu $t2, $t1, $a1
   3) addu t0, a0, a2
   4) addu t0, t0, t2 #add carry

   byteTable:  .byte 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF
   storeSpace:  .word 0, 0, 0

.text       # this starts the code area

main:
   la $t4, #byteTable #load the address of the table
   la $a1, storeSpace #result table
   move $t5, $a1
   move $t7, $t4
   li $t3, 16
   li $t2, 28
   li $t6, -4
   move $a0, $zero
   addi $a0, $a0, 170 #this number is the one you want to convert
   jal bintohex
   sb $zero, 0($a1)
   move $a0, $t5
   li $v0, 4
   syscall
   li	$v0, 10		# TRAP HALT
   syscall			# enditol (end it all)


bintohex:
   lb $t0, 0($t4)
   srlv $t1, $a0, $t2
   andi $t1, 0xF
   addi $t2, $t2, -4
   bne $t1, $t0, table
   sb $t1, 0($a1)
   addi $a1, $a1, 1
   bne $t2, $t6, bintohex
   jr $ra

sum:
  addi $t1, $t1, 0x30
  sb $t1, 0($a1)
  addi $a1, $a1, 1
  bne $t2, $t6, bintohex
  jr $ra

table:
   addi $t4, $t4, 1
