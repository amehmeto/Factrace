#include "../includes/f.h"

size_t	ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


void	ft_print(mpz_t n, mpz_t p, mpz_t q)
{
	char		*res;
	char		*fact1;
	char		*fact2;
	char c1;
	char c2;
	char c3;

	c1 = '=';
	c2 = '*';
	c3 = '\n';

	res = NULL;
	fact1 = NULL;
	fact2 = NULL;
	res = mpz_get_str(res, 10, n);
	fact1 = mpz_get_str(fact1, 10, p);
	fact2 = mpz_get_str(fact2, 10, q);

	write(1, res, ft_strlen(res));
	write(1, &c1, 1);
	write(1, fact1, ft_strlen(fact1));
	write(1, &c2, 1);
	write(1, fact2, ft_strlen(fact2));
	write(1, &c3, 1);

	free(res);
	free(fact1);
	free(fact2);
}

void		find_factor(mpz_t n, size_t limit)
{
	mpz_t	p;
	mpz_t	q;
	size_t i;

	mpz_init(p);
	mpz_init(q);
	mpz_set_ui(p, 2);
	i = 0;
	while (!mpz_divisible_p(n, p) && i < limit)
	{
		mpz_nextprime(p, p);
		i++;
	}
	if (i < limit)
	{
		mpz_cdiv_q(q, n, p);
		ft_print(n,p,q);
		// gmp_printf("%Zd=%Zd*%Zd\n", n, p, q);
	}
	mpz_clears(p, q, NULL);	
}

void	ft_factrace(int limit)
{
	int i;
	int nb_n;
	char str[51000];
	mpz_t n;

	i = 0;
	nb_n = 0;
	mpz_init(n);
	while (read(0, &str, 50000) > 0)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				nb_n++;
			i++;
		}
	}

	// printf("%d\n", nb_n);
	if (nb_n < 2)
		limit = 20000000;
	else if (nb_n < 10)
		limit = limit * 15;
	else if (nb_n < 50)
		limit = limit * 10;
	else if (nb_n < 100)
		limit = limit * 5;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			find_factor(n, limit);
			mpz_set_ui(n, 0);
		}
		else
		{
			mpz_mul_ui(n, n, 10);
			mpz_add_ui(n, n, str[i] - '0');
		}
		i++;
	}
	mpz_clear(n);
}

int main(int ac,char **av)
{
	size_t limit;

	if (ac == 2)
	{
		limit = atoi(av[1]);
		ft_factrace(limit);
	}
	return 0;
}