

all: serial pipe pthreads mmap


serial: main_serial.c
	gcc $^ -lc -o $@

pthreads: main_pthreads.c
	gcc $^ -lc -o $@

pipe: main_pipe.c
	gcc $^ -lc -o $@

mmap: main_mmap.c
	gcc $^ -lc -o $@
	