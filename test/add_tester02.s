.name "add_tester2"

.comment "This champion is a tester for the add function with reg, reg, reg.
			It tests if the add function sets the zero_flag when result is 0.
			It should never live. And die stupidly...  & Print r4 content (*)"

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42

test:		ld %1, r5
			add r5, r5, r3
			zjmp %:do_live
			ld %40, r2
			add r2, r3, r4
			aff r4

loop:		xor %0, %0, r3
			zjmp %:loop
