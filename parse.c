/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:21 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/26 15:49:22 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** 숫자 하나의 형식을 검사한다. 숫자는 공백이나 문자열 끝에서 끝난다.
** 부호는 맨 앞에 하나만 허용하고, 부호 뒤에는 숫자가 하나 이상 있어야 한다.
*/
static int	is_valid_format(char *s)
{
	if (*s == '+' || *s == '-')
	{
		++s;
	}
	if (*s == '\0' || *s == ' ')
	{
		return (0);
	}
	while (*s != '\0' && *s != ' ')
	{
		if (*s < '0' || *s > '9')
		{
			return (0);
		}
		++s;
	}
	return (1);
}

static long long	accumulate_digits(char *s)
{
	long long	result;

	result = 0;
	while (*s != '\0' && *s != ' ')
	{
		result = result * 10 + (*s - '0');
		if (result > 2147483648LL)
		{
			exit_error();
		}
		++s;
	}
	return (result);
}

/*
** s 가 가리키는 곳에서 시작하는 숫자 하나를 int 로 바꾼다.
** 숫자는 공백이나 문자열 끝에서 끝나며, 형식이나 범위가 틀리면 Error 로 종료한다.
*/
int	parse_int(char *s)
{
	long long	result;
	int			sign;

	if (is_valid_format(s) == 0)
	{
		exit_error();
	}
	sign = 1;
	if (*s == '-')
	{
		sign = -1;
	}
	if (*s == '-' || *s == '+')
	{
		++s;
	}
	result = accumulate_digits(s);
	if (sign == 1 && result > 2147483647LL)
	{
		exit_error();
	}
	return ((int)(result * sign));
}

int	has_duplicate(t_stack *a)
{
	int	position;
	int	other_position;

	position = 0;
	while (position < a->size)
	{
		other_position = position + 1;
		while (other_position < a->size)
		{
			if (stack_get(a, position) == stack_get(a, other_position))
			{
				return (1);
			}
			++other_position;
		}
		++position;
	}
	return (0);
}
