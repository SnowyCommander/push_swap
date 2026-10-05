/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:16 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:33:18 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	flush_bff(t_machine *m)
{
	if (m->bff_len > 0)
	{
		write(1, m->bff, m->bff_len);
		m->bff_len = 0;
	}
}

/*
** op 는 "sa\n" 같은 문자열 리터럴이라 읽기 전용 영역에 놓인다.
** 수정 시도를 컴파일 단계에서 막기 위해 const 를 붙였다.
*/
void	append_op_to_bff(t_machine *m, const char *op)
{
	int	len;
	int	i;

	len = 0;
	while (op[len] != '\0')
	{
		++len;
	}
	if (m->bff_len + len > BUFFER_SIZE)
	{
		flush_bff(m);
	}
	i = 0;
	while (i < len)
	{
		m->bff[m->bff_len] = op[i];
		++m->bff_len;
		++i;
	}
}
