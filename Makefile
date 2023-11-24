# directory for source files
SRC_DIR = src
INC_DIR = inc
OUT_DIR = out

# compiller and flags
CC = gcc
CFLAGS = -Wall -I$(INC_DIR) -std=c99

# font and object files
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SOURCES))

# executable name
EXECUTABLE = $(OUT_DIR)/main

# zip file name
ZIP_FILE = project.zip

# file list to zip
ZIP_FILES := $(SOURCES) $(wildcard $(INC_DIR)/*.h) Makefile

# compile rules
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# links
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# create output directory
$(shell mkdir -p $(OUT_DIR))

# temporary files cleaner
clean:
	rm -rf $(OUT_DIR) $(EXECUTABLE) $(ZIP_FILE)

# execute program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# zip creation
zip:
	zip $(ZIP_FILE) $(ZIP_FILES)

# compile
all: $(EXECUTABLE) 
