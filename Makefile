# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Source files
SRCS = main.cpp utils.cpp zipper.cpp

# result files
RSLT = *_compressed.txt *_decompressed.txt

# Output executable
OUT = zipper_bin

all: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRCS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT) $(RSLT)

test:
	sha256sum file.txt *_decompressed.txt 