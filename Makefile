BUILD_DIR := bin
OBJ_DIR := obj

LIBS := glfw3
ASSEMBLY := solaris
COMPILER_FLAGS := -g -MD `pkg-config -cflags $(LIBS)`
INCLUDE_FLAGS := -I./src -I./deps/glad/include -I./deps/objloader/
LINKER_FLAGS := -g `pkg-config -libs $(LIBS)` -Lbin -lglad -lm
DEFINES := -D_DEBUG

SRC_FILES := $(shell find src -name *.c)
DIRECTORIES := $(shell find src -type d)
OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)/%.o)

all: scaffold bin/libglad.a compile link

bin/libglad.a:
	$(MAKE) -C deps/glad/

.PHONY: scaffold
scaffold:
	@echo Scaffolding folder structure
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(DIRECTORIES))
	@mkdir -p $(BUILD_DIR)
	@echo Done

.PHONY: link
link: scaffold $(OBJ_FILES)
	@echo Linking $(ASSEMBLY)
	@clang $(OBJ_FILES) -o $(BUILD_DIR)/$(ASSEMBLY) $(LINKER_FLAGS)

.PHONY: compile
compile:
	@echo Compiling...

-include $(OBJ_FILES:.o=.d)
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJ_DIR)

$(OBJ_DIR)/%.c.o: %.c
	@echo $<...
	@clang $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS)

-include $(OBJ_FILES:.o=.d)
