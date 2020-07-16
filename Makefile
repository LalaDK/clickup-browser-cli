CC=gcc
OBJFILES=main.o http_helper.o tasks.o projects.o task_fetcher.o project_fetcher.o gui.o
TARGET=app
LDFLAGS=-l json-c -l curl -l ncurses #Library dependencies
CFLAGS=-I. -Wall #-Wall: gcc -Wall enables all compiler's warning messages. This option should always be used, in order to generate better code.

all: $(TARGET)

$(TARGET): $(OBJFILES)
	mv *.o obj/ && \
	cd obj/ && \
	echo $(PWD) && \
	$(CC) $(CFLAGS) -o ../bin/$(TARGET) $(OBJFILES) $(LDFLAGS)

main.o:
	gcc src/main.c -c -o main.o

http_helper.o:
	gcc src/http_helper.c -c -o http_helper.o

tasks.o:
	gcc src/tasks.c -c -o tasks.o

projects.o:
	gcc src/projects.c -c -o projects.o

task_fetcher.o:
	gcc src/task_fetcher.c -c -o task_fetcher.o

project_fetcher.o: projects.o
	gcc src/project_fetcher.c -c -o project_fetcher.o

gui.o:
	gcc src/gui.c -c -o gui.o

clean:
	cd obj/ && rm -f $(OBJFILES)
