.name "lldi_tester2"

.comment "This champion is a tester for the ldi function with IND, REG, REG.
			//
			Print r3 content (*)."

			and %42, %0, r2
			zjmp %:test

loop:		and %42, %0, r2
			zjmp %:loop

test:		ld %-2, r2
			live %42
			lldi 571, r2, r3
			aff r3
			and %42, %0, r2
			zjmp %:loop

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

			live %-2
