CC = gcc
CFLAGS = -Wall -Wextra

OUTPUT_DIR = _output

main: src/main.c src/hash_table.c
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/hash_table $^

.PHONY: clean

clean:
	rm -f $(OUTPUT_DIR)/hash_table