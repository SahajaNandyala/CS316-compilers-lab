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
vector<string> instructions;
vector<int> links;

struct code_object
{
	vector<string> instructions;
	string result_register;
	string result_type;
};


string get_register()
{
	int t = symbol_table[function_scope].temp_count++;
	string reg = "r" + to_string(t);
	return reg;
}

string get_label()
{
	label_count++;
	string label = "label" + to_string(label_count);
	return label;
}

string function_call(string function, vector<struct ASTnode*> *par_list);

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
		else if (ast_node->value == ":=")
		{
			int scope;
			struct entry left_entry = find_entry(ast_node->left->value, scope);
			string command;
			if (scope != 0)
			{
				command = "move " + right_code_object->result_register + " " + left_entry.stack_value;
			}
			else
			{
				command = "move " + right_code_object->result_register + " " + ast_node->left->value;
			}		
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
		
		string command;
		command = "move " + ast_node->value + " " + current_code_object->result_register;
		current_code_object->instructions.push_back(command);
	}
	else if (ast_node->node_type == "FLOATLITERAL")
	{
		current_code_object->result_register = get_register();
		current_code_object->result_type = "FLOAT";
		
		string command;
		command = "move " + ast_node->value + " " + current_code_object->result_register;
		current_code_object->instructions.push_back(command);
	}
	else if (ast_node->node_type == "IDENTIFIER")
	{
		current_code_object->result_register = get_register();
		
		int scope;
		struct entry left_entry = find_entry(ast_node->value, scope);
		string command;
		if (scope != 0)
		{
			command = "move " + left_entry.stack_value + " " + current_code_object->result_register;
		}
		else
		{
			command = "move " + ast_node->value + " " + current_code_object->result_register;
		}
		// cout << "scopes : "<< function_scope << " " << scope ;
		current_code_object->result_type = left_entry.Type;
		current_code_object->instructions.push_back(command);
	}
	else if (ast_node->node_type == "CALL")
	{
		current_code_object->result_register = function_call(ast_node->value,ast_node->par_list);
		
		for(int i = 0; i < symbol_table.size(); i++)
		{
			if (symbol_table[i].scope_name == ast_node->value)
			{
				current_code_object->result_type = symbol_table[i].return_type;
				break;
			}
		}
		
	}
	
	return current_code_object;

}


void write_code(string id)
{
	bool is_global;
	is_global = true;	
	string command;
	int f = 0;
	vector<int> parents = symbol_table[current_scope].parent_scopes;
	for(int p = 0; p < parents.size()-1; p++)
	{
		for(int i = 0; i < symbol_table[parents[p]].entries.size(); i++)
		{
			if (symbol_table[parents[p]].entries[i].ID.compare(id) == 0)
			{	
				if (symbol_table[parents[p]].entries[i].Type == "STRING")
				{
					command = "sys writes " + symbol_table[parents[p]].entries[i].stack_value + '\n';
				}
				else if (symbol_table[parents[p]].entries[i].Type == "INT")
				{
					command = "sys writei " + symbol_table[parents[p]].entries[i].stack_value + '\n';
				}
				else if(symbol_table[parents[p]].entries[i].Type == "FLOAT")
				{
					command = "sys writer " + symbol_table[parents[p]].entries[i].stack_value + '\n';
				}
				is_global = false;
				f = 1;
				break;
			}		
		}
		if (f) break;
	}
	
	if(is_global)
	{
		for(int i = 0; i < symbol_table[0].entries.size(); i++)
		{
			if (symbol_table[0].entries[i].ID.compare(id) == 0)
			{	
				if (symbol_table[0].entries[i].Type == "STRING")
				{
					command = "sys writes " + symbol_table[0].entries[i].ID + '\n';
				}
				else if (symbol_table[0].entries[i].Type == "INT")
				{
					command = "sys writei " + symbol_table[0].entries[i].ID + '\n';
				}
				else if(symbol_table[0].entries[i].Type == "FLOAT")
				{
					command = "sys writer " + symbol_table[0].entries[i].ID + '\n';
				}
				break;
			}		
		}
	}
	
	instructions.push_back(command);
}

