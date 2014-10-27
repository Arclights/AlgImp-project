# for power.ludat.lth.se
# CFLAGS	= -m64 -O3 -g -Wall -Wextra -Werror -std=c99 -mcpu=970 -mtune=970 -maltivec

# the following works on any machine
CFLAGS	= -O3 -g -Wall -Wextra -Werror -std=c99
#CFLAGS	= -O3 -g -Wall -Wextra -Werror -pg -fprofile-arcs -ftest-coverage -std=c99


CC	= gcc
OUT	= fm
OBJS	= main.o matrixhandler2.o vectorhandler2.o fix_p.o arena3.o TomKva_v4.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT)
	./fm
	size TomKva_v4.o

clean:
	rm -f $(OUT) $(OBJS)
