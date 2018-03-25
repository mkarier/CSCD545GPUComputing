word: thread.o serial.o

thread.o: 
	gcc -o thread -pthread thread_wordCount.c LinkedList.c parser.c main.c

serial.o:
	gcc -o serial LinkedList.c parser.c serial_wordCount.c main.c
