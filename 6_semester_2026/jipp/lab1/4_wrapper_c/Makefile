CC = clang
CFLAGS = -Wall -Wextra -std=c23 -O2 -I../3_libjpp_rust/include

LIB_STATIC = ../3_libjpp_rust/target/release/libjpp.a

SYSLIBS = -lpthread -ldl -lm

rust_static: rust_static.c
	$(CC) $(CFLAGS) rust_static.c $(LIB_STATIC) -o rust_static $(SYSLIBS)

clean:
	rm -f rust_static