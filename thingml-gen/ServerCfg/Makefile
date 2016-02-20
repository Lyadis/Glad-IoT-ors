CC = cc
LIBS = -lpthread -l mosquitto -l websockets -l ssl -l crypto -l z
CFLAGS = -O2 -w
SRCS = ClockLinux.c Server.c ServerCfg_cfg.c runtime.c
OBJS = ClockLinux.o Server.o ServerCfg_cfg.o runtime.o

all : ServerCfg

.c.o :
	${CC} ${CFLAGS} -c $< 

ServerCfg : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) -lm

clean:
	rm -f *.o *~ ServerCfg
