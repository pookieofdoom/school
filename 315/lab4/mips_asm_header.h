/*----------------------------------------------------------------------*
*	mips_asm Binary header (.mb) file header format.  This header	*
*	provides for future information on mips assembler files.	*
*									*
*	write_header - writes mips_asm header, along with test data	*
*									*
*	This shows how the mips_asm header is written, and provides	*
*	a test case (testcase1.mb) to be used for lab projects.		*
*----------------------------------------------------------------------*/

typedef struct _mb_hdr
{
   char signature[4];		/* Signature = 0x7F, 'M', 'B", 0x00 */
   unsigned int size;		/* Size of assembler program portion, bytes */
   unsigned int entry;		/* Entry point offset of program if not zero */
   unsigned int filler1;		/* Unused ... reserved for future use. */
   unsigned char filler2[64-16];	/* Overall header is 64 bytes */
} MB_HDR, *MB_HDR_PTR;


typedef struct {
   unsigned int opcode;
   unsigned int rs;
   unsigned int rt;
   unsigned int rd;
   unsigned int shamt;
   unsigned int funct;
}R_Instruction;

typedef struct {
   unsigned int opcode;
   unsigned int index;
}Jump_Instruction;

typedef struct {
   unsigned int opcode;
   unsigned int rs;
   unsigned int rt;
   unsigned int immed;
}I_Instruction;

static char* func_lookup[44] =
{
   "Logical Shift Left", "Not Available", "Logical Shift Right", "Shift Right Arithmetic",
   "Shift Left Logical Var.", "Not Available", "Shift Right Logical Var.", "Shift Right Arithmetic Var.",
   "Jump Register", "Jump And Link Register", "Not Available", "Not Available",
   "Syscall", "Not Available", "Not Available", "Not Available",
   "Move From HI", "Not Available", "Move From LO", "Not Available",
   "Not Available", "Not Available", "Not Available", "Not Available",
   "Multiply", "Multiply Unsigned", "Divide", "Divide Unsigned",
   "Not Available", "Not Available", "Not Available", "Not Available",
   "Add", "Add Unsigned", "Subtract", "Subtract Unsigned",
   "And", "Or", "Xor", "Nor",
   "Not Available", "Not Available", "Set Less Than", "Set Less Than Unsigned"      
};


static char *op_lookup[44] = {
   "Register Instruction", "Not Available", "Jump Instruction", "Jump And Link",
   "Branch On Equal", "Branch On Not Equal", "Not Available", "Not Available",
   "Add Immediate", "Add Immediate Unsigned", "Set Less Than Immediate", "Set Less Than Immediate Unsigned",
   "And Immediate", "Or Immediate", "Xor Immediate", "Load Upper Immediate",
   "Not Available", "Not Available", "Not Available", "Not Available",
   "Not Available", "Not Available", "Not Available", "Not Available",
   "Not Available", "Not Available", "Not Available", "Not Available",
   "Not Available", "Not Available", "Not Available", "Not Available",
   "Load Byte", "Load Halfword", "Not Available", "Load Word",
   "Load Byte Unsigned", "Load Halfword Unsigned", "Not Available", "Not Available",
   "Store Byte", "Store Halfword", "Not Available", "Store Word"
};