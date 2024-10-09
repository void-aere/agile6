# Add all new cpp-hpp combo names to this list!
SYMBOLS = dataHandler helpers mainmenu menu_create menu_edit menu_list menu_search accounts/bankAccount accounts/certificateOfDeposit accounts/checkingAccount accounts/highInterestChecking accounts/highInterestSavings accounts/noChargeChecking accounts/savingsAccount accounts/serviceChargeChecking

ENTRYPOINT = main

# Configure where things go
OUT_DIR = out
SRC_DIR = src
EXE = run-me

GPPFLAGS = -std=c++20 -Wall -Werror -Wpedantic -Isrc -iquote src/accounts

# Make a link in the root directory to the compiled EXE
default: ${OUT_DIR} ${OUT_DIR}/${EXE}
	@ln -sf ${OUT_DIR}/${EXE} ${EXE}
	$(info Done! Run the program with: ./${EXE})

# Create the output directory
${OUT_DIR}:
	mkdir ${OUT_DIR}
	mkdir ${OUT_DIR}/accounts

# Assemble an executble from the compiled objects
${OUT_DIR}/${EXE}: ${OUT_DIR}/${ENTRYPOINT}.o $(addprefix ${OUT_DIR}/, $(SYMBOLS:=.o))
	g++ ${GPPFLAGS} ${OUT_DIR}/*.o ${OUT_DIR}/accounts/*.o -o ${OUT_DIR}/${EXE}

# Compile the main function separately from other modules
${OUT_DIR}/${ENTRYPOINT}.o: ${SRC_DIR}/${ENTRYPOINT}.cpp
	g++ ${GPPFLAGS} -c ${SRC_DIR}/${ENTRYPOINT}.cpp -o ${OUT_DIR}/${ENTRYPOINT}.o

# Magic to compile each of the modules specified in $SYMBOLS and put objects in $OUT_DIR/
${OUT_DIR}/%.o: ${SRC_DIR}/%.cpp ${SRC_DIR}/%.hpp
	g++ ${GPPFLAGS} -c ${SRC_DIR}/$*.cpp -o $@

clean:
	rm -rf ${OUT_DIR}/*
	rm -f ${EXE}
