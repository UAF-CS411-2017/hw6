CPP=g++
CPPFLAGS=--std=c++17

build:
	read -p "Username: " USERNAME; \
	mkdir "test/$$USERNAME" -p; \
	cp solutions/$$USERNAME/huffcode.* test/$$USERNAME/; \
	cp huffcode_test.cpp test/$$USERNAME/; \
	clear; \
	$(CPP) $(CPPFLAGS) test/$$USERNAME/huffcode_test.cpp test/$$USERNAME/huffcode.cpp -o test/$$USERNAME/build; \
	test/$$USERNAME/build;

clean:
	rm -Rf test
	clear

test: clean build	
