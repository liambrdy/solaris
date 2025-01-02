BUILD_DIR := ../../bin
OBJ_DIR := ../../obj

ASSEMBLY := glad
COMPILER_FLAGS := -O2
INCLUDE_FLAGS := -Iinclude
DEFINES := -D_DEBUG

SRC_FILES := $(shell find src -name *.c)
DIRECTORIES := $(shell find src -type d)
OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)/%.o)

all: scaffold compile link

.PHONY: scaffold
scaffold:
	@echo Scaffolding folder structure
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(DIRECTORIES))
	@mkdir -p $(BUILD_DIR)
	@echo Done

.PHONY: link
link: scaffold $(OBJ_FILES)
	@echo Linking $(ASSEMBLY)
	@ar rcs $(BUILD_DIR)/lib$(ASSEMBLY).a $(OBJ_FILES)

.PHONY: compile
compile:
	@echo Compiling...

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJ_DIR)

$(OBJ_DIR)/%.c.o: %.c
	@echo $<...
	@clang $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS)