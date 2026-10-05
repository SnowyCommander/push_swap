/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:25 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/26 21:33:39 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** 원소 수에 따라 청크 개수를 고르고, 청크 하나에 들어갈 순위의 개수를 돌려준다.
** 청크 개수 5 와 11 은 출발점이며, 완성 후 bench.py 로 측정해 조정한다.
** + 2명이 "3명을 태우는 차 한 대를 새로 채우기엔 딱 한 명 모자라는" 수를 이용해서 소수를 올림한다.
*/
static int	choose_chunk_size(int n)
{
	int	chunk_count;

	chunk_count = 2;
	if (n > 100)
	{
		chunk_count = 3;
	}
	return ((n + chunk_count - 1) / chunk_count);
}

/*
** 방금 b 에 넣은 원소를 b 의 맨 아래로 보낸다.
** a 의 새 맨 위가 지금 청크 밖이라 어차피 ra 가 필요하면, rb 와 ra 를 rr 하나로 합친다.
*/
static void	sink_to_bottom_of_b(t_machine *m, int limit)
{
	if (m->a.size > 3 && stack_get(&m->a, 0) >= limit)
	{
		op_rr(m);
	}
	else
	{
		op_rb(m);
	}
}

/*
** a 의 맨 위를 b 로 보낸다. 청크의 아래쪽 절반 값이면 b 의 맨 아래로 내린다.
** b 에 원소가 하나뿐이면 rb 가 아무 효과가 없으므로 내리지 않는다.
*/
static void	push_top_to_b(t_machine *m, int rank, int limit, int chunk_size)
{
	op_pb(m);
	if (rank < limit - chunk_size / 2 && m->b.size > 1)
	{
		sink_to_bottom_of_b(m, limit);
	}
}

/*
** 순위를 chunk_size 개씩 구간으로 묶고, 작은 순위 구간에 속하는 a 의 원소부터 b 로 보낸다.
** 구간은 스택의 자리가 아니라 값(순위)의 범위이며, 같은 구간의 원소는 a 여기저기에 흩어져 있다.
** a 에는 3개를 남긴다.
** limit 은 지금 구간의 상한(미만)이다. 앞 구간들은 이미 전부 b 로 갔으므로,
** a 에서 rank < limit 인 원소는 곧 지금 구간의 원소다.
** 순위가 0 부터 n-1 까지 빠짐없이 있으므로 limit 미만 값은 정확히 limit 개이고,
** b 의 크기가 limit 에 이르면 지금 구간을 다 보낸 것이다.
*/
void	push_chunks_to_b(t_machine *m)
{
	int	chunk_size;
	int	limit;
	int	rank;

	chunk_size = choose_chunk_size(m->a.size);
	limit = chunk_size;
	while (m->a.size > 3)
	{
		rank = stack_get(&m->a, 0);
		if (rank < limit)
		{
			push_top_to_b(m, rank, limit, chunk_size);
			if (m->b.size == limit)
			{
				limit = limit + chunk_size;
			}
		}
		else
		{
			op_ra(m);
		}
	}
}
