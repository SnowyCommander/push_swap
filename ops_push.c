/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:32:54 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:32:56 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** src 의 맨 위 원소를 dst 의 맨 위로 옮긴다.
** 원형 버퍼에서 맨 위를 빼는 것은 head 를 배열의 다음 칸으로 옮기는 것이고,
** 맨 위에 넣는 것은 head 를 배열의 이전 칸으로 옮긴 뒤 그 자리에 쓰는 것이다.
** 원소를 밀어내는 이동이 전혀 없다.
**
** head 가 0 일 때 이전 칸은 -1 이 되는데,
** & (capacity - 1) 이 2의 보수 비트 패턴을 그대로 잘라 마지막 칸으로 되돌린다.
*/
static void	push_stack(t_stack *dst, t_stack *src)
{
	int	value;

	if (src->size < 1)
	{
		return ;
	}
	value = stack_get(src, 0);
	src->head = (src->head + 1) & (src->capacity - 1);
	--src->size;
	dst->head = (dst->head - 1) & (dst->capacity - 1);
	++dst->size;
	stack_set(dst, 0, value);
}

void	op_pa(t_machine *m)
{
	push_stack(&m->a, &m->b);
	append_op_to_bff(m, "pa\n");
}

void	op_pb(t_machine *m)
{
	push_stack(&m->b, &m->a);
	append_op_to_bff(m, "pb\n");
}
