/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:07 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:33:09 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** 맨 위 원소가 맨 아래가 되도록 스택을 위로 한 칸 회전시킨다.
** 맨 위 값을 현재 맨 아래의 다음 칸(= size 번째 자리)에 복사한 뒤
** head 를 배열의 다음 칸으로 옮긴다.
** size 가 capacity 보다 작으면 맨 아래 다음 칸이 비어 있으므로
** head 만 옮기면 빈 칸이 맨 아래로 들어오게 된다. 복사가 반드시 필요하다.
*/
static void	rotate_stack(t_stack *s)
{
	if (s->size < 2)
	{
		return ;
	}
	stack_set(s, s->size, stack_get(s, 0));
	s->head = (s->head + 1) & (s->capacity - 1);
}

void	op_ra(t_machine *m)
{
	rotate_stack(&m->a);
	append_op_to_bff(m, "ra\n");
}

void	op_rb(t_machine *m)
{
	rotate_stack(&m->b);
	append_op_to_bff(m, "rb\n");
}

void	op_rr(t_machine *m)
{
	rotate_stack(&m->a);
	rotate_stack(&m->b);
	append_op_to_bff(m, "rr\n");
}
