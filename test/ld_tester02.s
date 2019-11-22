.name "ld_tester2"

.comment "This champion is a tester for the ld function with ind, reg.
			//
			It should load 42 in r2, and print a '*' (42 in ascii table)."

			ld 6, r2
			live %42
			aff r2
			
loop:		xor %0, %0, r3
			zjmp %:loop
