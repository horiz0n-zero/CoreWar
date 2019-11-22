.name "fork_tester1"

.comment "This champion is a tester for the fork function with dir.
			It tests if the fork function fork a process.
			The new process should live infinitly."

test:		fork %:do_live

loop:		xor %42, %42, r2
			zjmp %:loop

do_live:	st r1, 6
			live %42
			xor %42, %42, r2
			zjmp %:do_live
