CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %, %.o, $(PROGS))
all: $(PROGS)
cyoa-step1: cyoa-step1.cpp Story.o Page.o util.o
	g++ -o cyoa-step1 -ggdb3 -Wall -Werror -pedantic -std=gnu++98 cyoa-step1.cpp util.cpp
cyoa-step2: cyoa-step2.cpp Story.o Page.o util.o
	g++ -o cyoa-step2 -ggdb3 -Wall -Werror -pedantic -std=gnu++98 cyoa-step2.cpp util.cpp
cyoa-step3: cyoa-step3.cpp Story.o Page.o util.o
	g++ -o cyoa-step3 -ggdb3 -Wall -Werror -pedantic -std=gnu++98 cyoa-step3.cpp util.cpp
cyoa-step4: cyoa-step4.cpp Story.o Page.o util.o
	g++ -o cyoa-step4 -ggdb3 -Wall -Werror -pedantic -std=gnu++98 cyoa-step4.cpp util.cpp

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

Story.o:Story.hpp
Page.o:Page.hpp
util.o:util.hpp
