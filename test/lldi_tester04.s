.name "lldi_tester4"

.comment "This champion is a tester for the ldi function with DIR, REG, REG.
			//
			Print r3 content (*)."

			and %42, %0, r2
			zjmp %:test

loop:		and %42, %0, r2
			zjmp %:loop

test:		ld %0, r2
			live %42
			lldi %568, r2, r3
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
