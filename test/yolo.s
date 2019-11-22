.name "Trololo"
.comment "gngngngngngngngnn"

	ld		%0, r3
	ld		%-1, r5
	ld		%4, r6
lol:
	live	%1
	live	%2
	add		r3, r6, r3
	sti		r5, %:yolol, r3
	ld		%0, r4
	zjmp	%:lol

yolol:
	ld		%0, r3
