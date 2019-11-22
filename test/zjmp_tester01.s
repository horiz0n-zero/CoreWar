.name "zjmp_tester1"

.comment "This champion is a tester for the zjmp function
			//
			It should live infinitly."

do_live:	live	%1
			xor		%0, %0, r3
			zjmp	%:do_live
