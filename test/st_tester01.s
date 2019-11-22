.name "st_tester1"

.comment "This champion is a tester for the st function with reg, ind.
			//
			It should store 42 after live."

			ld %42, r3
			st r3, 7
			ld %0, r2
			aff r2

loop:		xor %0, %0, r3
			zjmp %:loop
