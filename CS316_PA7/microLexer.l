%{
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h> 
	#include <bits/stdc++.h>
	#include <vector>
	#include <iostream>
	using namespace std;
    #include "microParser.hpp"

    int line_number = 1;
%}
INTLITERAL [0-9]+
SPACE [\r\t ]
OPERATOR [:]|[+]|[-]|[*]|[/]|[=]|[!]|[<]|[>]|[(]|[)]|[,]|[;]
IDENTIFIER [a-zA-Z][a-zA-Z0-9]*

%%
"//".* {}

\n {line_number++;}

{SPACE}+ {}

{INTLITERAL} {

	yylval.int_value = atoi(yytext);
	return INTLITERAL;
}

[0-9]*['.'][0-9]+ {

yylval.float_value = atof(yytext);
return FLOATLITERAL;

}

\"(\\.|[^"\\])*\"  {

	yylval.string_value = new string(yytext);
	return STRINGLITERAL;
}

PROGRAM {return PROGRAM;}
BEGIN {return _BEGIN ;}
END {return END;}
FUNCTION {return FUNCTION;}
READ {return READ;}
WRITE {return WRITE;}
IF {return IF;}
ELSE {return ELSE;}
ENDIF {return ENDIF;}
WHILE {return WHILE;}
ENDWHILE {return ENDWHILE;}
BREAK {return BREAK;}
CONTINUE {return CONTINUE;}
RETURN {return RETURN;}
VOID {
yylval.s = new std::pair<std::string, int>;
(yylval.s)->first = string(yytext);
(yylval.s)->second = line_number;
return VOID;
}

INT {
yylval.s = new std::pair<std::string, int>;
(yylval.s)->first = string(yytext);
(yylval.s)->second = line_number;

return INT;}

STRING {return STRING;}

FLOAT {	
yylval.s = new std::pair<std::string, int>;
(yylval.s)->first = string(yytext);
(yylval.s)->second = line_number;

return FLOAT;}

{IDENTIFIER} {
	yylval.s = new std::pair<std::string, int>;
	(yylval.s)->first = string(yytext);
	(yylval.s)->second = line_number;
	return IDENTIFIER;
}

{OPERATOR} {
	return *yytext;
}

. {}

%%

int yywrap(){
    return 1;
}
