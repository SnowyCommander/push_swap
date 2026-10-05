/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:29 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 22:47:45 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

/*
** 출력 버퍼 크기.
** 500개 정렬 시 명령어 약 5,500개 × 한 줄 최대 4바이트("rrr\n") = 약 22KB.
** 여유를 두어 32KB 로 잡았고, 이 크기면 write 가 단 한 번만 호출된다.
**
** 이 값이 실제 필요량보다 작아도 동작에는 문제가 없다.
** append_op_to_bff 가 넘칠 것을 미리 감지해 flush 한 뒤 이어서 쓰기 때문이다.
** 즉 이 상수는 write 호출 횟수만 좌우하고, 출력 내용에는 영향을 주지 않는다.
*/
# define BUFFER_SIZE 32768

/*
** 원형 버퍼 위에 놓인 스택.
** position : 스택의 위에서 몇 번째인가 (0 이 맨 위). 스택을 다루는 모든 코드가 쓰는 번호.
** idx      : data 배열의 몇 번 칸인가. access.c 안에서만 쓰는 번호.
** 둘은 idx = (head + position) & (capacity - 1) 로 연결되며, head 가 0 일 때만 같다.
*/
typedef struct s_stack
{
	int	*data;
	int	head;
	int	size;
	int	capacity;
}	t_stack;

/*
** push_swap 을 두 스택과 명령어 출력 포트를 가진 하나의 기계로 본다.
** 전역 변수 없이 이 구조체 하나를 함수 사이로 넘겨 상태를 전달한다.
*/
typedef struct s_machine
{
	t_stack	a;
	t_stack	b;
	char	bff[BUFFER_SIZE];
	int		bff_len;
}	t_machine;

/* error.c */
void	exit_error(void);
void	exit_error_free(t_stack *a, t_stack *b);

/* parse.c */
int		parse_int(char *s);
int		has_duplicate(t_stack *a);

/* args.c */
int		count_numbers(char **args, int arg_count);
void	fill_stack(t_stack *a, char **args, int arg_count);

/* stack.c */
void	init_stacks(t_stack *a, t_stack *b, int count);
void	free_stacks(t_stack *a, t_stack *b);
/* access.c */
int		stack_get(t_stack *s, int position);
void	stack_set(t_stack *s, int position, int value);

/* output.c */
void	append_op_to_bff(t_machine *m, const char *op);
void	flush_bff(t_machine *m);

/* ops_swap.c */
void	op_sa(t_machine *m);
void	op_sb(t_machine *m);
void	op_ss(t_machine *m);

/* ops_push.c */
void	op_pa(t_machine *m);
void	op_pb(t_machine *m);

/* ops_rotate.c */
void	op_ra(t_machine *m);
void	op_rb(t_machine *m);
void	op_rr(t_machine *m);

/* ops_rev_rotate.c */
void	op_rra(t_machine *m);
void	op_rrb(t_machine *m);
void	op_rrr(t_machine *m);

/* sort_utils.c */
int		is_sorted(t_stack *s);
int		find_min_position(t_stack *s);
int		find_target_position(t_stack *a, int value);

/* ranks.c */
void	compress_ranks(t_stack *a, t_stack *b);

/* sort_small.c */
void	sort_two(t_machine *m);
void	sort_three(t_machine *m);

/* sort_medium.c */
void	sort_four_five(t_machine *m);

/* push_chunks.c */
void	push_chunks_to_b(t_machine *m);

/* sort.c */
void	sort_stack(t_machine *m);

/* cost.c */
int		count_rotations_to_insert(t_stack *a, t_stack *b, int b_position);
int		find_cheapest_position(t_stack *a, t_stack *b);
int		find_cheapest_way(t_stack *a, t_stack *b, int b_position);

/* insert.c */
void	insert_one(t_machine *m, int b_position);

/* sort_big.c */
void	sort_big(t_machine *m);

#endif /* PUSH_SWAP_H */
