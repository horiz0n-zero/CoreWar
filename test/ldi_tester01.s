.name "ldi_tester1"

.comment "This champion is a tester for the ldi function with IND, DIR, REG.
			//
			Print r3 content (*)."

			live %-2
			live %42
			ldi -9, %-2, r3
			aff r3

loop:		and %42, %0, r2
			zjmp %:loop
