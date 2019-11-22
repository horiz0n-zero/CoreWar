.name "sub_tester1"

.comment "This champion is a tester for the sub function with reg, reg, reg.
			It tests if the sub function sets the zero_flag when result is 0.
			It should live infinitly && Print r4 content (*)"

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42
			ld %42, r2
			add r2, r3, r4
			aff r4


test:		sub r1, r1, r3
			st r3, 9
			zjmp %:do_live
			live %42
