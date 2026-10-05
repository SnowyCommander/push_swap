/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:32:45 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:32:46 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** 스택 하나만 count 번 돌린다. is_a 가 1 이면 a, 0 이면 b.
** up 이 1 이면 위로(ra/rb), 0 이면 아래로(rra/rrb) 돌린다.
*/
static void	rotate_one(t_machine *m, int count, int is_a, int up)
{
	while (count > 0)
	{
		if (is_a == 1 && up == 1)
		{
			op_ra(m);
		}
		else if (is_a == 1)
		{
			op_rra(m);
		}
		else if (up == 1)
		{
			op_rb(m);
		}
		else
		{
			op_rrb(m);
		}
		--count;
	}
}

/*
** 두 스택을 같은 방향으로 돌린다.
** 겹치는 동안은 rr(또는 rrr)로 합쳐 한 수에 처리하고, 남은 쪽만 따로 돌린다.
** 그래서 실제 연산 수가 두 횟수 중 더 큰 값이 되며, 비용 계산의 pick_greater 와 맞는다.
*/
static void	rotate_both(t_machine *m, int a_count, int b_count, int up)
{
	while (a_count > 0 && b_count > 0)
	{
		if (up == 1)
		{
			op_rr(m);
		}
		else
		{
			op_rrr(m);
		}
		--a_count;
		--b_count;
	}
	rotate_one(m, a_count, 1, up);
	rotate_one(m, b_count, 0, up);
}

/*
** find_cheapest_way 가 돌려준 조합 번호대로 두 스택을 돌린다.
** 0: ra + rb   1: rra + rrb   2: ra + rrb   3: rra + rb
*/
static void	rotate_by_way(t_machine *m, int a_up, int b_up, int way)
{
	if (way == 0)
	{
		rotate_both(m, a_up, b_up, 1);
	}
	else if (way == 1)
	{
		rotate_both(m, m->a.size - a_up, m->b.size - b_up, 0);
	}
	else if (way == 2)
	{
		rotate_one(m, a_up, 1, 1);
		rotate_one(m, m->b.size - b_up, 0, 0);
	}
	else
	{
		rotate_one(m, m->a.size - a_up, 1, 0);
		rotate_one(m, b_up, 0, 1);
	}
}

/*
** b 의 b_position 번째 원소를 a 의 제자리에 넣는다.
** 회전을 모두 끝낸 뒤에 pa 한다. pa 는 지금 a 의 맨 위 바로 앞에 끼워 넣으므로,
** 순서를 바꾸면 되돌릴 수 없는 자리에 들어간다.
*/
void	insert_one(t_machine *m, int b_position)
{
	int	a_up;
	int	way;

	a_up = find_target_position(&m->a, stack_get(&m->b, b_position));
	way = find_cheapest_way(&m->a, &m->b, b_position);
	rotate_by_way(m, a_up, b_position, way);
	op_pa(m);
}
