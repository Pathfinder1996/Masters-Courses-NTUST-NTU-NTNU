SUM       	START   	511
FIRST      	LDX      	ZERO
            LDA      	ZERO
LOOP      	ADD    		TABLE,X
            TIX      	COUNT
            JLT       	LOOP
            STA      	TOTAL
            RSUB		
TABLE      	RESW     	200
COUNT    	RESW     	1
ZERO       	WORD   		0
TOTAL      	RESW     	1
            END    	  	LOOP