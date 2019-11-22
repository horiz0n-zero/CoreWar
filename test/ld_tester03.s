.name "ld_tester3"

.comment "This champion is a tester for the ld function with dir, reg.
			It tests if the ld function sets the zero_flag when result is 0.
			It should live infinitly"

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42

test:		ld %0, r2
			zjmp %:do_live
