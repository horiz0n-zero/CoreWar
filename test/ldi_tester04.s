.name "ldi_tester4"

.comment "This champion is a tester for the ldi function with DIR, REG, REG.
			//
			Print r3 content (*)."

			ld %-2, r2
			live %42
			ldi %-2, r2, r3
			aff r3

loop:		and %42, %0, r2
			zjmp %:loop
