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
	@for file in *_decompressed.txt; do \
		base=$$(basename $$file _decompressed.txt).txt; \
		if [ -f $$base.txt ]; then \
			HASH1=$$(sha256sum $$base| awk '{print $$1}'); \
			HASH2=$$(sha256sum $$file | awk '{print $$1}'); \
			if [ "$$HASH1" = "$$HASH2" ]; then echo "[$$base] Test passed"; else echo "[$$base] Test failed"; fi; \
		else \
			echo "No compressed files exist"; \
		fi; \
	done