.name "xor_tester17"

.comment "This champion is a tester for the xor function with reg and reg.
			It tests if the xor function sets the zero_flag when result is 0.
			It should live infinitly && Print r4 content (*)"

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42
			ld %42, r3
			add r2, r3, r4
			aff r4

test:		xor r3, r3, r2
			zjmp %:do_live
