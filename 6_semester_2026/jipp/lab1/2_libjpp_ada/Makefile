CC = gnatmake
CFLAGS = -O2 -fPIC
ADAFLAGS = -cargs $(CFLAGS)

LIB_NAME = libjpp
LIB_STATIC = $(LIB_NAME).a
LIB_DYNAMIC = $(LIB_NAME).so

SRC = libjpp.adb
OBJ = libjpp.o
ALI = libjpp.ali

.PHONY: all clean

all: $(LIB_STATIC) $(LIB_DYNAMIC)

$(LIB_STATIC): $(OBJ)
	ar rcs $@ $^

$(LIB_DYNAMIC): $(OBJ)
	gnatgcc -shared -o $@ $^

$(OBJ): $(SRC)
	$(CC) -c $(SRC) $(ADAFLAGS)

clean:
	rm -f *.o *.ali $(LIB_STATIC) $(LIB_DYNAMIC)