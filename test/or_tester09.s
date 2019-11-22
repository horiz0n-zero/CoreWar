.name "or_tester9"

.comment "This champion is a tester for the or function with ind and ind.
			It tests if the or function sets the zero_flag when result is 0.
			It should live infinitly && Print r4 content (*)"

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42
			ld %42, r3
			add r2, r3, r4
			aff r4

test:		ld %0, r3
			or -5, -5, r2
			zjmp %:do_live
