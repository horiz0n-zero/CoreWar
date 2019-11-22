.name "ld_tester1"

.comment "This champion is a tester for the ld function with dir, reg.
			//
			It should load 42 in r2, and print a '*' (42 in ascii table)."

			ld %42, r2
			aff r2

loop:		xor %0, %0, r3
			zjmp %:loop
