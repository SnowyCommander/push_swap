/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 22:41:33 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/26 16:00:19 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*skip_spaces(char *s)
{
	while (*s == ' ')
	{
		++s;
	}
	return (s);
}

static char	*skip_number(char *s)
{
	while (*s != '\0' && *s != ' ')
	{
		++s;
	}
	return (s);
}

/*
** 인자 하나 안의 숫자들을 검증하며 개수를 센다.
** 숫자가 하나도 없는 인자("" 나 " ")는 Error 로 종료한다.
*/
static int	count_in_arg(char *arg)
{
	int	count;

	count = 0;
	arg = skip_spaces(arg);
	while (*arg != '\0')
	{
		parse_int(arg);
		++count;
		arg = skip_number(arg);
		arg = skip_spaces(arg);
	}
	if (count == 0)
	{
		exit_error();
	}
	return (count);
}

/*
** 모든 인자의 모든 숫자를 검증하고 총 개수를 돌려준다. 메모리 할당 전에 부른다.
** args 는 &argv[1] 이므로 args[0] 이 첫 번째 인자다.
*/
int	count_numbers(char **args, int arg_count)
{
	int	total;
	int	i;

	total = 0;
	i = 0;
	while (i < arg_count)
	{
		total = total + count_in_arg(args[i]);
		++i;
	}
	return (total);
}

/*
** 모든 인자를 다시 훑으며 숫자를 순서대로 a 에 채운다.
** 이미 count_numbers 로 검증했으므로 여기서는 실패하지 않는다.
** 처음 만나는 숫자가 스택의 맨 위(position 0)다.
*/
void	fill_stack(t_stack *a, char **args, int arg_count)
{
	int		position;
	int		i;
	char	*s;

	position = 0;
	i = 0;
	while (i < arg_count)
	{
		s = skip_spaces(args[i]);
		while (*s != '\0')
		{
			stack_set(a, position, parse_int(s));
			++position;
			s = skip_number(s);
			s = skip_spaces(s);
		}
		++i;
	}
	a->size = position;
}
