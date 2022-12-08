CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %, %.o, $(PROGS))
all: $(PROGS)
cyoa-step4: cyoa-step4.cpp Story.o Page.o util.o
	g++ -o cyoa-step4 -ggdb3 -Wall -Werror -pedantic -std=gnu++98 cyoa-step4.cpp util.cpp

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

Story.o:Story.hpp
Page.o:Page.hpp
util.o:util.hpp
