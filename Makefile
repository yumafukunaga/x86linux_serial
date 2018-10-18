PROG := serial
SRCS := main.c init.c
OBJS := $(SRCS:%.c=%.o)
DEPS := $(SRCS:%.c=%.d)

CC := gcc

all: $(PROG)

-include $(DEPS)

$(PROG): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $<

clean:
	rm -f $(PROG) $(OBJS) $(DEPS)

