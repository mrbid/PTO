all:
	cc pto.c haxstring.c -Ofast -march=native -o pto
	cd assets && ../pto sample.ply && nasm -f elf64 sample.asm -o sample.o && cd ..
	cc main.c glad_gl.c assets/sample.o -I inc -Ofast -lglfw -lm -o plv

test:
	cc pto.c haxstring.c -o pto
	cd assets && ../pto sample.ply && nasm -f elf64 sample.asm -o sample.o && cd ..
	cc main.c glad_gl.c assets/sample.o -I inc -Ofast -lglfw -lm -o /tmp/plyviewer_test
	/tmp/plyviewer_test
	rm /tmp/plyviewer_test

clean:
	rm -f plv
	rm -f pto
