
CXX = gcc
APP_NAME = shell.elf
COMPILE_FLAGS = -O3 
SRC_FILES = src/lexer/*.c \
			src/lexer/token/*.c \
			src/command_parser/*.c  \
			src/command_parser/command/*.c \
			src/reader/*.c \
			src/main/*.c \
			src/executor/*.c \
			src/process_parser/process/*.c \
			src/process_parser/*.c \
			src/Application/*.c \
			src/Navigation/*.c
			



build:
	$(CXX) $(COMPILE_FLAGS) $(SRC_FILES) -o $(APP_NAME)
build_run:	build
	./shell.elf

debug:	build 
	gdb ./shell.elf

memory-check: build
	valgrind --show-leak-kinds=all --leak-check=full ./shell.elf  

clean:
	rm shell.elf