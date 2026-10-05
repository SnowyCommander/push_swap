/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:55 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:33:56 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** 스택이 맨 위부터 오름차순인지 확인한다.
** 원소가 0개나 1개면 반복문이 돌지 않고 1을 반환한다. 하나뿐인 원소는 정렬된 상태다.
*/
int	is_sorted(t_stack *s)
{
	int	position;

	position = 0;
	while (position < s->size - 1)
	{
		if (stack_get(s, position) > stack_get(s, position + 1))
		{
			return (0);
		}
		++position;
	}
	return (1);
}

/*
** 스택에서 가장 작은 값이 위에서 몇 번째에 있는지 찾는다.
** 돌려주는 값은 position(스택 위치)이며, idx(배열 칸 번호)가 아니다.
*/
int	find_min_position(t_stack *s)
{
	int	min_position;
	int	position;

	min_position = 0;
	position = 1;
	while (position < s->size)
	{
		if (stack_get(s, position) < stack_get(s, min_position))
		{
			min_position = position;
		}
		++position;
	}
	return (min_position);
}

/*
** value 를 a 의 제자리에 넣으려면 pa 직전에 무엇이 a 의 맨 위에 있어야 하는지,
** 그 값의 position 을 돌려준다.
** 1. a 에 value 보다 큰 값이 있으면, 그중 가장 작은 값의 위치
** 2. 없으면(value 가 a 의 모든 값보다 크면), a 의 최솟값의 위치
** 두 경우 모두 "정렬 순서상 value 의 바로 다음 자리"이며,
** 2번은 a 가 원형이라 맨 끝 다음이 맨 처음으로 돌아오는 경우다.
*/
int	find_target_position(t_stack *a, int value)
{
	int	target_position;
	int	position;
	int	current;

	target_position = -1;
	position = 0;
	while (position < a->size)
	{
		current = stack_get(a, position);
		if (current > value && (target_position == -1
				|| current < stack_get(a, target_position)))
		{
			target_position = position;
		}
		++position;
	}
	if (target_position == -1)
	{
		return (find_min_position(a));
	}
	return (target_position);
}
