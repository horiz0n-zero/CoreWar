.name "sti_tester5"

.comment "This champion is a tester for the sti function with REG, IND, DIR.
			//
			Print r3 content (*)."

			ld %42, r2
			ld %4, r3
			sti r2, -5, %5
			ld %0, r3
			aff r3

loop:		and %42, %0, r2
			zjmp %:loop
