kurrent_os := $(shell sh -c 'uname -s 2>/dev/null || echo not')

.PHONY: all clean rebuild check test_model tests check fix open tests_open uninstall

all: install start

clean:
	rm -rf ./BUILD
	rm -rf ./tests/BUILD

install: checkdir
	cd BUILD && cmake .. && make

uninstall:
	rm -rf ./BUILD

checkdir :
	@echo "checkdir"
	mkdir -p BUILD
	mkdir -p tests/BUILD

dvi:
ifeq ($(OS), Linux)
	open dvi.html
else
	firefox dvi.html
endif

start:
	./BUILD/bin/SmartCalc2

dist:
	tar -cf SmartCalc_v2.0.tar ./*

tests:
	cd tests && mkdir -p BUILD && cd BUILD && cmake .. && make && ctest && make make_coverage

tests_open:
ifeq ($(OS), Linux)
	open ./tests/BUILD/coverage_report/index.html
else
	firefox ./tests/BUILD/coverage_report/index.html
endif

check:
	@echo "processing ..."
	./clang_custom.sh n
	echo "~~~ $@ DONE ~~~"

fix:
	echo "processing ..."
	./clang_custom.sh n
	echo "~~~ $@ DONE ~~~"
