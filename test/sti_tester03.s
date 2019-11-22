.name "sti_tester3"

.comment "This champion is a tester for the sti function with REG, DIR, DIR.
			//
			Print r3 content (*)."

			ld %42, r2
			sti r2, %6, %3
			ld %0, r3
			aff r3

loop:		and %42, %0, r2
			zjmp %:loop
