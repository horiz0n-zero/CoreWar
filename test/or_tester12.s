.name "or_tester12"

.comment "This champion is a tester for the or function with ind and reg.
			It tests if the or function does not set the zero_flag when result is no null.
			  It should never live. And die stupidly... && Print r2 content (*)"

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42

test:		ld %34, r3
			ld %8, r4
			or -5, r3, r2
			zjmp %:do_live
			aff r2

loop:		xor %0, %0, r3
			zjmp %:loop
