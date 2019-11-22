.name "ldi_tester3"

.comment "This champion is a tester for the ldi function with DIR, DIR, REG.
			//
			Print r3 content (*)."

			live %42
			ldi %-4, %0, r3
			aff r3

loop:		and %42, %0, r2
			zjmp %:loop
