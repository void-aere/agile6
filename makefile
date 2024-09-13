# Add all new symbol names to this list!
SYMBOLS = helpers mainmenu

GPPFLAGS = -std=c++20 -Wall -Werror -Wpedantic

# Make a link in the root directory to the compiled executable
default: build/output
	ln -sf build/output output

# Assemble an executble from the compiled objects
build/output: build/main.o $(addprefix build/, $(SYMBOLS:=.o))
	g++ ${GPPFLAGS} build/*.o -o build/output

# Compile the main function separately from other modules
build/main.o: src/main.cpp
	g++ ${GPPFLAGS} -c src/main.cpp -o build/main.o

# Magic to compile each of the modules specified in $SYMBOLS and put objects in build/
build/%.o: src/%.cpp src/%.hpp
	g++ ${GPPFLAGS} -c src/$*.cpp -o $@

clean:
	rm -f build/*
	rm -f output
