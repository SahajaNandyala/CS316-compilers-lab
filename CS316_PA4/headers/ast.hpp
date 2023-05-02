#ifndef AST_HPP
#define AST_HPP


	
struct ASTnode
{
	string node_type; // OPERATOR, INTLITERAL, FLOATLITERAL, IDENTIFIER, COMPARE
	string value;
	ASTnode *left = NULL;
    ASTnode *right = NULL;
};


struct ASTnode* create_node(string node_type, string value, ASTnode *left, ASTnode *right)
{
	ASTnode* new_node = new ASTnode;
	new_node->node_type = node_type;
	new_node->value = value;
	new_node->left = left;
    new_node->right = right;
    
	return new_node;
}

#endif
