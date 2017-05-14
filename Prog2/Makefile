OBJS=Prog2.o

CFLAGS= -std=c++11

Prog2: $(OBJS)
	g++ -g -o $@ $(OBJS) $(CFLAGS)

.cpp.o:
	g++ -g -c $< $(CFLAGS)
clean:
	rm -f *.o *- Prog2 tmp.data

