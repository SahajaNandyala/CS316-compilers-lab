#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <bits/stdc++.h>
#include <vector>
#include <iostream>
using namespace std;

int blocks_count = 0;
int scope_count = -1;
bool is_variable_declaration = false;
string variable_type;

struct entry
{
	string ID;
	string Value;
	string Type;
	int line;
};

struct symbol_tab
{
	string scope_name;
	vector<entry> entries;	
};

vector<symbol_tab> symbol_table;


void printSymbolTable()
{
	for (int i = 0; i < symbol_table.size(); i++)
	{
		if (i != 0)
		{
			cout<< "\n";
		}
		cout<< "Symbol table " << symbol_table[i].scope_name << endl;
		
		for (int j = 0; j < symbol_table[i].entries.size(); j++)
		{
			if (symbol_table[i].entries[j].Type == "STRING" )
			{
				cout<< "name " << symbol_table[i].entries[j].ID << " type " << symbol_table[i].entries[j].Type << " value " << symbol_table[i].entries[j].Value<<endl;
			}
			else 
			{
				cout<< "name " << symbol_table[i].entries[j].ID << " type " << symbol_table[i].entries[j].Type<<endl;
			}
		}
		
	}
}

bool isDeclared(string id)
{
	for(int i = 0; i < symbol_table[scope_count].entries.size(); i++)
	{
		if (symbol_table[scope_count].entries[i].ID.compare(id) == 0)
		{
			cout << "DECLARATION ERROR " << id << " (previous declaration was at line " << symbol_table[scope_count].entries[i].line << ')' << endl;
			return true;
		}			
		
	}
	
	return false;
}

void addScope(string scope, bool isBlock)
{	
	if(isBlock)
	{
		blocks_count++;
		scope = "BLOCK " + to_string(blocks_count);
	}
	
	struct symbol_tab new_table;
	new_table.scope_name = scope;			 
	symbol_table.push_back(new_table);
	scope_count++;
	
}

void addEntry(string ID, string Type, string Value, int line)
{
	struct entry new_entry;
	new_entry.ID = ID;
	new_entry.Type = Type;
	new_entry.Value = Value; 
	new_entry.line = line;
	symbol_table[scope_count].entries.push_back(new_entry);
}

string find_entry_type(string id)
{
	for(int i = 0; i < symbol_table[scope_count].entries.size(); i++)
	{
		if (symbol_table[scope_count].entries[i].ID.compare(id) == 0)
		{
			return symbol_table[scope_count].entries[i].Type;
		}			
		
	}
	for(int i = 0; i < symbol_table[0].entries.size(); i++)
	{
		if (symbol_table[0].entries[i].ID.compare(id) == 0)
		{
			return symbol_table[0].entries[i].Type;
		}				
	}
	return "nan";
}
#endif