void read_code(string id)
{
	string command;
	bool is_global;
			is_global = true;
			int f = 0;
			// cout << "I am here\n";
			vector<int> parents = symbol_table[current_scope].parent_scopes;
			
			for(int p = 0; p < parents.size(); p++)
			{			
				for(int i = 0; i < symbol_table[parents[p]].entries.size(); i++)
				{
					if (symbol_table[parents[p]].entries[i].ID.compare(id) == 0)
					{							
						if (symbol_table[parents[p]].entries[i].Type == "INT")
						{
							command = "sys readi " + symbol_table[parents[p]].entries[i].stack_value + '\n';
						}
						else if(symbol_table[parents[p]].entries[i].Type == "FLOAT")
						{
							command = "sys readr " + symbol_table[parents[p]].entries[i].stack_value + '\n';
						}
						is_global = false;
						f = 1;
						break;
						
					}		
				}
				if (f)
				{
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
							command = "sys readi " + symbol_table[0].entries[i].ID + '\n';
						}
						else if(symbol_table[0].entries[i].Type == "FLOAT")
						{
							command = "sys readr " + symbol_table[0].entries[i].ID + '\n';
						}
						break;
					}		
				}
			}
	instructions.push_back(command);		
}

void push_into_stack(string function)
{
	string command;
	command = "push\n";
	instructions.push_back(command);
	
	// cout << "push " << '\n'; // return address
	
	for(int i = 0; i < 30; i++) // saved registers
	{
		command = "push r" + to_string(i) + "\n"; 
		instructions.push_back(command);
		
		// cout << "push r" << to_string(i) << "\n"; 
	}
	
	command = "jsr " + function + "\n"; 
	instructions.push_back(command);
	
	// cout << "jsr " << function << '\n';
}

string function_call(string function, vector<struct ASTnode*> *par_list)
{	
	string command;
	command = "push\n";
	instructions.push_back(command);
	
	// cout << "push " << '\n'; // push return address
	
	for(int i = 0; i < par_list->size(); i++) // push arguments
	{	 
		// cout << i << '\n';
		// cout << i << "ast node value : " << (*par_list)[i]->value << '\n' ;
		struct code_object* p_code_object = generate_code((*par_list)[i]);
		
		for (auto& it : p_code_object->instructions) 
		{	
			 command = it + '\n';
			 instructions.push_back(command);
			 // cout << it << '\n';
		}
		
		command = "push " + p_code_object->result_register + '\n';
		instructions.push_back(command);
		
		// cout << "push " << p_code_object->result_register <<'\n';
	}
	
	for(int i = 0; i < 30; i++) // push saved registers
	{
		command = "push r" + to_string(i) + "\n";
		instructions.push_back(command);
		
		// cout << "push r" << to_string(i) << "\n"; 
	}
	
	command = "jsr " + function + '\n';
	instructions.push_back(command);
	
	// cout << "jsr " << function << '\n';
	
	for(int i = 29; i > -1; i--) // pop saved registers
	{
		command =  "pop r" + to_string(i) + '\n';
		instructions.push_back(command);
		
		// cout << "pop r" << to_string(i) << "\n"; 
	}
	
	for(int i = 0; i < par_list->size(); i++) // pop arguments
	{
		command =  "pop\n";
		instructions.push_back(command);
		
		// cout << "pop\n";
	}
	
	string result_reg = get_register();
	
	command = "pop " + result_reg + '\n';
	instructions.push_back(command);
		
	// cout << "pop " << result_reg << '\n';
	
	
	return result_reg;
}

void printInstructions()
{
	int l = 0;
	for(int i = 0; i < string_decl.size(); i++) 
	{
		cout << string_decl[i];
	} 
	
	for(int i = 0; i < instructions.size(); i++) 
	{
		if (instructions[i] == "link")
		{
			cout << "link " << to_string(links[l]) << '\n';
			l++;
		}
		else
		{
			cout << instructions[i];
		}
		
		if (to_string(instructions[0][1]) == "r")
		{
			break;
		}
	}

}

#endif
