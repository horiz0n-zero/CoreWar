.name "sti_tester2"

.comment "This champion is a tester for the sti function with REG, REG, REG.
			//
			Print r3 content (*)."

			ld %42, r2
			ld %3, r4
			ld %4, r5
			sti r2, r4, r5
			ld %0, r3
			aff r3

loop:		and %42, %0, r2
			zjmp %:loop
