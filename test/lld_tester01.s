.name "lld_tester1"

.comment "This champion is a tester for the lld function with dir, reg.
			//
			It should load 42 in r2, and print a '*' (42 in ascii table)."

			lld %42, r2

trash:		and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3

display:	aff r2

loop:		xor %0, %0, r3
			zjmp %:loop
