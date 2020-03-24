# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  glfw_config = debug
  glad_config = debug
  imgui_config = debug
  freetype_config = debug
  Engine_config = debug
  Game_config = debug

else ifeq ($(config),release)
  glfw_config = release
  glad_config = release
  imgui_config = release
  freetype_config = release
  Engine_config = release
  Game_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := glfw glad imgui freetype Engine Game

.PHONY: all clean help $(PROJECTS) Dependencies

all: $(PROJECTS)

Dependencies: freetype glad glfw imgui

glfw:
ifneq (,$(glfw_config))
	@echo "==== Building glfw ($(glfw_config)) ===="
	@${MAKE} --no-print-directory -C ext/glfw -f Makefile config=$(glfw_config)
endif

glad:
ifneq (,$(glad_config))
	@echo "==== Building glad ($(glad_config)) ===="
	@${MAKE} --no-print-directory -C ext/glad -f Makefile config=$(glad_config)
endif

imgui:
ifneq (,$(imgui_config))
	@echo "==== Building imgui ($(imgui_config)) ===="
	@${MAKE} --no-print-directory -C ext/imgui -f Makefile config=$(imgui_config)
endif

freetype:
ifneq (,$(freetype_config))
	@echo "==== Building freetype ($(freetype_config)) ===="
	@${MAKE} --no-print-directory -C ext/freetype -f Makefile config=$(freetype_config)
endif

Engine: glad glfw imgui freetype
ifneq (,$(Engine_config))
	@echo "==== Building Engine ($(Engine_config)) ===="
	@${MAKE} --no-print-directory -C . -f Engine.make config=$(Engine_config)
endif

Game: glad glfw imgui freetype Engine
ifneq (,$(Game_config))
	@echo "==== Building Game ($(Game_config)) ===="
	@${MAKE} --no-print-directory -C Game -f Makefile config=$(Game_config)
endif

clean:
	@${MAKE} --no-print-directory -C ext/glfw -f Makefile clean
	@${MAKE} --no-print-directory -C ext/glad -f Makefile clean
	@${MAKE} --no-print-directory -C ext/imgui -f Makefile clean
	@${MAKE} --no-print-directory -C ext/freetype -f Makefile clean
	@${MAKE} --no-print-directory -C . -f Engine.make clean
	@${MAKE} --no-print-directory -C Game -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   glfw"
	@echo "   glad"
	@echo "   imgui"
	@echo "   freetype"
	@echo "   Engine"
	@echo "   Game"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"