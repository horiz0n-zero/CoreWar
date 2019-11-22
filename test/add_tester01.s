.name "add_tester1"

.comment "This champion is a tester for the add function with reg, reg, reg.
			It tests if the add function sets the zero_flag when result is 0.
			It should live infinitly && Print r4 content (*)"

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42
			ld %42, r2
			add r2, r3, r4
			aff r4

test:		ld %-1 ,r2
			add r1, r2, r3
			zjmp %:do_live
