/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:34:04 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 22:45:42 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	round_up_power_of_two(int n)
{
	int	capacity;

	capacity = 1;
	while (capacity < n)
	{
		capacity = capacity * 2;
	}
	return (capacity);
}

void	init_stacks(t_stack *a, t_stack *b, int count)
{
	int	capacity;

	capacity = round_up_power_of_two(count);
	a->data = malloc(sizeof(int) * capacity);
	if (a->data == NULL)
	{
		exit_error();
	}
	b->data = malloc(sizeof(int) * capacity);
	if (b->data == NULL)
	{
		free(a->data);
		exit_error();
	}
	a->head = 0;
	a->size = 0;
	a->capacity = capacity;
	b->head = 0;
	b->size = 0;
	b->capacity = capacity;
}

void	free_stacks(t_stack *a, t_stack *b)
{
	free(a->data);
	free(b->data);
	a->data = NULL;
	b->data = NULL;
	a->head = 0;
	a->size = 0;
	b->head = 0;
	b->size = 0;
}
