/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:31:05 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:31:13 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** 스택 위치(position)를 배열 칸 번호(idx)로 번역하는 곳은 이 파일뿐이다.
** 나머지 코드는 전부 position 만 다루므로, 원형 버퍼 계산을 빠뜨릴 수 없다.
*/
int	stack_get(t_stack *s, int position)
{
	int	idx;

	idx = (s->head + position) & (s->capacity - 1);
	return (s->data[idx]);
}

void	stack_set(t_stack *s, int position, int value)
{
	int	idx;

	idx = (s->head + position) & (s->capacity - 1);
	s->data[idx] = value;
}
