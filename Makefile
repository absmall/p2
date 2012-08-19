.PHONY:clean

p2: main.o p2.o
	g++ $(CFLAGS) -o $@ $^

%.o:%.cc
	g++ -c $(CFLAGS) -o $@ $<
clean:
	rm p2 *.o
