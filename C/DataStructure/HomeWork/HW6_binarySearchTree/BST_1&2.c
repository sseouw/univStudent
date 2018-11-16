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

TreeNode* _addBST(TreeNode*root, TreeNode*newNode) 
{
	if (root == NULL) 
		return newNode;

	if (newNode->data < root->data)
		root->left = _addBST(root->left, newNode);
	else if (newNode->data > root->data)
		root->right = _addBST(root->right, newNode);

	return root;
}

void BST(TreeNode*root, char* data, int num)
{
	if (data[num] == '\0')
		return;

	TreeNode* pNewNode = CreateTree(NULL, data[num], NULL);
	pNewNode->data = data[num];

	_addBST(root, pNewNode);

	BST(root, data, num + 1);
}

TreeNode *SearchBST(TreeNode *root, Element key)
{
	while (root != NULL)
	{
		if (key == root->data)
			break;
		else if (key < root->data)
			root = root->left;
		else if (key > root->data)
			root = root->right;
	}
	return root;
}

TreeNode* _deleteBST(TreeNode *root, Element data, int* success)
{
	if (root == NULL)
	{
		success = 0;
		return root;
	}
	if (data < root->data)
		root->left = _deleteBST(root->left, data, success);
	else if (data > root->data)
		root->right = _deleteBST(root->right, data, success);
	else
	{
		TreeNode *delPtr = NULL;
		success = 1;

		if (!root->right)
		{
			delPtr = root;
			root = root->left;
			free(delPtr);
			return root;
		}
		else if (!root->left)
		{
			delPtr = root;
			root = root->right;
			free(delPtr);
			return root;
		}
		else
		{
			for (delPtr = root->left; delPtr->right != NULL; delPtr = delPtr->right);
			root->data = delPtr->data;
			root->left = _deleteBST(root->left, delPtr->data, success);
		}
	}
	return root;
}

void BFT(TreeNode *root,int num,TreeNode** ret,int test,char* ch2)
{
	if (root == NULL || root->data == NULL)
		return;

	printf("%c",root->data);

	if (ch2[test] == '\0')
		return;

	if (root->right != NULL&&root->left != NULL)
	{
		ret[num] = root->left;
		ret[num + 1] = root->right;
		BFT(ret[test], num + 2, ret,test+1, ch2);
	}
	else if (root->right == NULL&&root->left != NULL)
	{
		ret[num] = root->left;
		BFT(ret[test], num + 1, ret,test+1, ch2);
	}
	else if (root->right != NULL&&root->left == NULL)
	{
		ret[num] = root->right;
		BFT(ret[test], num + 1, ret,test+1, ch2);
	}
	else if (root->right == NULL&&root->left == NULL)
		if(ret[test]!=NULL)
			BFT(ret[test], num, ret, test+1, ch2);
		return;

	return;
}

int main()
{
	TreeNode *root;
	TreeNode **ret = (TreeNode**)malloc(100 * sizeof(TreeNode*));;
	char* data, ch, ch2[100], ch3[100];
	int a = 0,sum=0,sum2=0;

	data = &ch;

	printf("Enter the String : ");
	for (int i = 0; i < 100; i++)
	{
		scanf("%c", data);
		if (*data == '\n')
		{
			ch2[sum2] = '\0';
			break;
		}
		else if (*data == ' ')
			sum++;
	
		for (int j = 0; j < i; j++)
			if (ch2[j] == *data)
				sum++;

		if(sum==0)
			ch2[sum2++] = *data;

		sum = 0;
	}//' ',반복문자를 제외한 문자저장

	root = CreateTree(NULL, ch2[0], NULL);// 뿌리 생성
	
	BST(root, ch2, 1);//BST생성

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
	BFT(root, 1, ret,1,ch2);
	printf("\n");

	return 0;
}