LIB_NAME = libjpp
TARGET_DIR = target/release

LIB_STATIC = $(TARGET_DIR)/$(LIB_NAME).a
LIB_DYNAMIC = $(TARGET_DIR)/$(LIB_NAME).so

SOURCES = libjpp.rs

CARGO = cargo
CARGO_FLAGS = --release

.PHONY: all clean test

all: $(LIB_STATIC) $(LIB_DYNAMIC)

$(LIB_STATIC) $(LIB_DYNAMIC): $(SOURCES) Cargo.toml
	$(CARGO) build $(CARGO_FLAGS)

clean:
	$(CARGO) clean