all: NetMap

NetMap: main.o Roteador.o Terminal.o
	gcc -o NetMap main.o Roteador.o Terminal.o

main.o: main.c
	gcc -c main.c

Roteador.o: Roteador.c
	gcc -c Roteador.c

Terminal.o: Terminal.c
	gcc -c Terminal.c

clean:
	rm -rf *.o

rmproper:
	rm -tf NetMap

run: NetMap
	./NetMap entrada.txt
