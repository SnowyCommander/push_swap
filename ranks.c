/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:33:37 by jiylee            #+#    #+#             */
/*   Updated: 2026/09/25 20:33:39 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_int(int *x, int *y)
{
	int	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

/*
** root 자리의 값이 자식보다 작으면, 더 큰 자식과 자리를 바꾸며 아래로 내려보낸다.
** 자식이 없거나 자식들보다 크거나 같아지면 멈춘다.
** 배열을 트리로 보면 idx 번 칸의 왼쪽 자식은 2*idx+1, 오른쪽 자식은 2*idx+2 번 칸이다.
** root, left, largest 는 모두 idx(배열 칸 번호) 종류이며, 트리에서의 역할을 이름으로 나타냈다.
*/
static void	sift_down(int *arr, int size, int root)
{
	int	largest;
	int	left;

	while (1)
	{
		largest = root;
		left = 2 * root + 1;
		if (left < size && arr[left] > arr[largest])
		{
			largest = left;
		}
		if (left + 1 < size && arr[left + 1] > arr[largest])
		{
			largest = left + 1;
		}
		if (largest == root)
		{
			return ;
		}
		swap_int(&arr[root], &arr[largest]);
		root = largest;
	}
}

/*
** 1단계: 자식이 있는 마지막 칸부터 0번까지 sift_down 하여 최대 힙을 만든다.
** 2단계: 맨 위(최댓값)를 힙의 맨 끝과 바꾸고, 힙 크기를 하나 줄여 다시 sift_down 한다.
** 배열 뒤쪽부터 큰 값이 차곡차곡 쌓이며, 추가 공간 없이 제자리에서 정렬된다.
** arr 는 head 를 거치지 않은 data 배열이므로, 여기서의 번호는 전부 idx 다.
*/
static void	heap_sort(int *arr, int size)
{
	int	idx;

	idx = size / 2 - 1;
	while (idx >= 0)
	{
		sift_down(arr, size, idx);
		--idx;
	}
	idx = size - 1;
	while (idx > 0)
	{
		swap_int(&arr[0], &arr[idx]);
		sift_down(arr, idx, 0);
		--idx;
	}
}

/*
** 정렬된 arr 에서 value 의 위치를 찾는다. 매번 탐색 범위를 절반으로 줄인다.
** arr 는 시작 위치, size 는 거기서부터 탐색할 칸 수, value 는 찾을 값이다.
** 중복이 없고 value 는 반드시 arr 안에 있으므로, 찾은 칸 번호가 곧 순위다.
** low, high, mid 는 모두 idx(배열 칸 번호) 종류이며, 탐색 범위에서의 역할을 이름으로 나타냈다.
** mid 를 (low + high) / 2 가 아니라 low + (high - low) / 2 로 구하는 것은
** 두 수를 더하는 과정의 부호 있는 정수 오버플로를 피하기 위한 관용구다.
** 매개변수들 뜻: (arr시작위치, size탐색범위, value타겟)
*/
static int	binary_search(int *arr, int size, int value)
{
	int	low;
	int	high;
	int	mid;

	low = 0;
	high = size - 1;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (arr[mid] == value)
		{
			return (mid);
		}
		if (arr[mid] < value)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return (-1);
}

/*
** 1. a 의 값들을 비어 있는 b 의 저장 공간에 복사한다. (추가 malloc 없음)
**    b->data[position] 은 a 의 position 번째 값을 b 의 같은 번호 칸(idx)에 두는 의도된 대응이다.
**    b 는 스택으로 쓰지 않으므로 stack_set 을 거치지 않고 data 에 직접 쓴다.
** 2. 그 복사본을 힙 정렬한다.
** 3. a 의 각 값을 정렬된 복사본에서 이진 탐색하여, 찾은 칸 번호(= 순위)로 덮어쓴다.
** 3단계는 정렬된 b 만 읽으므로 a 를 순서대로 덮어써도 이후 계산에 영향이 없다.
** b 의 size 는 0 인 채로 두므로, 탐색 범위로 b->size 가 아니라 a->size 를 넘긴다.
*/
void	compress_ranks(t_stack *a, t_stack *b)
{
	int	position;
	int	rank;

	position = 0;
	while (position < a->size)
	{
		b->data[position] = stack_get(a, position);
		++position;
	}
	heap_sort(b->data, a->size);
	position = 0;
	while (position < a->size)
	{
		rank = binary_search(b->data, a->size, stack_get(a, position));
		stack_set(a, position, rank);
		++position;
	}
}
