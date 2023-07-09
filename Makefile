_SDL=SDL
_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -D $(_SDL) -I./include
LDFLAGS = -lm -l$(_SDL)

ifeq ($(OS),Windows_NT)
    USRBIN=C:/msys64/usr/bin
else
    USRBIN=/usr/bin
endif

.PHONY: clean doc check-syntax compile-all launch-tests tests

dir:
	mkdir -p tests/results

# rule to generate the doxygen documentation
doc:
	doxygen conf/doxygen.conf

# rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- rm -f tests/results/*
	- $(USRBIN)/find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

# compile rules
%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

# you should put all the .o files corresponding to your .c files as prerequisites of
# this rule (see examples)
# \ allows to go on the next line
check-syntax: example-main.o read-file-formatted.o read-file-text.o \
	write-fact.o test-dummy.o disc.o snow.o vector.o test-vector.o particle.o test-particle.o test-loader.o event.o test-event.o simulation-naive.o\
	clash-of-particles-naive.o heap.o test-correctness-heap.o test-complexity-heap.o test-complexity-1mop-heap.o\
	simulation-bh.o clash-of-particles-bh.o

# put all the rules to build your applications and tests here (see examples)
example-main: example-main.o
	$(CC) $(CFLACS) -o example-main example-main.o

example-string: example-string.o
	$(CC) $(CFLACS) -o example-string example-string.o

read-file-formatted: read-file-formatted.o
	$(CC) $(CFLACS) -o read-file-formatted read-file-formatted.o

read-file-text: read-file-text.o
	$(CC) $(CFLACS) -o read-file-text read-file-text.o

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o write-fact write-fact.o

clash-of-particles-naive: clash-of-particles-naive.o simulation-naive.o loader.o particle.o vector.o event.o disc.o
	$(CC) $(CFLACS) -o clash-of-particles-naive clash-of-particles-naive.o simulation-naive.o particle.o vector.o loader.o event.o disc.o $(LDFLAGS)

clash-of-particles-bh: clash-of-particles-bh.o simulation-bh.o loader.o particle.o vector.o event.o disc.o heap.o
	$(CC) $(CFLACS) -o clash-of-particles-bh clash-of-particles-bh.o simulation-bh.o particle.o vector.o loader.o event.o disc.o heap.o $(LDFLAGS)

test-dummy: test-dummy.o
	$(CC) $(CFLACS) -o test-dummy test-dummy.o

test-vector: test-vector.o vector.o
	$(CC) $(CFLACS) -o test-vector test-vector.o vector.o

test-loader: test-loader.o loader.o particle.o vector.o dir
	$(CC) $(CFLACS) -o test-loader test-loader.o loader.o particle.o vector.o $(LDFLAGS)

test-particle: test-particle.o loader.o particle.o vector.o dir
	$(CC) $(CFLACS) -o test-particle test-particle.o particle.o vector.o loader.o $(LDFLAGS)

test-event: test-event.o event.o particle.o vector.o dir
	$(CC) $(CFLACS) -o test-event test-event.o particle.o vector.o event.o $(LDFLAGS)

test-correctness-heap: test-correctness-heap.o heap.o particle.o vector.o event.o dir
	$(CC) $(CFLACS) -o test-correctness-heap test-correctness-heap.o particle.o vector.o heap.o event.o $(LDFLAGS)

test-complexity-heap: test-complexity-heap.o heap.o particle.o vector.o event.o dir
	$(CC) $(CFLACS) -o test-complexity-heap test-complexity-heap.o particle.o vector.o heap.o event.o $(LDFLAGS)

test-complexity-1mop-heap: test-complexity-1mop-heap.o heap.o particle.o vector.o event.o dir
	$(CC) $(CFLACS) -o test-complexity-1mop-heap test-complexity-1mop-heap.o particle.o vector.o heap.o event.o $(LDFLAGS)


# the snow app. Beware, for graphical applications, you MUST add $(LDFLAGS)!
snow: snow.o disc.o ./include/disc.h
	$(CC) $(CFLAGS) -o snow snow.o disc.o $(LDFLAGS)

# put all your applications and tests executables as prerequisite of this rule
# \ allows to go to the next line
compile-all: example-main read-file-formatted read-file-text \
	write-fact test-dummy snow clash-of-particles-naive test-loader test-particle test-event test-vector\
	test-correctness-heap test-complexity-heap test-complexity-1mop-heap clash-of-particles-bh

# add all your test executables in the following variable. You should respect
# the order given in the project text
# \ allows to go to the next line
ALL_TESTS = test-dummy test-vector test-loader test-particle test-event

launch-tests: $(ALL_TESTS)
	@set -e
	@./test-dummy 
	@./test-vector
	echo "* Starting test-loader tests..." ; ./test-loader -f data/two-particles-simple.txt > tests/results/test-loader-results.txt && $(USRBIN)/diff --strip-trailing-cr -q tests/results/test-loader-results.txt tests/cmp/test-loader.cmp && echo "  +-> OK!"
	@./test-particle data/test-particles.txt tests/cmp/test-particles.cmp
	@./test-event

# add all .c, .h and .txt files in repository
svn-add-all-files:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q
