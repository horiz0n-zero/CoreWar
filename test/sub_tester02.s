.name "sub_tester2"

.comment "This champion is a tester for the sub function with reg, reg, reg.
			It tests if the sub function sets the zero_flag when result is 0.
			It should never live. And die stupidly..."

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42

test:		ld %-41 ,r2
			sub r1, r2, r4
			zjmp %:do_live
			aff r4

loop:		xor %0, %0, r3
			zjmp %:loop
