.name "lldi_tester6"

.comment "This champion is a tester for the ldi function with REG, REG, REG.
			//
			Print r3 content (*)."

			and %42, %0, r2
			zjmp %:test

loop:		and %42, %0, r2
			zjmp %:loop

test:		ld %286, r4
			ld %287, r3
			live %42
			lldi r3, r4, r3
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

			live %42
