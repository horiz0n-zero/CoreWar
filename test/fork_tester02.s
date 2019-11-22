.name "fork_tester2"

.comment "This champion is a tester for the fork function with dir == 0.
			It tests if the fork function fork a process.
			The new process should live infinitly."

test:		fork %4117

loop:		xor %42, %42, r2
			zjmp %:loop

do_live:	st r1, 6
			live %42
			xor %42, %42, r2
			zjmp %:do_live
