# for power.ludat.lth.se
# CFLAGS	= -m64 -O3 -g -Wall -Wextra -Werror -std=c99 -mcpu=970 -mtune=970 -maltivec

# the following works on any machine
# CFLAGS	= -O3 -g -Wall -Wextra -Werror -std=c99
CFLAGS	= -O3 -g -Wall -Wextra -Werror -pg -fprofile-arcs -ftest-coverage -std=c99


CC	= gcc
OUT	= fm
OBJS	= main.o matrixhandler.o vectorhandler.o fix_p.o arena.o TomKva_v5.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT)
	./fm
	size TomKva_v1.o

clean:
	rm -f $(OUT) $(OBJS)
