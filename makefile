CCMD = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

SOURCE_DIR = src
UTILITIES_DIR = src/utilities
FEATURES_DIR = src/features
HELPERS_DIR = src/helpers
SYSTEM_DIR = src/system

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)\
		  $(wildcard $(UTILITIES_DIR)/*.c)\
		  $(wildcard $(FEATURES_DIR)/*.c)\
		  $(wildcard $(HELPERS_DIR)/*.c)\
		  $(wildcard $(SYSTEM_DIR)/*.c)

EXECUTABLE = ATM_MS.exe

run: build
	@echo "Running the executable..."
	./$(EXECUTABLE)

build: $(SOURCES) clean_terminal
	@echo "Building the project executable..."
	$(CCMD) $(SOURCES) -o $(EXECUTABLE) $(CFLAGS)

clean_terminal:
	clear
