TEST      START   0

BEGIN     LDA     ONE
          STA     I
          LDA     ZERO
          STA     INDEX
          
L1        LDA     ONE
          STA     J
          
L2        LDA     I
          MUL     J
          STA     SUM
          LDA     INDEX
          MUL     THREE
          STA     TEMP
          LDX     TEMP
          LDA     SUM
          STA     ARRAY,X
          LDA     INDEX
          ADD     ONE
          STA     INDEX
          LDA     J
          ADD     ONE
          STA     J
          LDA     J
          COMP    TEN
          JLT     L2
          
          LDA     I
          ADD     ONE
          STA     I
          LDA     I
          COMP    TEN
          JLT     L1

          END     BEGIN

I         RESW    1
J         RESW    1
INDEX     RESW    1
ARRAY     RESW    81
SUM       RESW    1
TEMP      RESW    1

ZERO      WORD    0
ONE       WORD    1
TEN       WORD    10
THREE     WORD    3
