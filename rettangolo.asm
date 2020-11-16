// colonna 20 linea di larghezza 1 e altezza 50

@50
D=A //D=50
@END
D;JLE  // if D>0 then
@counter
M=D    //  counter=D
@SCREEN
D=A
D=D+1
@address
M=D    //  address=SCREEN
(LOOP)
@16
D=A
@address
A=M
M=D
@address
D=M    //   D=address
@32
D=D+A  //   D += 32
@address
M=D    //   address=D
@counter
MD=M-1 //   counter--
@LOOP
D;JGT  //  until counter<=0
(END)
@END
0;JMP
