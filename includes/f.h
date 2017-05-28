#ifndef F_H
# define F_H

# include "gmp.h"

# include <string.h>
# include <stdio.h>
#include <unistd.h>
# include <stdlib.h>

typedef struct 		lst
{
	mpz_t			nb;
	struct 	lst		*next;
}					t_lst;

#endif