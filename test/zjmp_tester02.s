.name "zjmp_tester2"

.comment "This champion is a tester for the zjmp function
			//
			It should never live. And die stupidly..."

test:		xor		%42, %0, r3
			zjmp	%:do_live
			xor		%0, %0, r3
			zjmp	%:test

do_live:	live	%1
