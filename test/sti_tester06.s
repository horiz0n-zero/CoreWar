.name "sti_tester6"

.comment "This champion is a tester for the sti function with REG, IND, REG.
			//
			Print r3 content (*)."

			ld %42, r2
			ld %4, r4
			sti r2, -5, r4
			ld %0, r3
			aff r3

loop:		and %42, %0, r2
			zjmp %:loop
