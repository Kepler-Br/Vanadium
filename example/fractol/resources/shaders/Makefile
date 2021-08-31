COLOR_NONE = \e[0m
COLOR_WHITE = \e[1;37m
COLOR_BLUE = \e[1;34m
COLOR_GREEN = \e[1;32m
COLOR_PURPLE = \e[1;35m

ifndef SHADERC
	SHADERC = shaderc
endif

SRC_DIR = .
OUT_DIR = ./compiled

SPIRV_OUT = $(OUT_DIR)/spirv
GLSL_OUT = $(OUT_DIR)/glsl
ESSL_OUT = $(OUT_DIR)/essl

FRAGMENT_SRCS = $(SRC_DIR)/fs_mandelbulb.sc
VERTEX_SRCS = $(SRC_DIR)/vs_texturedQuad.sc

FRAGMENT_SPIRV_BINS = $(patsubst $(SRC_DIR)/%,$(SPIRV_OUT)/%,$(FRAGMENT_SRCS:.sc=.bin))
FRAGMENT_GLSL_BINS = $(patsubst $(SRC_DIR)/%,$(GLSL_OUT)/%,$(FRAGMENT_SRCS:.sc=.bin))
FRAGMENT_ESSL_BINS = $(patsubst $(SRC_DIR)/%,$(ESSL_OUT)/%,$(FRAGMENT_SRCS:.sc=.bin))

VERTEX_SPIRV_BINS = $(patsubst $(SRC_DIR)/%,$(SPIRV_OUT)/%,$(VERTEX_SRCS:.sc=.bin))
VERTEX_GLSL_BINS = $(patsubst $(SRC_DIR)/%,$(GLSL_OUT)/%,$(VERTEX_SRCS:.sc=.bin))
VERTEX_ESSL_BINS = $(patsubst $(SRC_DIR)/%,$(ESSL_OUT)/%,$(VERTEX_SRCS:.sc=.bin))

INCLUDES = -i "include"

all: $(FRAGMENT_SPIRV_BINS) $(FRAGMENT_GLSL_BINS) $(FRAGMENT_ESSL_BINS) $(VERTEX_SPIRV_BINS) $(VERTEX_GLSL_BINS) $(VERTEX_ESSL_BINS)

re: clean all

$(SPIRV_OUT)/fs_%.bin: $(SRC_DIR)/fs_%.sc
	@mkdir -p $(SPIRV_OUT)
	@printf "$(COLOR_GREEN)Compiling $(COLOR_PURPLE)$<$(COLOR_GREEN) to $(COLOR_PURPLE)$@$(COLOR_GREEN)...$(COLOR_NONE)\n"
	@$(SHADERC) --type f --varyingdef $(SRC_DIR)/varying.def.sc $(INCLUDES) -f $< -o $@ --profile spirv

$(GLSL_OUT)/fs_%.bin: $(SRC_DIR)/fs_%.sc
	@mkdir -p $(GLSL_OUT)
	@printf "$(COLOR_GREEN)Compiling $(COLOR_PURPLE)$<$(COLOR_GREEN) to $(COLOR_PURPLE)$@$(COLOR_GREEN)...$(COLOR_NONE)\n"
	@$(SHADERC) --type f --varyingdef $(SRC_DIR)/varying.def.sc $(INCLUDES) -f $< -o $@ --profile 440

$(ESSL_OUT)/fs_%.bin: $(SRC_DIR)/fs_%.sc
	@mkdir -p $(ESSL_OUT)
	@printf "$(COLOR_GREEN)Compiling $(COLOR_PURPLE)$<$(COLOR_GREEN) to $(COLOR_PURPLE)$@$(COLOR_GREEN)...$(COLOR_NONE)\n"
	@$(SHADERC) --type f --varyingdef $(SRC_DIR)/varying.def.sc $(INCLUDES) -f $< -o $@ --profile 300_es

$(SPIRV_OUT)/vs_%.bin: $(SRC_DIR)/vs_%.sc
	@mkdir -p $(SPIRV_OUT)
	@printf "$(COLOR_GREEN)Compiling $(COLOR_PURPLE)$<$(COLOR_GREEN) to $(COLOR_PURPLE)$@$(COLOR_GREEN)...$(COLOR_NONE)\n"
	@$(SHADERC) --type v --varyingdef $(SRC_DIR)/varying.def.sc $(INCLUDES) -f $< -o $@ --profile spirv

$(GLSL_OUT)/vs_%.bin: $(SRC_DIR)/vs_%.sc
	@mkdir -p $(GLSL_OUT)
	@printf "$(COLOR_GREEN)Compiling $(COLOR_PURPLE)$<$(COLOR_GREEN) to $(COLOR_PURPLE)$@$(COLOR_GREEN)...$(COLOR_NONE)\n"
	@$(SHADERC) --type v --varyingdef $(SRC_DIR)/varying.def.sc $(INCLUDES) -f $< -o $@ --profile 440

$(ESSL_OUT)/vs_%.bin: $(SRC_DIR)/vs_%.sc
	@mkdir -p $(ESSL_OUT)
	@printf "$(COLOR_GREEN)Compiling $(COLOR_PURPLE)$<$(COLOR_GREEN) to $(COLOR_PURPLE)$@$(COLOR_GREEN)...$(COLOR_NONE)\n"
	@$(SHADERC) --type v --varyingdef $(SRC_DIR)/varying.def.sc $(INCLUDES) -f $< -o $@ --profile 300_es

clean:
	@/bin/rm -rf $(SPIRV_OUT)/*.bin
	@/bin/rm -rf $(GLSL_OUT)/*.bin
	@/bin/rm -rf $(ESSL_OUT)/*.bin
