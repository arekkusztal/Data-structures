#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <unistd.h>
#include <string.h>

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define RES "\x1B[0m"

enum side{
	LEFT,
	RIGHT
};

struct node {
	struct node *right;
	struct node *left;
	struct node *parent;
	uint32_t val;
	int w;

};

struct bts_tree {
	struct node *root;
} bts_tree;

void print_tree(struct node * node);

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
	
	if (tree->root->val == val)
		return tree->root;

	if (tree->root->val > val)
		curr = tree->root->left;
	else
		curr = tree->root->right;
	
	while (curr->val != val && curr != NULL) {
		if (curr->val > val)
			curr = curr->left;
		else
			curr = curr->right;
	}

	
	return curr;
}

struct node * find_node2(struct bts_tree *tree,
		uint32_t val, uint32_t *w, struct node ** parent) {
	struct node * child;
	struct node * curr;

	if (val >= tree->root->val) {
		child = tree->root->right;
	}
	else {
		child = tree->root->left;
	}
	curr = tree->root;

	while (child != NULL) {
		*parent = curr;
		curr = child;
		if (val >= child->val) {
			child = child->right;
		}
		else {
			child = child->left;
		}
	}
	curr->parent = *parent;
	return curr;
}


void rotate_left_2(struct bts_tree *tree,
		struct node * node) {

	struct node * parent;
	struct node * child;


	if (tree->root == node) {
		if (node->right->right != NULL) {
			tree->root = node->right;
			node->right->parent = NULL;
			node->parent = node->right;
			node->right->left = node;
			node->right = NULL;
			if (node->left)
				node->w = node->left->w + 1;
			else
				node->w = 1;
		}
		else {
			tree->root = node->right->left;
			tree->root->parent = NULL;
			node->right->parent = node->right->left;
			node->parent = node->right->left;
			node->right->left->left = node;
			node->right->left->right = node->right;
			node->right->left = NULL;
			node->right = NULL;
			if (node->left)
				node->w = node->left->w + 1;
			else
				node->w = 1;

			if (tree->root->right->right != NULL) {
				tree->root->right = tree->root->right->right + 1;
			} else if (tree->root->right->left != NULL) {
				tree->root->right = tree->root->right->left + 1;

			} else
				tree->root->right->w = 1;

			tree->root->w = 2;
		}

		return 0;
	}

	if (node->right->right != NULL) {
		printf("\nHere");
		if (node->parent->right == node)
			node->parent->right = node->right;
		else
			node->parent->left = node->right;

		node->right->parent = node->parent;
		node->parent = node->right;
		node->right->left = node;
		node->right = NULL;
		if (node->left)
			node->w = node->left->w + 1;
		else
			node->w = 1;

		printf("\nneed %u %u",node->parent->val,node->parent->w);
	}
	else {
		printf("\ntu tu");
	}


}


void rotate_right_2(struct bts_tree *tree,
		struct node * node) {

	struct node * parent;
	struct node * child;


	if (tree->root == node) {
		if (node->left->left != NULL) {


			tree->root = node->left;
			node->left->parent = NULL;
			node->parent = node->left;
			node->left->right = node;
			node->left = NULL;
			if (node->right)
				node->w = node->right->w + 1;
			else
				node->w = 1;
		}
		else {

			tree->root = node->left->right;
			tree->root->parent = NULL;
			node->left->parent = node->left->right;
			node->parent = node->left->right;
			node->left->right->right = node;
			node->left->right->left = node->left;
			node->left->right = NULL;
			node->left = NULL;
			if (node->right)
				node->w = node->right->w + 1;
			else
				node->w = 1;

			if (tree->root->left->left != NULL) {
				tree->root->left = tree->root->left->left + 1;
			} else if (tree->root->left->right != NULL) {
				tree->root->left = tree->root->left->right + 1;

			} else
				tree->root->left->w = 1;

			tree->root->w = 2;
		}

		return 0;
	}

	if (node->left->left != NULL) {
		printf("\nHere");
		if (node->parent->left == node)
			node->parent->left = node->left;
		else
			node->parent->right = node->left;

		node->left->parent = node->parent;
		node->parent = node->left;
		node->left->right = node;
		node->left = NULL;
		if (node->right)
			node->w = node->right->w + 1;
		else
			node->w = 1;

		printf("\nneed %u %u",node->parent->val,node->parent->w);
	}
	else {
		printf("\ntu tu");
	}


}


