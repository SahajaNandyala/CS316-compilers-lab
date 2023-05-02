%{
    #include "microParser.h"
%}
INTLITERAL [0-9]+
SPACE [ \r\n\t ]
OPERATOR [:]|[+]|[-]|[*]|[/]|[=]|[!]|[<]|[>]|[(]|[)]|[,]|[;]


%%
5
"//".*\n {}

{INTLITERAL} {return INTLITERAL;}

[0-9]*['.'][0-9]+ {return FLOATLITERAL;}

\"(\\.|[^"\\])*\"  {return STRINGLITERAL;}

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
INT {return INT;}
VOID {return VOID;}
STRING {return STRING;}
FLOAT {return FLOAT;}

[a-zA-Z][a-zA-Z0-9]* {return IDENTIFIER;}

{SPACE}+ {}

{OPERATOR} {return *yytext;}

%%

int yywrap(){
    return 1;
}
