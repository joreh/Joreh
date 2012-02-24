LexicalAnalyzer:
	bison --defines=ConfigParser.y.h --locations -o ConfigParser.y.c ConfigParser.y
	flex -oConfigParser.yy.c ConfigParser.lex
	g++ -o ConfigParser ConfigParser.yy.c ConfigParser.y.c ../Utilities/CString.cpp ../Utilities/SwarmException.cpp Config.cpp

clean:
	rm -fr ConfigParser
	rm -fr ConfigParser.yy.c
	rm -fr ConfigParser.y.h ConfigParser.y.c
