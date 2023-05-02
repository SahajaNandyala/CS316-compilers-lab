#ifndef AST_HPP
#define AST_HPP


	
struct ASTnode
{
	string node_type; // OPERATOR, INTLITERAL, FLOATLITERAL, IDENTIFIER, COMPARE, CALL
	string value;
	ASTnode *left = NULL;
    ASTnode *right = NULL;
    vector<ASTnode*> *par_list;
};


struct ASTnode* create_node(string node_type, string value, ASTnode *left, ASTnode *right, vector<ASTnode*> *par_list)
{
	ASTnode* new_node = new ASTnode;
	new_node->node_type = node_type;
	new_node->value = value;
	new_node->left = left;
    new_node->right = right;
    new_node->par_list = par_list;
	return new_node;
}

#endif
