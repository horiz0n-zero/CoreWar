.name "st_tester2"

.comment "This champion is a tester for the st function with reg, reg.
			//
			It should store 42 from r2 to r3, then store r3 after live."

			ld %42, r2
			st r2, r3
			aff r3

loop:		xor %0, %0, r3
			zjmp %:loop
