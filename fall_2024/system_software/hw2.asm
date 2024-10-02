TEST    START   0

        LDA     #1
        RMO     A,S        ;I = 1
        LDA     #0
        RMO     A,B        ;INDEX = 0

L1      LDA     #1
        RMO     A,T        ;J = 1

L2      RMO     B,A        
        MUL     #3         
        RMO     A,X       
        RMO     T,A        
        MULR    S,A        
        STA     ARRAY,X
        RMO     B,A      
        ADD     #1        
        RMO     A,B        
        RMO     T,A       
        ADD     #1        
        RMO     A,T       
        RMO     T,A       
        COMP    #10
        JLT     L2         

        RMO     S,A       
        ADD     #1      
        RMO     A,S     
        RMO     S,A       
        COMP    #10
        JLT     L1 

        END     TEST

ARRAY   RESW    81
