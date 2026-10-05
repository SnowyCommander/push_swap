/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:42 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:33:43 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** 2단계. b 가 빌 때까지, 매번 가장 싼 원소를 골라 a 의 제자리에 넣는다.
** 하나를 넣을 때마다 두 스택이 모두 바뀌므로 비용을 매번 처음부터 다시 계산한다.
*/
static void	insert_all_back(t_machine *m)
{
	int	b_position;

	while (m->b.size > 0)
	{
		b_position = find_cheapest_position(&m->a, &m->b);
		insert_one(m, b_position);
	}
}

/*
** 3단계. 2단계를 마친 a 는 정렬되어 있지만 회전된 상태일 수 있다.
** 최솟값이 위쪽 절반에 있으면 ra, 아래쪽 절반에 있으면 rra 로 더 짧은 방향을 골라
** 최솟값을 맨 위로 올린다.
*/
static void	rotate_min_to_top(t_machine *m)
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
}

/*
** 원소 6개 이상을 정렬한다.
** 1단계로 a 에 3개만 남기고, 그 3개를 정렬한 뒤, 2단계로 b 를 모두 되돌리고,
** 3단계로 최솟값을 맨 위에 맞춘다.
*/
void	sort_big(t_machine *m)
{
	push_chunks_to_b(m);
	sort_three(m);
	insert_all_back(m);
	rotate_min_to_top(m);
}
