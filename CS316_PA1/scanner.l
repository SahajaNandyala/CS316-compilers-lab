%{

%}
ADD "+"
SUB "-"
DIVIDE "/"
EQUAL "="
MULTIPLY "*"
NOT_EQUAL "!="
SET_EQUAL_TO ":="
GREATTHAN ">"
LESSTHAN "<"
GREATER_EQUAL ">="
LESSER_EQUAL "<="
SEMICOLON ";"
COMMA ","
OPEN_BRACKET "("
CLOSE_BRACKET ")"
PROGRAM "PROGRAM"
BEGIN "BEGIN"
END "END"
FUNCTION "FUNCTION"
READ "READ"
WRITE "WRITE"
IF "IF"
ELSE "ELSE"
ENDIF "ENDIF"
WHILE "WHILE"
ENDWHILE "ENDWHILE"
BREAK "BREAK"
RETURN "RETURN"
CONTINUE "CONTINUE"
INT "INT"
VOID "VOID"
STRING "STRING"
FLOAT "FLOAT"

%%

"//".*"\n"            /* comment */

[0-9]+ {fprintf(yyout,"Token Type: INTLITERAL\nValue: %s\n",yytext);}

[0-9]*['.'][0-9]+ {fprintf(yyout,"Token Type: FLOATLITERAL\nValue: %s\n",yytext);}

\"(\\.|[^"\\])*\"  {fprintf(yyout,"Token Type: STRINGLITERAL\nValue: %s\n",yytext);}

{SET_EQUAL_TO}|{ADD}|{SUB}|{DIVIDE}|{EQUAL}|{MULTIPLY}|{NOT_EQUAL}|{GREATTHAN}|{LESSTHAN}|{GREATER_EQUAL}|{LESSER_EQUAL}|{SEMICOLON}|{COMMA}|{OPEN_BRACKET}|{CLOSE_BRACKET} {fprintf(yyout,"Token Type: OPERATOR\nValue: %s\n",yytext);}

{PROGRAM}|{BEGIN}|{END}|{FUNCTION}|{READ}|{WRITE}|{IF}|{ELSE}|{ENDIF}|{WHILE}|{ENDWHILE}|{BREAK}|{CONTINUE}|{RETURN}|{INT}|{VOID}|{STRING}|{FLOAT} {fprintf(yyout,"Token Type: KEYWORD\nValue: %s\n",yytext);}

[a-zA-Z][a-zA-Z0-9]* {fprintf(yyout,"Token Type: IDENTIFIER\nValue: %s\n",yytext);}

[ \t\n]+          /* eat up whitespace */



%%"

int yywrap(){}

int main(int argc, char *argv[]){

FILE *f_out,*f_in ;
f_in = fopen(argv[1],"r");
f_out = fopen(argv[2],"w");
yyin = f_in;
yyout = f_out;
yylex();
fclose(yyin);
fclose(yyout);

return 0;
}
