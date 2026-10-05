/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:32:49 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/26 15:56:03 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_machine	m;
	int			count;

	if (argc < 2)
	{
		return (0);
	}
	m.bff_len = 0;
	count = count_numbers(&argv[1], argc - 1);
	init_stacks(&m.a, &m.b, count);
	fill_stack(&m.a, &argv[1], argc - 1);
	if (has_duplicate(&m.a) == 1)
	{
		exit_error_free(&m.a, &m.b);
	}
	if (is_sorted(&m.a) == 0)
	{
		compress_ranks(&m.a, &m.b);
		sort_stack(&m);
	}
	flush_bff(&m);
	free_stacks(&m.a, &m.b);
	return (0);
}
