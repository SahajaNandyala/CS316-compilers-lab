#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

int blocks_count = 0;
int scope_count = -1;
int current_scope;
int function_scope;
bool is_variable_declaration = false;
string variable_type;
vector<string> string_decl;
int temp_count = -1;

struct entry
{
	string ID;
	string Value;
	string Type;
	int line;
	string stack_value;
};

struct symbol_tab
{
	string scope_name;
	string return_type = "VOID";
	vector<entry> entries;
	vector<int> parent_scopes;	
	int param = 5;
	int local = 0;
	int temp_count = 0;
	//vector<int> registers{0,0,0,0};
	//std::map<std::string, int> registers = {{"r0",0},{"r1",0},{"r2",0},{"r3",0}};
};

vector<symbol_tab> symbol_table;


void printSymbolTable()
{
	cout << "\n---------------------\n";
	for (int i = 0; i < symbol_table.size(); i++)
	{
		if (i != 0)
		{
			cout<< "\n";
		}
		cout<< "Symbol table " << symbol_table[i].scope_name << endl;
		cout << "Parent Scopes : ";
		for(int j = 0; j < symbol_table[i].parent_scopes.size(); j++)
		{
			cout << symbol_table[i].parent_scopes[j] << " ";
		}
		cout << "\n";
		
		for (int j = 0; j < symbol_table[i].entries.size(); j++)
		{
			if (symbol_table[i].entries[j].Type == "STRING" )
			{
				cout<< "name " << symbol_table[i].entries[j].ID << " type " << symbol_table[i].entries[j].Type << " value " <<  symbol_table[i].entries[j].Value<< " stack value : "<< symbol_table[i].entries[j].stack_value << endl;
			}
			else 
			{
				cout<< "name " << symbol_table[i].entries[j].ID << " type " << symbol_table[i].entries[j].Type << " stack value : "<< symbol_table[i].entries[j].stack_value<<endl;
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

void addScope(string scope, bool isBlock, string return_type)
{	
	if(isBlock)
	{
		blocks_count++;
		scope = "BLOCK " + to_string(blocks_count);
	}
	
	struct symbol_tab new_table;
	new_table.scope_name = scope;
	scope_count++;
	new_table.parent_scopes.push_back(scope_count);
	if(scope_count > 0)
	{
		for(int i = 0; i < symbol_table[current_scope].parent_scopes.size(); i++)
		{
			new_table.parent_scopes.push_back(symbol_table[current_scope].parent_scopes[i]);
		}
	}
	new_table.return_type = return_type;		 
	symbol_table.push_back(new_table);
	current_scope = scope_count;
	
}

void addEntry(string ID, string Type, string Value, int line, bool is_param)
{
	struct entry new_entry;
	new_entry.ID = ID;
	new_entry.Type = Type;
	new_entry.Value = Value; 
	new_entry.line = line;
	if (is_param)
	{
		symbol_table[function_scope].param++;
		new_entry.stack_value = '$'+to_string(symbol_table[function_scope].param);
	}
	else
	{
		if(Type == "STRING")
		{
			new_entry.stack_value = ID + to_string(current_scope);
			string command;
			if (current_scope == 0)
			{
				command = "str " + ID + " " + Value + "\n" ;
				string_decl.push_back(command);
			}
			else
			{
				command = "str " + new_entry.stack_value + " " + Value + "\n" ;
				string_decl.push_back(command);
			}
		}
		else
		{
			symbol_table[function_scope].local--;
			new_entry.stack_value = '$'+to_string(symbol_table[function_scope].local);
		}
		
	}
	symbol_table[current_scope].entries.push_back(new_entry);
	
}

struct entry find_entry(string id, int& scope)
{
	// cout << "cs "<< current_scope << "  ";
	for(int j = 0; j < symbol_table[current_scope].parent_scopes.size(); j++)
	{
		
		int a = symbol_table[current_scope].parent_scopes[j];
		// cout << a << " ";
		for(int i = 0; i < symbol_table[a].entries.size(); i++)
		{
			// cout << symbol_table[a].entries[i].ID << ' ';
			if (symbol_table[a].entries[i].ID.compare(id) == 0)
			{	
				scope = a;

				// cout << "scope " << scope << "\n";
				return symbol_table[a].entries[i];
				
			}			
		}
	
	}
	struct entry new_entry;
	new_entry.Type = "NULL";
	
	return new_entry;
}



#endif
