#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
	char *word;
	struct TreeNode *venstreBarn;
	struct TreeNode *høyreBarn;
} TreeNode;


TreeNode *createNode(const char *word) {
	TreeNode *new = malloc(sizeof *new);

	if (new == NULL) {
		printf("memory allocation failed.\n");
		exit(1);
	}

	new->word = malloc(strlen(word) + 1);

	if (new->word == NULL) {
		free(new);
		printf("memory allocation failed.\n");
		exit(1);
	}



	strcpy(new->word, word);
	new->venstreBarn = NULL;
	new->høyreBarn = NULL;
	
	return new;
}

TreeNode *insertNode(TreeNode *root, const char *word) {

	if (root == NULL) {
		return createNode(word);
	}

	int compare = strcmp(word, root->word);

	if (compare < 0) {
		root->venstreBarn = insertNode(root->venstreBarn, word);
	}
	else {
		root->høyreBarn = insertNode(root->høyreBarn, word);
	}

	return root;
}
void printLevel(const TreeNode* node, int depth, int width) {
	if (depth == 0) {
		const char* word = node != NULL ? node->word : "";
		int length = (int)strlen(word);
		int left = (width - length) / 2;
		int right = width - length - left;

		printf("%*s%s%*s", left, "", word, right, "");
		return;
	}

	printLevel(node != NULL ? node->venstreBarn : NULL,
		depth - 1, width);

	printLevel(node != NULL ? node->høyreBarn : NULL,
		depth - 1, width);
}

void printTree(const TreeNode* root) {
	if (root == NULL) {
		return;
	}

	int width = 64;

	for (int level = 0; level < 4; level++) {
		printLevel(root, level, width);
		printf("\n");
		width /= 2;
	}
}

void freeTree(TreeNode* node) {
	if (node == NULL) {
		return;
	}

	freeTree(node->venstreBarn);
	freeTree(node->høyreBarn);

	free(node->word);
	free(node);
}

int main(void) {
	TreeNode* root = NULL;
	char word[100];

	printf("Skriv ord med mellomrom mellom. Avslutt med 'stopp':\n");

	while (scanf("%99s", word) == 1) {
		if (strcmp(word, "stopp") == 0) {
			break;
		}

		root = insertNode(root, word);
	}

	printTree(root);
	freeTree(root);

	return 0;
}



