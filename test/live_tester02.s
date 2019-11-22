.name "live_tester"

.comment "This champion is a tester for the live function
			//
			It should live infinitly"

do_live:	xor %42, %42, r2
			live	%1
			zjmp %:do_live
