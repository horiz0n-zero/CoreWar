# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    labels.s                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/24 09:07:15 by afeuerst          #+#    #+#              #
#    Updated: 2019/11/24 09:12:58 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# a labels test

.name "labels"
.comment "labels is a futur vision"

live %42
start: live %42
	zjmp %:end
	zjmp %:end
	zjmp %:start
middle: zjmp %:middle

end: live %42
	zjmp %:start
	zjmp %:end
