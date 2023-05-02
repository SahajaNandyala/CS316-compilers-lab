#ifndef CODE_GENERATION_HPP
#define CODE_GENERATION_HPP

#include <bits/stdc++.h>
#include <string.h> 
#include <vector>
#include "symbolTable.hpp"

bool is_write = false;
bool is_read = false;
int temp_count = -1;
int label_count = -1;
vector<int> labels;
vector<int> while_labels;
bool is_while_block = false;

struct code_object
{
	vector<string> instructions;
	string result_register;
	string result_type;
};


string get_register()
{
	temp_count++;
	string reg = "r" + to_string(temp_count);
	return reg;
}

string get_label()
{
	label_count++;
	string label = "label" + to_string(label_count);
	return label;
}

struct code_object* generate_code(struct ASTnode* ast_node)
{	
	struct code_object* current_code_object = new code_object;
	struct code_object* left_code_object;
	struct code_object* right_code_object;
	
	if (ast_node->left != nullptr)
	{
		left_code_object = generate_code(ast_node->left);		
	}

	if (ast_node->right != nullptr)
	{
		right_code_object = generate_code(ast_node->right);
	}

	if (ast_node->node_type == "OPERATOR")
	{
		
		if (ast_node->value == "+")
		{	
			string command;
			for (auto& it : left_code_object->instructions) 
			{
				current_code_object->instructions.push_back(it);
			}
			for (auto& it : right_code_object->instructions) 
			{
				current_code_object->instructions.push_back(it);
			}
			
			if (left_code_object->result_type =="INT" && right_code_object->result_type == "INT" )
			{
				command = "addi " +  right_code_object->result_register  + " " + left_code_object->result_register;
				current_code_object->result_type = "INT";
			}
			else
			{
				command = "addr "+  right_code_object->result_register  + " " + left_code_object->result_register;
				current_code_object->result_type = "FLOAT";
			}
			current_code_object->result_register = left_code_object->result_register;
			current_code_object->instructions.push_back(command);
			
		}
		else if (ast_node->value == "-") 
		{
			string command;
			for (auto& it : left_code_object->instructions) 
			{
				current_code_object->instructions.push_back(it);
			}
			for (auto& it : right_code_object->instructions) 
			{
				current_code_object->instructions.push_back(it);
			}
			
			if (left_code_object->result_type =="INT" && right_code_object->result_type == "INT" )
			{
				command = "subi " +  right_code_object->result_register  + " " + left_code_object->result_register;
				current_code_object->result_type = "INT";
			}
			else
			{
				command = "subr "+  right_code_object->result_register  + " " + left_code_object->result_register;
				current_code_object->result_type = "FLOAT";
			}
			current_code_object->result_register = left_code_object->result_register;
			current_code_object->instructions.push_back(command);
			
		}
		else if (ast_node->value == "*") 
		{
			string command;
			for (auto& it : left_code_object->instructions) 
			{
				current_code_object->instructions.push_back(it);
			}
			for (auto& it : right_code_object->instructions) 
			{
				current_code_object->instructions.push_back(it);
			}
			
			if (left_code_object->result_type =="INT" && right_code_object->result_type == "INT" )
			{
				command = "muli " +  right_code_object->result_register  + " " + left_code_object->result_register;
				current_code_object->result_type = "INT";
			}
			else
			{
				command = "mulr "+  right_code_object->result_register  + " " + left_code_object->result_register;
				current_code_object->result_type = "FLOAT";
			}
			current_code_object->result_register = left_code_object->result_register;
			current_code_object->instructions.push_back(command);
		
		}
		else if (ast_node->value == "/") 
		{
			string command;
			for (auto& it : left_code_object->instructions) 
			{
				current_code_object->instructions.push_back(it);
			}
			for (auto& it : right_code_object->instructions) 
			{
				current_code_object->instructions.push_back(it);
			}
			
			if (left_code_object->result_type =="INT" && right_code_object->result_type == "INT" )
			{
				command = "divi " +  right_code_object->result_register  + " " + left_code_object->result_register;
				current_code_object->result_type = "INT";
			}
			else
			{
				command = "divr "+  right_code_object->result_register  + " " + left_code_object->result_register;
				current_code_object->result_type = "FLOAT";
			}
			current_code_object->result_register = left_code_object->result_register;
			current_code_object->instructions.push_back(command);
		
		}
		else if (ast_node->value == ":="){
			string command = "move " + right_code_object->result_register + " " + ast_node->left->value;
			for (auto& it : right_code_object->instructions) 
			{
				current_code_object->instructions.push_back(it);
			}
			current_code_object->result_type = right_code_object->result_type;
			current_code_object->instructions.push_back(command);
		
		}
				
	}
	else if (ast_node->node_type == "COMPARE")
	{
		string command;
		string cmp_command;
		for (auto& it : left_code_object->instructions) 
		{
			current_code_object->instructions.push_back(it);
		}
		for (auto& it : right_code_object->instructions) 
		{
			current_code_object->instructions.push_back(it);
		}
		
		if (left_code_object->result_type =="INT" && right_code_object->result_type == "INT" )
		{
			cmp_command = "cmpi " + left_code_object->result_register + " " + right_code_object->result_register ;
		}
		else
		{
			cmp_command = "cmpr "+  left_code_object->result_register  + " " + right_code_object->result_register;
		}
		
		
		current_code_object->instructions.push_back(cmp_command);
		
		string flabel = get_label();
		string after_else_label = get_label();
		

		if(is_while_block)
		{
			while_labels.push_back(label_count);
		}
		labels.push_back(label_count);
		
		
		if (ast_node->value == "=") 
		{
			command = "jne " + flabel; /* Conditional jump to ( else part ) or (out of while part) */
		}
		else if (ast_node->value == "!=") 
		{
			command = "jeq " + flabel;
		}
		else if (ast_node->value == ">") 
		{
			command = "jle " + flabel;
		}
		else if (ast_node->value == ">=") 
		{
			command = "jlt " + flabel;
		}
		else if (ast_node->value == "<") 
		{
			command = "jge " + flabel;
		}
		else if (ast_node->value == "<=") 
		{
			command = "jgt " + flabel;
		}
		
		current_code_object->instructions.push_back(command);
		
	}
	else if (ast_node->node_type == "INTLITERAL")
	{	
		current_code_object->result_register = get_register();
		current_code_object->result_type = "INT";
		
		string command = "move " + ast_node->value + " " + current_code_object->result_register;
		current_code_object->instructions.push_back(command);
	}
	else if (ast_node->node_type == "FLOATLITERAL")
	{
		current_code_object->result_register = get_register();
		current_code_object->result_type = "FLOAT";
		
		string command = "move " + ast_node->value + " " + current_code_object->result_register;
		current_code_object->instructions.push_back(command);
	}
	else if (ast_node->node_type == "IDENTIFIER")
	{
		current_code_object->result_register = get_register();
		current_code_object->result_type = find_entry_type(ast_node->value);
		
		string command = "move " + ast_node->value + " " + current_code_object->result_register;
		current_code_object->instructions.push_back(command);
	}
	
