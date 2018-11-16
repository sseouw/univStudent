#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef char Element;

typedef struct tTreeNode
{
	Element data;
	struct tTreeNode*left, *right; 
} TreeNode;

TreeNode* CreateTree(TreeNode *left, Element item, TreeNode *right) 
{
	TreeNode *pNewNode = (TreeNode*)malloc(sizeof(TreeNode)); 
	
	if (pNewNode == NULL) 
		return NULL;

	pNewNode->data = item;
	pNewNode->left = left;
	pNewNode->right = right;
	return pNewNode;
}

void Preorder(TreeNode *root) 
{
	if (root == NULL) 
		return;

	printf("%c", root->data); 
	Preorder(root->left); 
	Preorder(root->right);
}

void Inorder(TreeNode *root) 
{ 
	if (root == NULL) 
		return; 

	Inorder(root->left); 
	printf("%c", root->data); 
	Inorder(root->right); 
}

void Postorder(TreeNode *root) 
{
	if (root == NULL) 
		return;

	Postorder(root->left); 
	Postorder(root->right); 
	printf("%c", root->data);
}

void DestroyTree(TreeNode *root) 
{
	if (root == NULL) 
		return;

	if (root->left) 
		DestroyTree(root->left); 
	if (root->right) 
		DestroyTree(root->right);
	free(root);
}

void CBT(TreeNode *root, char* data, int num, int level, TreeNode** ret,int test)
{
	int sum=2;

	if (data[num] == '\0')
		return ;

	for (int i = 1; i < level; i++)
		sum *= 2;
	
	TreeNode* pNewNode = CreateTree(NULL, data[num], NULL);
	pNewNode->data = data[num];
	
	if (root->left == NULL)
	{	
		root->left = pNewNode;
		ret[num] = root->left;
		CBT(root, data, num + 1, level,ret,test);
	}
	else if (root->right == NULL)
	{
		root->right = pNewNode;
		ret[num] = root->right;

		if (num == sum - 2)
			CBT(ret[sum / 2 - 1], data, num + 1, level + 1, ret, sum / 2);
		else
			CBT(ret[test], data, num + 1, level, ret, test + 1);
	}
}


void BFT(TreeNode *root, char* data, int num, int level, TreeNode** ret, int test)
{
	int sum = 2;

	if (num == 1)
		printf("%c",root->data);

	if (data[num] == '\0')
		return;

	for (int i = 1; i < level; i++)
		sum *= 2;

	if (root->left->data != NULL)
	{
		printf("%c", root->left->data);
		ret[num] = root->left;
		root->left->data = NULL;
		BFT(root, data, num + 1, level, ret, test);
	}
	else if (root->right->data != NULL)
	{
		ret[num] = root->right;
		printf("%c", root->right->data);
		root->right->data = NULL;

		if (num == sum - 2)
			BFT(ret[sum / 2 - 1], data, num + 1, level + 1, ret, sum / 2);
		else
			BFT(ret[test], data, num + 1, level, ret, test + 1);
	}
}

int main(int argc, char *argv[]) {
	TreeNode *root;
	TreeNode **ret=(TreeNode**)malloc(100 * sizeof(TreeNode*));;
	char* data,ch,ch2[100],ch3[100];
	int a=0;

	data = &ch;

	printf("Enter the String : ");
	for (int i=0 ; i < 100; i++)
	{
		scanf("%c", data);
		if (*data == '\n')
		{
			ch2[i] = '\0';
			break;
		}
		else if (*data == ' ')
		{
			i--;
			*data = ch2[i];
		}
		
		ch2[i] = *data;
	}//' '阑 力寇茄 巩磊历厘

	root = CreateTree(NULL, ch2[0], NULL);// 谎府 积己

	CBT(root, ch2, 1, 2, ret,2);// CBT积己 
	printf("\n");

	printf("Preorder : ");
	Preorder(root);
	printf("\n");
	printf("inorder : ");
	Inorder(root);
	printf("\n");
	printf("Postorder : ");
	Postorder(root);
	printf("\n");
	printf("breath-first traversal : ");
	BFT(root, ch2, 1, 2, ret, 2);
	printf("\n");
	return 0;
}