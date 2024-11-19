CFLAGS=-Wall -Werror

.PHONY: clean run-main run-interactive

run-interactive: interactive
	./interactive

interactive: interactive.c imageprocessing.c bmp.c
	gcc interactive.c imageprocessing.c bmp.c $(CFLAGS) -o interactive

clean:
	rm -f main interactive
