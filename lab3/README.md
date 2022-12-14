# lab3

[Toc]

## read and understand

翻译后的汇编代码如下

```assembly
.ORIG x3000
ADD R1,R1,#1
ADD R2,R2,#1
ADD R3,R3,#2
LD R5,NUMBER1023
ADD R0,R0,#-2
BRP START
BRN N2
ADD R7,R7,#1
BRNZP  END
N2 ADD R7,R7,#2
BRNZP END
START ADD R7,R1,R1
ADD R7,R7,R3
AND R7,R7,R5
ADD R1,R2,#0
ADD R2,R3,#0
ADD R3,R7,#0
ADD R0,R0,#-1
BRP START
END HALT
NUMBER1023 .FILL #1023
RESA .FILL #930
RESB .FILL #246
RESC .FILL #386
RESD .FILL #70
.END
```

## guess

源代码的最后四行如下

0000001110100010
0000000011110110
0000000110000010
0000000001000110

计算可得，它们分别是数列的第20、11（或95）、16、53项，则源代码主人的学号为20111653或20951653，根据飞书群中表格可知，学号应为20111653

## Optimizeing

源代码中每一步计算出数列的下一项后直接求得模1024的结果，可以优化为在计算到最后一项时再模1024

优化后的汇编代码如下

```assembly
.ORIG x3000
ADD R1,R1,#1
ADD R2,R2,#1
ADD R3,R3,#2
LD R5,NUMBER1023
ADD R0,R0,#-2
BRP START
BRN N2
ADD R7,R7,#1
BRNZP  END
N2 ADD R7,R7,#2
BRNZP END
START ADD R7,R1,R1
ADD R7,R7,R3
ADD R1,R2,#0
ADD R2,R3,#0
ADD R3,R7,#0
ADD R0,R0,#-1
BRP START
AND R7,R7,R5
END HALT
NUMBER1023 .FILL #1023
RESA .FILL #930
RESB .FILL #246
RESC .FILL #386
RESD .FILL #70
.END
```

