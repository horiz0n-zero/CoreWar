.name "xor_tester6"

.comment "This champion is a tester for the xor function with dir and reg.
			It tests if the xor function does not set the zero_flag when result is no null.
			It should never live. And die stupidly... && Print r2 content (*)"

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42

test:		ld %6, r3
			xor %44, r3, r2
			zjmp %:do_live
			aff r2

loop:		xor %0, %0, r3
			zjmp %:loop
