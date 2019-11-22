.name "ld_tester4"

.comment "This champion is a tester for the ld function with dir, reg.
			It tests if the ld function does not set the zero_flag when result is no null.
			It should never live. And die stupidly..."

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42

test:		ld %42, r2
			zjmp %:do_live

loop:		xor %0, %0, r3
			zjmp %:loop
