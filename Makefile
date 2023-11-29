CC = gcc
CFLAGS = -Wall -Wextra

OUTPUT_DIR = _output

main: src/main.c src/hash_table.c
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/hash_table $^

test: tests/test_hash_table.c src/hash_table.c
	$(CC) -o $(OUTPUT_DIR)/test_hash_table ./tests/test_hash_table.c ./src/hash_table.c -lcheck -lm -lpthread -lrt -lsubunit

.PHONY: clean

clean:
	rm -f $(OUTPUT_DIR)/main $(OUTPUT_DIR)/test_hash_table