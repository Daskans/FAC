####################################################################
#  HCL Description of control for single-cycle y86 processor "Seq" #
#                                                                  #
#  Original (C) Randal E. BRYANT, David R. O'HALLARON, 2002        #
#  Updates  (C) Alexis BANDET, Valentin GAISSET, Romain GUISSET,   #
#               Florian SIMBA, 2020                                #
#  Updates  (C) El Hadji Pathe FALL, Corentin MERCIER, Benjamin    #
#               MORO, Nicolas MARIN PACHE, Nathan PRECIGOUT, 2021  #
#  Updates  (C) Mohamed Amine BEN AMARA, 2022                      #
#  Updates  (C) Thomas CASTAGNOS, Julien CHAVEROUX, Pierre-Henri   #
#               DUPOUY, Jeremy PAQUIOT, 2023                       #
####################################################################

## Symbolic representation of y86 instruction codes ################

intsig NOP                      'instructionSet.get("nop").icode'
intsig HALT                     'instructionSet.get("halt").icode'
intsig RRMOVL                   'instructionSet.get("rrmovl").icode'
intsig IRMOVL                   'instructionSet.get("irmovl").icode'
intsig RMMOVL                   'instructionSet.get("rmmovl").icode'
intsig MRMOVL                   'instructionSet.get("mrmovl").icode'
intsig OPL                      'instructionSet.get("addl").icode'
intsig IOPL                     'instructionSet.get("iaddl").icode'
intsig JXX                      'instructionSet.get("jmp").icode'
intsig CALL                     'instructionSet.get("call").icode'
intsig PUSHL                    'instructionSet.get("pushl").icode'
intsig PORE                     'instructionSet.get("PORE").icode'
intsig INCL                     'instructionSet.get("incl").icode'

## Symbolic representation of y86 registers referenced explicitly ##

intsig RESP                     'registers.esp'         # Stack Pointer
intsig REBP                     'registers.ebp'         # Frame Pointer
intsig RNONE                    'registers.none'        # Special value indicating "no register"

## ALU functions referenced explicitly #############################

intsig ALUADD                   'alufct.A_ADD'          # ALU should add its arguments

## Signals that can be referenced by control logic #################

## Fetch stage inputs
intsig pc                       'ctx.pc'                # Program counter

## Fetch stage computations
intsig icode                    'ctx.icode'             # Instruction control code
intsig ifun                     'ctx.ifun'              # Instruction function
intsig rA                       'ctx.ra'                # rA field from instruction
intsig rB                       'ctx.rb'                # rB field from instruction
intsig valC                     'ctx.valC'              # Constant from instruction
intsig valP                     'ctx.valP'              # Address of following instruction

## Decode stage computations
intsig valA                     'ctx.valA'              # Value from register A port
intsig valB                     'ctx.valB'              # Value from register B port

## Execute stage computations
intsig valE                     'ctx.valE'              # Value computed by ALU
boolsig Bch                     'ctx.bcond'             # Branch test

## Memory stage computations
intsig valM                     'ctx.valM'              # Value read from memory

####################################################################
#    Control Signal Definitions.                                   #
####################################################################

## Fetch stage #####################################################

## Does fetched instruction require a register numbers byte?
bool need_regids =
    icode in { RRMOVL, OPL, IOPL, PUSHL, PORE, IRMOVL, RMMOVL, MRMOVL };

## Does fetched instruction require a constant word?
bool need_valC =
    icode in { IRMOVL, RMMOVL, MRMOVL, JXX, CALL, IOPL };

## Is instruction valid?
bool instr_valid =
    icode in { NOP, HALT, RRMOVL, IRMOVL, RMMOVL, MRMOVL,
               OPL, IOPL, JXX, CALL, PUSHL, PORE };

## Decode stage ####################################################

## What register should be used as the A source?
int srcA = [
    icode in { RRMOVL, RMMOVL, OPL, PUSHL } : rA;
    icode in { PORE } : RESP;
    1 : RNONE;  # Don't need register for reading
];

## What register should be used as the B source?
int srcB = [
    icode in { OPL, IOPL, RMMOVL, MRMOVL } : rB;
    icode in { PUSHL, PORE, CALL } : RESP;
    1 : RNONE;  # Don't need register for reading
];

## What register should be used as the E destination?
int dstE = [
    icode in { RRMOVL, IRMOVL, OPL, IOPL } : rB;
    icode in { PUSHL, PORE, CALL } : RESP;
    1 : RNONE;  # Don't need register for writing
];

## What register should be used as the M destination?
int dstM = [
    icode in { MRMOVL, PORE } : rA;
    1 : RNONE;  # Don't need register for writing
];

## Execute stage ###################################################

## Select input A to ALU
int aluA = [
    icode in { RRMOVL, OPL } : valA;
    icode in { IRMOVL, RMMOVL, MRMOVL, IOPL } : valC;
    icode in { CALL, PUSHL } : -4;
    icode in { PORE } : 4;
    # Other instructions don't need ALU
];

## Select input B to ALU
int aluB = [
    icode in { RMMOVL, MRMOVL, OPL, IOPL, CALL, PUSHL, PORE } : valB;
    icode in { RRMOVL, IRMOVL } : 0;
    # Other instructions don't need ALU
];

## Set ALU function
int alufun = [
    icode in { OPL, IOPL } : ifun;
    1 : ALUADD;  # Perform additions by default
];

## Should condition codes be updated?
bool set_cc = icode in { OPL, IOPL };

bool is_bch = icode in { JXX };

## Memory stage ####################################################

## Set read control signal
bool mem_read =
    icode in { MRMOVL, PORE };

## Set write control signal
bool mem_write =
    icode in { RMMOVL, PUSHL, CALL };

## Select memory address
int mem_addr = [
    icode in { RMMOVL, PUSHL, CALL, MRMOVL } : valE;
    icode in { PORE } : valA;
    # Other instructions don't need address
];

## Select memory input data
int mem_data = [
    # Value from register
    icode in { RMMOVL, PUSHL } : valA;
    # Return PC address
    icode == CALL : valP;
    # Default: Don't write anything
];

## Program Counter update ##########################################

## Compute address of next instruction to be fetched
int new_pc = [
    # Call: Use immediate value
    icode == CALL : valC;
    # Taken branch:  Use immediate value
    icode == JXX && Bch : valC;
    # Completion of RET instruction: Use value retrieved from stack
    icode == PORE && ifun == 1 : valM;
    # Default: Use incremented PC
    1 : valP;
];
