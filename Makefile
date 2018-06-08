LLVM_CONFIG = /usr/bin/llvm-config-6.0

NO_WARNING =  -Wno-return-type \
	-Wno-c++11-compat-deprecated-writable-strings \
	-Wno-deprecated-register \
	-Wno-switch 

LEX = flex
YACC = bison
CC = clang++-6.0
CXXFLAGS = `$(LLVM_CONFIG) --cppflags` -std=c++11 $(NO_WARNING)
LDFLAGS = `$(LLVM_CONFIG) --ldflags`
LIBS = `$(LLVM_CONFIG) --libs --system-libs`

OBJS = AbstractTree.o CodeGenContext.o token.o parser.o main.o

all: exec
	$(CC) -o pascal $(OBJS) $(LDFLAGS) $(LIBS)

lex: pascal.l
	$(LEX) -o token.cpp pascal.l 
lex_compile: lex
	$(CC) $(CXXFLAGS) -c token.cpp

yacc: pascal.y
	$(YACC) -d pascal.y -o parser.cpp
yacc_compile: yacc
	$(CC) $(CXXFLAGS) -c parser.cpp

exec: lex_compile yacc_compile main.cpp AbstractTree.cpp CodeGenContext.cpp
	$(CC) $(CXXFLAGS) -c main.cpp AbstractTree.cpp CodeGenContext.cpp

clean:
	rm $(OBJS) token.cpp token.hpp parser.cpp parser.hpp

