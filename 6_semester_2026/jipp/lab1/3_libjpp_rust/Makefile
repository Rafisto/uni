LIB_NAME = libjpp
TARGET_DIR = target/release

LIB_STATIC = $(TARGET_DIR)/$(LIB_NAME).a
LIB_DYNAMIC = $(TARGET_DIR)/$(LIB_NAME).so

SOURCES = libjpp.rs

CARGO = cargo
CARGO_FLAGS = --release

.PHONY: all clean test build-info

all: $(LIB_STATIC) $(LIB_DYNAMIC)

$(LIB_STATIC) $(LIB_DYNAMIC): $(SOURCES) Cargo.toml
	@echo "Building Rust library in release mode..."
	$(CARGO) build $(CARGO_FLAGS)

build-info: all
	@echo "--- Build Artifacts ---"
	@ls -lh $(LIB_STATIC) $(LIB_DYNAMIC)

clean:
	$(CARGO) clean
	@echo "Cleaned Rust target directory."