CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %, %.o, $(PROGS))
all: $(PROGS)
cyoa-step%: cyoa-step%.o util.o Story.hpp Page.hpp
	g++ -o $@ $^
%.o: %.cpp util.cpp
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

util.o: util.hpp
