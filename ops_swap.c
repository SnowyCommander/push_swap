/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:11 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:33:14 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_stack(t_stack *s)
{
	int	tmp;

	if (s->size < 2)
	{
		return ;
	}
	tmp = stack_get(s, 0);
	stack_set(s, 0, stack_get(s, 1));
	stack_set(s, 1, tmp);
}

void	op_sa(t_machine *m)
{
	swap_stack(&m->a);
	append_op_to_bff(m, "sa\n");
}

void	op_sb(t_machine *m)
{
	swap_stack(&m->b);
	append_op_to_bff(m, "sb\n");
}

void	op_ss(t_machine *m)
{
	swap_stack(&m->a);
	swap_stack(&m->b);
	append_op_to_bff(m, "ss\n");
}
