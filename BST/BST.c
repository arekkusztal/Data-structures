#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <unistd.h>

enum side{
	LEFT,
	RIGHT
};

struct node {
	uint32_t val;
	struct node *right;
	struct node *left;
};

struct bts_tree {
	struct node *root;
} bts_tree;

void find_curr_prev_node(struct bts_tree *tree,
		struct node ** curr, struct node ** prev,
		uint32_t val) {
	
	if ((*curr)->val == val) {
		goto ret;
	}
		
	if (*curr != NULL)
	while ((*curr)->val != val) {
		if (val < (*curr)->val && (*curr)->left != NULL) {
			(*prev) = (*curr);
			(*curr) = (*curr)->left;
		}
		else if (val >= (*curr)->val && (*curr) != NULL) {
			(*prev) = (*curr);
			(*curr) = (*curr)->right;
		}
		else {
			*curr = NULL;
			goto ret;
		}
	}
	

ret:
	return;
	
}

struct node * find_node(struct bts_tree *tree,
		uint32_t val) {
	struct node * child;
	struct node * curr;
	
	if (val >= tree->root->val)
		child = tree->root->right;
	else
		child = tree->root->left;
	
	curr = tree->root;
	
	while (child != NULL) {
		curr = child;
		if (val >= child->val)
			child = child->right;
		else
			child = child->left;		
	}
	
	return curr;
}

int bts_insert_node(struct bts_tree *tree, 
		uint32_t val) {

	struct node * the_node;
	struct node * curr;
	
	the_node = malloc(sizeof(struct node));
	the_node->val = val;
	the_node->right = NULL;
	the_node->left = NULL;
	
	if (tree->root == NULL) {
		tree->root = the_node;
		goto ret;
	}
	
	curr = find_node(&bts_tree, val);
	if (val >= curr->val)
		curr->right = the_node;
	else
		curr->left = the_node;
	
ret:
	return 0;
};

int bts_delete_node(struct bts_tree * tree,
		uint32_t val) {

	struct node * curr;
	struct node * prev = NULL;
	struct node * topright = NULL;
	struct node * topright_prev = NULL;

	curr = bts_tree.root;
	if (bts_tree.root->val != val) {
		find_curr_prev_node(&bts_tree, &curr, &prev, val);
	}
	
	if (curr->left != NULL) {
		topright_prev = curr;
		topright = curr->left;
		
		if (topright->right != NULL) {
			while (topright->right != NULL) {
				topright_prev = topright;
				topright = topright->right;
			}
	
			topright_prev->right = topright->left;	
			
			if (topright != curr->right) {
				topright->right = curr->right;
			} else {
				topright->right = NULL;			
			}
			
			if (topright != curr->left) {
				topright->left = curr->left;
			} else {
				topright->left = NULL;			
			}			
			
			curr = topright;	
			
			if (prev) {
			if (prev->val > curr->val) {
				prev->left = curr;
			} else {
				prev->right = curr;			
			}	
			}
			else
				tree->root = curr;
		} else {
			topright->right = curr->right;
			curr = topright;
			if (prev == NULL) {
				bts_tree.root = curr;
			} else {
				prev->right = curr;
			}
			
		}		
	}
	else if (curr->right != NULL) {
		if (prev) {
			prev->left = curr->right;
		}
		
		if (prev == NULL) {
			curr->right->left = curr->left;
		}
		
		curr = curr->right;	

		if (prev == NULL) {
		tree->root = curr;
		}
	}
	else {
		if (prev)
		if (prev->val > curr->val) {
			prev->left = NULL;
		} else {
			prev->right = NULL;			
		}
		curr = NULL;
	}

ret:	
	return 0;
}

void print_tree(struct node * node) {

	printf("\n NODE : %p, val : %u, \n\tleft : %p, \tright : %p",
			node, node->val, node->left, node->right);
	if (node->left != NULL) {
		print_tree(node->left);		
	}
	if (node->right != NULL) {
		print_tree(node->right);
	}
}

int main()
{	
	bts_insert_node(&bts_tree, 14);
	bts_insert_node(&bts_tree, 7);
	bts_insert_node(&bts_tree, 12);
	bts_insert_node(&bts_tree, 22);
	bts_insert_node(&bts_tree, 15);
	bts_insert_node(&bts_tree, 2);
	bts_insert_node(&bts_tree, 3);
	
	print_tree(bts_tree.root);
	printf("\n----------------");
	
	bts_delete_node(&bts_tree, 14);
	bts_delete_node(&bts_tree, 12);
	bts_delete_node(&bts_tree, 15);
	bts_insert_node(&bts_tree, 15);
	bts_insert_node(&bts_tree, 15);
	bts_insert_node(&bts_tree, 15);
	bts_insert_node(&bts_tree, 14);
	print_tree(bts_tree.root);
	
	
	struct node *curr = bts_tree.root;
	struct node *prev = NULL;
	
	
	printf("\n");
	
	return 0;
}
