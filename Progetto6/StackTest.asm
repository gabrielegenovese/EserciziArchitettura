//bootstrap
@256
D=A
@SP
M=D
//push constant 17 
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 17 
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
//eq   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
D=M
@EQ10
D;JEQ
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_EQ10
0;JMP
(EQ10)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_EQ10)
//push constant 17 
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 16 
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
//eq   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
D=M
@EQ13
D;JEQ
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_EQ13
0;JMP
(EQ13)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_EQ13)
//push constant 16 
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 17 
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
//eq   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
D=M
@EQ16
D;JEQ
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_EQ16
0;JMP
(EQ16)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_EQ16)
//push constant 892 
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 891 
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
//lt   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
D=M
@LT19
D;JLT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_LT19
0;JMP
(LT19)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_LT19)
//push constant 891 
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 892 
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
//lt   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
D=M
@LT22
D;JLT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_LT22
0;JMP
(LT22)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_LT22)
//push constant 891 
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 891 
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
//lt   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
D=M
@LT25
D;JLT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_LT25
0;JMP
(LT25)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_LT25)
//push constant 32767 
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 32766 
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
//gt   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
D=M
@GT28
D;JGT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_GT28
0;JMP
(GT28)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_GT28)
//push constant 32766 
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 32767 
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
//gt   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
D=M
@GT31
D;JGT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_GT31
0;JMP
(GT31)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_GT31)
//push constant 32766 
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 32766 
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
//gt   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
D=M
@GT34
D;JGT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_GT34
0;JMP
(GT34)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_GT34)
//push constant 57 
@57
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 31 
@31
D=A
@SP
A=M
M=D
@SP
M=M+1
//push constant 53 
@53
D=A
@SP
A=M
M=D
@SP
M=M+1
//add   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
D=D+M
@SP
A=M
M=D
@SP
M=M+1
//push constant 112 
@112
D=A
@SP
A=M
M=D
@SP
M=M+1
//sub   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
D=M
@SP
A=M
M=D
@SP
M=M+1
//neg   
@SP
M=M-1
@SP
A=M
D=M
D=-D
@SP
A=M
M=D
@SP
M=M+1
//and   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=D&M
D=M
@SP
A=M
M=D
@SP
M=M+1
//push constant 82 
@82
D=A
@SP
A=M
M=D
@SP
M=M+1
//or   
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=D|M
D=M
@SP
A=M
M=D
@SP
M=M+1
//not   
@SP
M=M-1
@SP
A=M
D=M
D=!D
@SP
A=M
M=D
@SP
M=M+1
