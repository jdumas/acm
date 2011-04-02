CFILES := $(wildcard *.cpp)
EFILES := $(patsubst %.cpp, %, $(CFILES))

all : $(EFILES)

% : %.cpp
	g++ $^ -o $@ -O -ansi -Wall -lm -static

clean :
	@rm -vf $(EFILES) *~
