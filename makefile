program : backup cleanup main.o main.h consumer.o consumer.h producer.o producer.h
	gcc -o program main.o consumer.o producer.o

main.o : main.c main.h
	gcc -c main.c

consumer.o : consumer.c consumer.h
	gcc -c consumer.c

producer.o : producer.c producer.h
	gcc -c producer.c

backup : 
	cp main.c consumer.c producer.c main.h consumer.h producer.h makefile ./backup

cleanup : 
	rm -f main.o consumer.o producer.o

debug : 
	gcc -o -g -pg program main.o consumer.o producer.o