void rotate_left(struct bts_tree *tree,
		struct node * node) {

	struct node * parent;
	struct node * child;


	if (tree->root == node) {
		tree->root = node->right;
		node->right->parent = NULL;
	}

	child = node->right->left;
	node->right->left->parent = node;
	node->right->left = node;
	node->parent = node->right;
	node->right = child;

	if (node->left != NULL) {
		node->w = node->left->w + 1;
	}
	else {
		node->w = 1;
	}

	printf("\n ------ !! -------%u",node->parent->w);

}


void rotate_right(struct bts_tree *tree,
		struct node * node) {

	struct node * parent;
	struct node * child;


	if (tree->root == node) {
		tree->root = node->left;
		node->left->parent = NULL;
	}

	child = node->left->right;
	node->left->right->parent = node;
	node->left->right = node;
	node->parent = node->left;
	node->left = child;

	if (node->right != NULL) {
		node->w = node->right->w + 1;
	}
	else {
		node->w = 1;
	}

	printf("\n ------ !! -------%u",node->parent->w);

}

uint32_t sum;

void traverse(struct bts_tree *tree,
		struct node * node) {

	struct node * child = node;
	sum = node->w;
	node = node->parent;
	while (node != tree->root) {
		++sum;
		if (node->w < sum)
			node->w = sum;
		child = node;
		printf("\nTRAVERSE: examining %i node",node->val);
		if (node->parent->right == node) { //On the right side of parent
			printf("\n---node rsbt %i",node->val);
			if (node->left) {
				if (node->w - node->left->w > 2) {
					printf("\nNeed5 to rotate left%i",node->val);
					rotate_left_2(tree, node);
				}
			}
			if (node->w >= 3) {
				if (node->left == NULL) {
					printf("\nNeed4 L to rotate left%i ",node->val);
					rotate_left_2(tree, node);
					print_tree(bts_tree.root);
				}
				else if (node->right == NULL){
					printf("\nNeed4 R to rotate right%i ",node->val);
					rotate_right_2(tree, node);
					print_tree(bts_tree.root);

				}
				sum -= 2;
			}
		} else { //On the left subtree
			printf("\---node lsbt %i",node->val);
			if (node->right) {
				if (node->w - node->right->w > 2) {
					printf("\nNeed5 to rotate right%i",node->val);
					rotate_right_2(tree, node);
				}
			}

			if (node->w >= 3) {

					if (node->left == NULL) {
						printf("\nNeed4L to rotate left%i ",node->val);
						rotate_left_2(tree, node);
						print_tree(bts_tree.root);
					}
					else if (node->right == NULL){
						printf("\nNeed4R to rotate right%i ",node->val);
						rotate_right_2(tree, node);
						print_tree(bts_tree.root);

					}
					sum -= 2;
			}
		}


		node = node->parent;


	}
	/*++sum;
	if (node->w < sum)
		node->w = sum; */

	if (node->left && node->right)
		node->w = node->left->w > node->right->w ? node->left->w : node->right->w;
	else if (node->left)
		node->w = node->left->w;
	else if (node->right)
		node->w = node->right->w;

	node->w++;

	printf("\nROOT: v=%i w=%i",node->val,node->w);

	if (node->left) {
		if (node->w - node->left->w > 2) {
			printf("\nNeed2 to rotate %i",node->val);
			print_tree(bts_tree.root);
			rotate_left(tree, node);
		}
		if (node->right && node->w - node->right->w > 2) {
			printf("\nNeed2 to rotate right%i",node->val);
			print_tree(bts_tree.root);
			rotate_right(tree, node);
		}

		if (node->w >= 3 && node->right == NULL) {
			printf("\nNeed6 to rotate right%i",node->val);
			rotate_right_2(tree, node);
		}
	}
	else {
		if (node->w - node->right->w > 2) {
			printf("\nWhat %u, %u",node->w,node->left->w);
			printf("\nNeed2 to rotate %i",node->val);
			print_tree(bts_tree.root);
			rotate_right(tree, node);
		}
		if (node->w >= 3 && node->left == NULL) {
			printf("\nNeed6 to rotate left%i",node->val);
			rotate_left_2(tree, node);
		}
	}

	print_tree(bts_tree.root);
}

