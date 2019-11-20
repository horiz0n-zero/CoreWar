# 
# toto
#

.name"toto".comment"zazou"

# be ready!

start_point:
	live %42
	live %:middle_point

middle_point:
	live %23
	live %:end_point

end_point:
	live %42 #juste because the answer is 42!
	live %:start_point

# be unready now!
