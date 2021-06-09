CC		= gcc
CFLAGS		= -I $(INC_DIR)

INC_DIR 	= include
SRC_DIR		= src
OBJ_DIR 	= obj

_DEPS		= mash.h
DEPS		= $(patsubst %,$(INC_DIR)/%,$(_DEPS))

_OBJ		= main.o util.o
OBJ		= $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

all: mash clean

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

mash: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(OBJ_DIR)/*.o

.PHONY: clean