void upstairs(struct bts_tree *tree,
		struct node * node) {


	while (node != tree->root) {
		if (node->w == 2) {
			rotate_left(tree, node);
		}
		node = node->parent;
	}

}
int bts_insert_node(struct bts_tree *tree, 
		uint32_t val) {

	struct node * the_node;
	struct node * curr;
	struct node * parent = NULL;
	int w;
	printf(YEL"\nInsertion of %u\n"RES,val);
	the_node = malloc(sizeof(struct node));
	the_node->val = val;
	the_node->right = NULL;
	the_node->left = NULL;
	the_node->w = 1;
	the_node->parent = NULL;
	
	if (tree->root == NULL) {
		tree->root = the_node;
		goto ret;
	}
	
	curr = find_node2(&bts_tree, val, &w, &parent);
	//find_curr_prev_node(&bts_tree, &curr, &parent,val);

	if (val >= curr->val) {
		curr->right = the_node;
	}
	else {
		curr->left = the_node;
	}
	the_node->parent = curr;
	traverse(tree,the_node);

	print_tree(bts_tree.root);
	printf("\n----------------");

ret:
	return 0;
};

int bts_delete_node(struct bts_tree * tree,
		uint32_t val) {

	struct node * curr;
	struct node * prev = NULL;

	curr = find_node(tree, val);
	printf(RED"\nDelete at %p val %i"RES,curr,curr->val);
	if (curr->left) {
		if (curr == tree->root) {
			tree->root = curr->left;
		}
		if (curr->left->right) {
			printf("\nByc tu!!");
			curr->left->right->parent = curr->parent;
			curr->left->right->left  = curr->left;
			curr->left->right->right = curr->right;
			if (curr->parent->right == curr) {
				curr->parent->right = curr->left->right;
			}
			else {
				curr->parent->left = curr->left->right;
				curr->left->right = NULL;//curr->left->right->left;
			}
		}
		else {
			curr->left->parent = curr->parent;
			curr->left->left  = curr->left;
			curr->left->right = curr->right;
			if (curr->parent->right == curr) {
				curr->parent->right = curr->left;
			}
			else {
				curr->parent->left = curr->left;
			}
		}

	}
	else if (curr->right) {
		if (curr == tree->root) {
			tree->root = curr->right;
		}
		if (curr->right->left) {
			curr->right->left->parent = curr->parent;
			curr->right->left->right  = curr->right;
			curr->right->left->left = curr->left;
			if (curr->parent->left == curr) {
				curr->parent->left = curr->right->left;
			}
			else {
				curr->parent->right = curr->right->right;
			}
		}
		else {
			curr->right->parent = curr->parent;
			curr->right->right  = curr->right;
			curr->right->left = curr->left;
			if (curr->parent->left == curr) {
				curr->parent->left = curr->right;
			}
			else {
				curr->parent->right = curr->right;
			}
		}
	}
	else {
		if (curr->parent->right == curr) {
			curr->parent->right = NULL;
		}
		else {
			curr->parent->left = NULL;
		}
	}

	traverse(tree,curr);
	free(curr);

ret:	
	return 0;
}

void print_tree(struct node * node) {

	if (node == bts_tree.root) {
		printf("\nROOT -- ");
	}
	char red[6] = GRN;
	char left[6] = RES, right[6] = RES;
	//char l = RES;

	if (node->left == NULL) {
		//left = red;
		memcpy(left, red, 6);
	}
	if (node->right == NULL) {
		memcpy(right, red, 6);
	}


	printf("\n NODE : %p, val : "RED" %u "RES", w : %d\n\t parent %p,  \n\t left :%s %p "YEL" (%i) "RES",  \tright :%s %p "YEL" (%i)" RES,
				node, node->val, node->w,node->parent,left,
				node->left , node->left ? node->left->val : -1,
				right,  node->right , node->right ? node->right->val : -1);

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
	bts_insert_node(&bts_tree, 22);
	bts_insert_node(&bts_tree, 9);
	bts_insert_node(&bts_tree, 6);
	bts_insert_node(&bts_tree, 5);
	bts_insert_node(&bts_tree, 4);
	bts_insert_node(&bts_tree, 3);
	bts_insert_node(&bts_tree, 2);
	bts_insert_node(&bts_tree, 15);

	bts_delete_node(&bts_tree, 5);

/*	bts_insert_node(&bts_tree, 14);
	bts_insert_node(&bts_tree, 5);
	bts_insert_node(&bts_tree, 22);
	bts_insert_node(&bts_tree, 17);
	bts_insert_node(&bts_tree, 27);
	bts_insert_node(&bts_tree, 36); */



/*	bts_insert_node(&bts_tree, 27);
	bts_insert_node(&bts_tree, 35);
	bts_insert_node(&bts_tree, 51);
	bts_insert_node(&bts_tree, 8);
	bts_insert_node(&bts_tree, 10); */

/*	rotate_left(&bts_tree, bts_tree.root->right);

	bts_insert_node(&bts_tree, 25);
	print_tree(bts_tree.root);
	printf("\n----------------");
	*/

	printf("\n");
	
	return 0;
}
