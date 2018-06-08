LLVM_CONFIG = /usr/bin/llvm-config-6.0

NO_WARNING =  -Wno-return-type \
	-Wno-c++11-compat-deprecated-writable-strings \
	-Wno-deprecated-register \
	-Wno-switch 

LEX = flex
YACC = bison
CC = g++
CXXFLAGS = `$(LLVM_CONFIG) --cppflags` -std=c++11 $(NO_WARNING)
LDFLAGS = `$(LLVM_CONFIG) --ldflags`
LIBS = `$(LLVM_CONFIG) --libs --system-libs`

OBJS = token.o parser.o main.o AbstractTree.o CodeGenContext.o

all: exec
	$(CC) -o pascal $(OBJS) $(LDFLAGS) $(LIBS)

lex: pascal.l
	$(LEX) -o token.cpp pascal.l 
	$(CC) $(CXXFLAGS) -c token.cpp

yacc: pascal.y
	$(YACC) -y -d pascal.y -o parser.cpp
	$(CC) $(CXXFLAGS) -c parser.cpp

exec: lex yacc main.cpp AbstractTree.cpp CodeGenContext.cpp
	$(CC) $(CXXFLAGS) -c main.cpp AbstractTree.cpp CodeGenContext.cpp

clean:
	rm $(OBJS) token.cpp token.hpp parser.cpp 

