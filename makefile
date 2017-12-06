program : Consumer.o Producer.o Main.o 
	gcc -o program Consumer.o Producer.o Main.o;
	chmod 700 program

Main.o : Main.c
	gcc -c Main.c

Consumer.o : Consumer.c
	gcc -c Consumer.c

Producer.o : Producer.c
	gcc -c Producer.c