	return current_code_object;

}


void write_code(string id)
{
	bool is_global;
	is_global = true;			
	for(int i = 0; i < symbol_table[scope_count].entries.size(); i++)
	{
		if (symbol_table[scope_count].entries[i].ID.compare(id) == 0)
		{	
			if (symbol_table[scope_count].entries[i].Type == "STRING")
			{
				cout << "sys writes " << symbol_table[scope_count].entries[i].ID << '\n';
			}
			else if (symbol_table[scope_count].entries[i].Type == "INT")
			{
				cout << "sys writei " << symbol_table[scope_count].entries[i].ID << '\n';
			}
			else if(symbol_table[scope_count].entries[i].Type == "FLOAT")
			{
				cout << "sys writer " << symbol_table[scope_count].entries[i].ID << '\n';
			}
			is_global = false;
			break;
		}		
	}
	
	if(is_global)
	{
		for(int i = 0; i < symbol_table[0].entries.size(); i++)
		{
			if (symbol_table[0].entries[i].ID.compare(id) == 0)
			{	
				if (symbol_table[0].entries[i].Type == "STRING")
				{
					cout << "sys writes " << symbol_table[0].entries[i].ID << '\n';
				}
				else if (symbol_table[0].entries[i].Type == "INT")
				{
					cout << "sys writei " << symbol_table[0].entries[i].ID << '\n';
				}
				else if(symbol_table[0].entries[i].Type == "FLOAT")
				{
					cout << "sys writer " << symbol_table[0].entries[i].ID << '\n';
				}
				break;
			}		
		}
	}
}

void read_code(string id)
{

bool is_global;
				is_global = true;			
				for(int i = 0; i < symbol_table[scope_count].entries.size(); i++)
				{
					if (symbol_table[scope_count].entries[i].ID.compare(id) == 0)
					{							
						if (symbol_table[scope_count].entries[i].Type == "INT")
						{
							cout << "sys readi " << symbol_table[scope_count].entries[i].ID << '\n';
						}
						else if(symbol_table[scope_count].entries[i].Type == "FLOAT")
						{
							cout << "sys readr " << symbol_table[scope_count].entries[i].ID << '\n';
						}
						is_global = false;
						break;
					}		
				}
				
				if(is_global)
				{
					for(int i = 0; i < symbol_table[0].entries.size(); i++)
					{
						if (symbol_table[0].entries[i].ID.compare(id) == 0)
						{	
							if (symbol_table[0].entries[i].Type == "INT")
							{
								cout << "sys readi " << symbol_table[0].entries[i].ID << '\n';
							}
							else if(symbol_table[0].entries[i].Type == "FLOAT")
							{
								cout << "sys readr " << symbol_table[0].entries[i].ID << '\n';
							}
							break;
						}		
					}
				}
}
#endif
