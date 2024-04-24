CFLAGS= -std=c17 -g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
COMMON_LIBS=-ldl $(OPTLIBS) -lm -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -L./lib -llcthw -lbsd
LDLIBS=$(COMMON_LIBS) -pthread -L./build -lGrafx
PREFIX?=/urs/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

IMPL_TEST_SRC=tests/impl_test.c
IMPL_TEST=tests/impl_test

TARGET=build/libGrafx.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The target build
all: $(TARGET) $(SO_TARGET) tests impl_test

dev: CFLAGS= -std=c17 -g -O0 -fno-inline -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC 
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The unit tests
.PHONY: tests
tests: LDLIBS = $(TARGET) $(COMMON_LIBS)
tests: $(TESTS)
	sh ./tests/runtests.sh

#impl_test: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
impl_test: LDLIBS = $(TARGET) $(COMMON_LIBS)
impl_test: $(IMPL_TEST)

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`
	rm -f tests/impl_test

# The install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true