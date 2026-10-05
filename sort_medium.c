/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:45 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:33:47 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** a 의 최솟값을 맨 위로 끌어올려 b 로 보낸다.
** 위쪽 절반에 있으면 ra, 아래쪽 절반에 있으면 rra 로 더 짧은 방향을 고른다.
*/
static void	push_min_to_b(t_machine *m)
{
	int	min_position;
	int	count;

	min_position = find_min_position(&m->a);
	if (min_position <= m->a.size / 2)
	{
		count = min_position;
		while (count > 0)
		{
			op_ra(m);
			--count;
		}
	}
	else
	{
		count = m->a.size - min_position;
		while (count > 0)
		{
			op_rra(m);
			--count;
		}
	}
	op_pb(m);
}

/*
** 최솟값을 하나씩 b 로 보내 a 를 3개로 줄이고, 3개 정렬 후 전부 되돌린다.
** 작은 값부터 보냈으므로 b 에는 큰 값이 위에 쌓여 있고,
** pa 할 때마다 a 의 맨 위에 더 작은 값이 올라와 정렬 순서가 맞는다.
*/
void	sort_four_five(t_machine *m)
{
	while (m->a.size > 3)
	{
		push_min_to_b(m);
	}
	sort_three(m);
	while (m->b.size > 0)
	{
		op_pa(m);
	}
}
