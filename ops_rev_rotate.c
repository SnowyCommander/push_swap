/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rev_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:32:59 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:33:01 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** 맨 아래 원소가 맨 위가 되도록 스택을 아래로 한 칸 회전시킨다.
** head 를 배열의 이전 칸으로 옮긴 뒤,
** 옛 맨 아래 값(새 기준으로 size 번째 자리)을 새 맨 위에 복사한다.
** size 가 capacity 보다 작으면 head 의 이전 칸이 비어 있으므로
** 복사 없이는 빈 칸이 맨 위로 올라온다.
**
** head 가 0 일 때 이전 칸은 -1 이 되는데,
** & (capacity - 1) 이 2의 보수 비트 패턴을 그대로 잘라 마지막 칸으로 되돌린다.
*/
static void	rev_rotate_stack(t_stack *s)
{
	if (s->size < 2)
	{
		return ;
	}
	s->head = (s->head - 1) & (s->capacity - 1);
	stack_set(s, 0, stack_get(s, s->size));
}

void	op_rra(t_machine *m)
{
	rev_rotate_stack(&m->a);
	append_op_to_bff(m, "rra\n");
}

void	op_rrb(t_machine *m)
{
	rev_rotate_stack(&m->b);
	append_op_to_bff(m, "rrb\n");
}

void	op_rrr(t_machine *m)
{
	rev_rotate_stack(&m->a);
	rev_rotate_stack(&m->b);
	append_op_to_bff(m, "rrr\n");
}
