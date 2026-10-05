/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:32:31 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:32:34 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	pick_greater(int x, int y)
{
	if (x > y)
	{
		return (x);
	}
	return (y);
}

/*
** b 의 b_position 번째 원소를 a 의 제자리에 넣는 데 드는 회전 수를 센다.
** 마지막에 붙는 pa 1 수는 어느 원소든 같으므로 세지 않는다.
**
** a 를 위로 a_up 번 돌리면 목표 값이 a 의 맨 위에 오고, 아래로는 a->size - a_up 번이다.
** b 도 마찬가지로 위로 b_up 번, 아래로 b->size - b_up 번이다.
** 두 스택을 같은 방향으로 돌릴 때는 겹치는 만큼 rr(또는 rrr)로 합칠 수 있어
** 비용이 합이 아니라 더 큰 쪽이 되고, 방향이 다르면 합칠 수 없어 합이 된다.
** 네 조합 중 가장 작은 값을 돌려준다.
*/
int	count_rotations_to_insert(t_stack *a, t_stack *b, int b_position)
{
	int	a_up;
	int	b_up;
	int	best;
	int	cost;

	a_up = find_target_position(a, stack_get(b, b_position));
	b_up = b_position;
	best = pick_greater(a_up, b_up);
	cost = pick_greater(a->size - a_up, b->size - b_up);
	if (cost < best)
	{
		best = cost;
	}
	cost = a_up + (b->size - b_up);
	if (cost < best)
	{
		best = cost;
	}
	cost = (a->size - a_up) + b_up;
	if (cost < best)
	{
		best = cost;
	}
	return (best);
}

/*
** count_rotations_to_insert 와 같은 순서로 같은 네 값을 비교하여,
** 가장 싼 조합의 번호를 돌려준다. 계산과 실행이 어긋나지 않도록 판단을 한곳에 모은다.
** 0: ra + rb   1: rra + rrb   2: ra + rrb   3: rra + rb
*/
int	find_cheapest_way(t_stack *a, t_stack *b, int b_position)
{
	int	a_up;
	int	b_up;
	int	best;
	int	way;

	a_up = find_target_position(a, stack_get(b, b_position));
	b_up = b_position;
	best = pick_greater(a_up, b_up);
	way = 0;
	if (pick_greater(a->size - a_up, b->size - b_up) < best)
	{
		best = pick_greater(a->size - a_up, b->size - b_up);
		way = 1;
	}
	if (a_up + (b->size - b_up) < best)
	{
		best = a_up + (b->size - b_up);
		way = 2;
	}
	if ((a->size - a_up) + b_up < best)
	{
		way = 3;
	}
	return (way);
}

/*
** b 의 모든 원소 중 회전 비용이 가장 작은 것의 position 을 돌려준다.
** 비용이 같으면 먼저 찾은 것(b 의 위쪽)을 고른다.
*/
int	find_cheapest_position(t_stack *a, t_stack *b)
{
	int	best_position;
	int	best_cost;
	int	position;
	int	cost;

	best_position = 0;
	best_cost = count_rotations_to_insert(a, b, 0);
	position = 1;
	while (position < b->size)
	{
		cost = count_rotations_to_insert(a, b, position);
		if (cost < best_cost)
		{
			best_cost = cost;
			best_position = position;
		}
		++position;
	}
	return (best_position);
}
