/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:50 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:33:51 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** 스택에서 가장 큰 값이 위에서 몇 번째에 있는지 찾는다.
** 돌려주는 값은 position(스택 위치)이며, idx(배열 칸 번호)가 아니다.
*/
static int	find_max_position(t_stack *s)
{
	int	max_position;
	int	position;

	max_position = 0;
	position = 1;
	while (position < s->size)
	{
		if (stack_get(s, position) > stack_get(s, max_position))
		{
			max_position = position;
		}
		++position;
	}
	return (max_position);
}

void	sort_two(t_machine *m)
{
	if (stack_get(&m->a, 0) > stack_get(&m->a, 1))
	{
		op_sa(m);
	}
}

/*
** 1. 최댓값을 맨 아래로 보낸다. 맨 위에 있으면 ra, 가운데 있으면 rra.
** 2. 남은 위 두 개가 뒤집혀 있으면 sa.
** 5가지 경우 모두 최대 2수로 끝나며, 이것이 3개 정렬의 최적이다.
** 값이 0, 1, 2 라고 가정하지 않고 크기를 비교하므로,
** 더 큰 정렬 안에서 순위가 5, 8, 9 같은 원소 셋을 정렬할 때도 그대로 쓸 수 있다.
*/
void	sort_three(t_machine *m)
{
	int	max_position;

	max_position = find_max_position(&m->a);
	if (max_position == 0)
	{
		op_ra(m);
	}
	else if (max_position == 1)
	{
		op_rra(m);
	}
	if (stack_get(&m->a, 0) > stack_get(&m->a, 1))
	{
		op_sa(m);
	}
}
