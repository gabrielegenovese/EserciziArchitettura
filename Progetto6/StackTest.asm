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
@EQ3
D;JEQ
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_EQ3
0;JMP
(EQ3)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_EQ3)
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
@EQ6
D;JEQ
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_EQ6
0;JMP
(EQ6)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_EQ6)
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
@EQ9
D;JEQ
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_EQ9
0;JMP
(EQ9)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_EQ9)
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
@LT12
D;JLT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_LT12
0;JMP
(LT12)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_LT12)
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
@LT15
D;JLT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_LT15
0;JMP
(LT15)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_LT15)
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
@LT18
D;JLT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_LT18
0;JMP
(LT18)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_LT18)
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
@GT21
D;JGT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_GT21
0;JMP
(GT21)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_GT21)
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
@GT24
D;JGT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_GT24
0;JMP
(GT24)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_GT24)
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
@GT27
D;JGT
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@END_GT27
0;JMP
(GT27)
@0
D=A
D=D-1
@SP
A=M
M=D
@SP
M=M+1
(END_GT27)
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
