dev:
	@echo "Sahaja Nandyala\n200010032@iitdh.ac.in"

compiler: main.cpp microParser.ypp microLexer.l
	@bison -d -o microParser.cpp microParser.ypp
	@flex -o lex.yy.cpp microLexer.l
	@g++ lex.yy.cpp microParser.cpp main.cpp -o a.out

clean:
	@rm -f lex.yy.cpp microParser.cpp microParser.hpp
