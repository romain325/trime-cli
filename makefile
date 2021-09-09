CC=gcc

CFLAGS= -Wall -lcurl -g -I ./

SRC=./

OBJ=$(SRC)main.o \
    $(SRC)router.o \
    $(SRC)cJSON.o \
    $(SRC)act.o \
    $(SRC)tracker.o \
    $(SRC)sync.o \
    $(SRC)utils.o 

out : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(SRC)%.o: private/$(SRC)%.c public/$(SRC)%.h
	$(CC) $(CFLAGS) -c $< -o $@

all: out

clean:
	rm -rf $(SRC)*.o out
	clear
