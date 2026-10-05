NAME        = push_swap
NAME_ASAN   = push_swap_asan

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
ASAN_FLAGS  = -fsanitize=address -g -fno-omit-frame-pointer

SRCS        = main.c \
              error.c \
              parse.c \
              args.c \
              stack.c \
              access.c \
              output.c \
              ops_swap.c \
              ops_push.c \
              ops_rotate.c \
              ops_rev_rotate.c \
              sort_utils.c \
              ranks.c \
              sort_small.c \
              sort_medium.c \
              push_chunks.c \
              cost.c \
              sort.c \
              insert.c \
              sort_big.c

OBJ_DIR      = obj
OBJS         = $(SRCS:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR_ASAN = obj_asan
OBJS_ASAN    = $(SRCS:%.c=$(OBJ_DIR_ASAN)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c push_swap.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

asan: $(NAME_ASAN)

$(NAME_ASAN): $(OBJS_ASAN)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(OBJS_ASAN) -o $(NAME_ASAN)

$(OBJ_DIR_ASAN)/%.o: %.c push_swap.h
	@mkdir -p $(OBJ_DIR_ASAN)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OBJ_DIR_ASAN)

fclean: clean
	rm -f $(NAME) $(NAME_ASAN)
	rm -rf $(NAME_ASAN).dSYM

re:
	$(MAKE) fclean
	$(MAKE) all
# <이렇게 작성한 이유>
#  병렬 빌드(make -j)에서의 순서 보장 문제때문. GNU Make는 -j 옵션으로 병렬 실행을 켜면,
# fclean과 all을 의존성으로 나란히 적어놔도 완료 순서를 보장하지 않음.
#  옵션 전파는 $(MAKE)를 쓸 때 따라오는 사실이지만,
# 이 구조를 쓰는 핵심 동기는 병렬 빌드에서도 fclean이 반드시 all보다 먼저 끝나도록 순서를 강제하기 위함임.

re_asan:
	$(MAKE) fclean
	$(MAKE) asan
# re와 같은 이유로 fclean과 asan을 별도의 $(MAKE) 호출로 분리함.

.PHONY: all clean fclean re asan re_asan