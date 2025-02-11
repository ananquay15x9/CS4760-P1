# Author: Tu Le
# Date: 2/8/2025
# CS4760 Lab 1


CC = gcc
CFLAGS = -Wall -g
OSS_TARGET = oss
USER_TARGET = user

OSS_OBJS = oss.o
USER_OBJS = user.o

all: $(OSS_TARGET) $(USER_TARGET)

$(OSS_TARGET): $(OSS_OBJS)
	$(CC) $(CFLAGS) -o $(OSS_TARGET) $(OSS_OBJS)

$(USER_TARGET): $(USER_OBJS)
	$(CC) $(CFLAGS) -o $(USER_TARGET) $(USER_OBJS)

oss.o: oss.c
	$(CC) $(CFLAGS) -c oss.c

user.o: user.c
	$(CC) $(CFLAGS) -c user.c

# Apply clean rule
clean:
	rm -f $(OSS_TARGET) $(USER_TARGET) *.o
