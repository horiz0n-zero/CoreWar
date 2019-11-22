.name "xor_tester18"

.comment "This champion is a tester for the xor function with reg and reg.
			It tests if the xor function does not set the zero_flag when result is no null.
			It should never live. And die stupidly... && Print r2 content (*)"

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42

test:		ld %44, r3
			ld %6, r4
			xor r3, r4, r2
			zjmp %:do_live
			aff r2

loop:		xor %0, %0, r3
			zjmp %:loop
