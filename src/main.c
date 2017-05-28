/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 18:57:39 by amehmeto          #+#    #+#             */
/*   Updated: 2017/05/28 21:18:10 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gmp.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static size_t	ft_strlen_and_limit_gen(char *s, int j, size_t limit, int nb_n)
{
	size_t i;

	if (j == 0)
	{
		i = 0;
		while (s[i])
			i++;
		return (i);
	}
	else if (j == 1)
	{
		if (nb_n < 2)
			return (limit = 20000000);
		else if (nb_n < 10)
			return (limit = limit * 15);
		else if (nb_n < 50)
			return (limit = limit * 10);
		else if (nb_n < 100)
			return (limit = limit * 5);
		else
			return (limit);
	}
	return (0);
}

static void		ft_print(mpz_t n, mpz_t p, mpz_t q)
{
	char	*res;
	char	*fact1;
	char	*fact2;
	char	c[3];

	c[0] = '=';
	c[1] = '*';
	c[2] = '\n';
	res = NULL;
	fact1 = NULL;
	fact2 = NULL;
	res = mpz_get_str(res, 10, n);
	fact1 = mpz_get_str(fact1, 10, p);
	fact2 = mpz_get_str(fact2, 10, q);
	write(1, res, ft_strlen_and_limit_gen(res, 0, 0, 0));
	write(1, &c[0], 1);
	write(1, fact1, ft_strlen_and_limit_gen(fact1, 0, 0, 0));
	write(1, &c[1], 1);
	write(1, fact2, ft_strlen_and_limit_gen(fact2, 0, 0, 0));
	write(1, &c[2], 1);
	free(res);
	free(fact1);
	free(fact2);
}

static void		find_factor(mpz_t n, size_t limit)
{
	mpz_t	p;
	mpz_t	q;
	size_t	i;

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
		ft_print(n, p, q);
	}
	mpz_clears(p, q, NULL);
}

static void		ft_factrace(size_t limit, char *str, int nb_n)
{
	int		i;
	mpz_t	n;

	mpz_init(n);
	limit = ft_strlen_and_limit_gen(NULL, 1, limit, nb_n);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\n')
		{
			find_factor(n, limit);
			mpz_set_ui(n, 0);
		}
		else
		{
			mpz_mul_ui(n, n, 10);
			mpz_add_ui(n, n, (unsigned)str[i] - (unsigned)'0');
		}
	}
	mpz_clear(n);
}

int				main(int ac, char **av)
{
	char	str[51000];
	int		nb_n;
	int		i;

	nb_n = 0;
	if (ac == 2)
	{
		i = -1;
		while (read(0, &str, 50000) > 0)
			while (str[++i])
				if (str[i] == '\n')
					nb_n++;
		ft_factrace((size_t)atoi(av[1]), str, nb_n);
	}
	return (0);
}
