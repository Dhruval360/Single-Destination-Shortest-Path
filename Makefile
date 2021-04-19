compiler=gcc

Dijkstra: Client.o Implementation.o PES1UG19CS313_H.h
	${compiler} -o Dijkstra Client.o Implementation.o

Client.o: PES1UG19CS313_C.c PES1UG19CS313_H.h
	${compiler} -c PES1UG19CS313_C.c -o Client.o

Implementation.o: PES1UG19CS313_F.c PES1UG19CS313_H.h
	${compiler} -c PES1UG19CS313_F.c -o Implementation.o

clean: 
	rm -f Client.o Implementation.o Dijkstra 

test: Dijkstra
	./TestScript.sh
