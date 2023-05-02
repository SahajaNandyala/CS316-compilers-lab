#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <iostream>
#include "microParser.hpp"

using namespace std;
int yyparse();
int yylex(); 
extern FILE* yyin;

// yerror function
void yyerror(const char *s){
  if(0);
}

// main function
int main(int argc, char* argv[]){
	if(argc > 1){
		FILE *filep = fopen(argv[1], "r");
		if(filep)
			yyin = filep;
	}
	
    if (yyparse() == 0)
	if(0);        
}
