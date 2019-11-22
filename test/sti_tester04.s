.name "sti_tester4"

.comment "This champion is a tester for the sti function with REG, DIR, REG.
			//
			Print r3 content (*)."

			ld %42, r2
			ld %8, r4
			sti r2, %0, r4
			ld %0, r3
			aff r3

loop:		and %42, %0, r2
			zjmp %:loop
