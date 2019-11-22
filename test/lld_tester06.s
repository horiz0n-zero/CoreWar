.name "lld_tester5"

.comment "This champion is a tester for the lld function with ind and reg.
			It tests if the lld function does not set the zero_flag when result is no null.
			It should never live. And die stupidly... && Print r2 content (*)"

			xor %42, %42, r2
			zjmp %:test

do_live:	st r1, 6
			live %42

test:		lld 628, r2
			zjmp %:do_live

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
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			and %42, %42, r3
			aff r2

display:	live %42

loop:		xor %0, %0, r3
			zjmp %:loop
