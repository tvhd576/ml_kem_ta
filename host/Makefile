
CC = $(CROSS_COMPILE)gcc

CFLAGS += -Wall -Wextra -O2
CFLAGS += -I../ta/include
CFLAGS += -I$(TEEC_EXPORT)/include

LDFLAGS += -L$(TEEC_EXPORT)/lib
LDLIBS += -lteec

TARGET = mlkem_client

.PHONY: all clean

all: $(TARGET)

$(TARGET): main.c ../ta/include/mlkem_bench_ta.h
	$(CC) $(CFLAGS) main.c $(LDFLAGS) $(LDLIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

