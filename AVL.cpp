#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

typedef struct AVLTree
{
   int data;
   AVLTree *pLeft;
   AVLTree *pRight;
   int nHeight;
}AVLTree;

int Max(int a,int b);

int Heigth(AVLTree *Node);

AVLTree* insert(int nData, AVLTree *pNode);

AVLTree * LLRotate(AVLTree *pNode);

AVLTree * RRRotate(AVLTree *pNode);

AVLTree * LRRotate(AVLTree *pNode);

AVLTree * RLRotate(AVLTree *pNode);

void DeleteTree(AVLTree **pNode);

void PrintTree(AVLTree *pNode);

const int summary = 100000;

int deepmax = 0x80000000;
int main()
{
	AVLTree * pRoot = NULL;

	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < 400000000; i++)
	{
		pRoot = ::insert(rand()%summary,pRoot);
	}
	PrintTree(pRoot);
	return 0;
}

int Max(int a, int b)
{
   return ((a > b)? a:b);
}

int Height(AVLTree *pNode)
{
    if ( pNode == NULL)
		return -1;

	return pNode->nHeight;
}


AVLTree * insert(int nData, AVLTree* pNode)
{
    if ( NULL == pNode)
	{
	  pNode = new AVLTree();
	  pNode->data = nData;
	  pNode->nHeight =  0;
	  pNode->pLeft = NULL;
	  pNode->pRight = NULL;
	}
	else if (nData < pNode->data )//insert into left tree
   {
		pNode->pLeft = insert(nData,pNode->pLeft);

		if (Height(pNode->pLeft) - Height(pNode->pRight) == 2)//��ƽ��AVL
		{
			if (nData < pNode->pLeft->data)
		   {
		      pNode = LLRotate(pNode);
		   }
		   else
		   {
		     pNode = LRRotate(pNode);
		   }
		}
    }
	else if (nData > pNode->data)
   {
		pNode->pRight = insert(nData, pNode->pRight);

		if ( Height(pNode->pRight)- Height(pNode->pLeft) == 2)
		{
			if (nData > pNode->pRight->data)
			{
			   pNode = RRRotate(pNode);
			}
			else
			{
			  pNode = RLRotate(pNode);
			}
		}
   }
	pNode->nHeight = Max(::Height(pNode->pLeft),Height(pNode->pRight)) + 1;

	return pNode;
}

//**************************************************************************************
//      pNode                                                pNode->pLeft
//       /                                                        /\
//     pNode->pLeft                 -->        pNode->pLeft->pLeft  pNode 
//      /                                                     
// pNode->pLeft->pLeft                         
//**************************************************************************************

AVLTree* LLRotate(AVLTree *pNode)
{
  AVLTree *pNode1;
  pNode1 = pNode->pLeft;
  pNode->pLeft = pNode1->pRight;
  pNode1->pRight = pNode;
  //���½��ܵ�ĸ߶ȣ�
  pNode->nHeight = Max(::Height(pNode->pLeft), Height(pNode->pRight))+1;
  pNode1->nHeight = Max(::Height(pNode1->pLeft), pNode->nHeight) + 1;

  return pNode1;
}

//**************************************************************************************
//      pNode                                                pNode->pRight
//       \                                                        /\
//     pNode->pRight                 -->                     pNode  pNode->pRight->pRight              
//         \                                                      
// pNode->pRight->pRight                                       
//**************************************************************************************

AVLTree * RRRotate(AVLTree * pNode)//RR
{ 
	AVLTree *pNode1;
	pNode1 = pNode->pRight;
	pNode->pRight = pNode1->pLeft;
	pNode1->pLeft = pNode;

	pNode->nHeight = Max(::Height(pNode->pLeft),::Height(pNode->pRight)) + 1;
	pNode1->data = Max(::Height(pNode1->pRight), pNode->nHeight) + 1;

	return pNode1;
}


AVLTree  * LRRotate(AVLTree * pNode)
{
	pNode->pLeft = RRRotate(pNode->pLeft);//1.��ƽ��ڵ�pNode������Ӵ���������ת
	return (LLRotate(pNode));             //2.��ƽ��ڵ�pNode����������ת�������½ڵ�
}

AVLTree *RLRotate(AVLTree * pNode)
{
	pNode->pRight = LLRotate(pNode->pRight);//1.��ƽ��ڵ�pNode���ұ߶��Ӵ����������ת
	return (RRRotate(pNode));               //2.��ƽ��ڵ�pNode����������ת�������½ڵ�
}


void  DeleteTree(AVLTree **ppNode)
{
	if (ppNode == NULL || *ppNode == NULL)
         return ;
	DeleteTree(&((*ppNode)->pLeft));
	DeleteTree(&((*ppNode)->pRight));
	delete(*ppNode);
	*ppNode = NULL;
}

void ::PrintTree(AVLTree *pNode)
{
    if (pNode == NULL)
		return ;
	static int n = 0;
	if (pNode->nHeight > deepmax)
		deepmax = pNode->nHeight;
	PrintTree(pNode->pLeft);

	std::cout <<"["<<++n<<"] : Data = "<<pNode->data<< "  Height="<<pNode->nHeight <<"  MAX DEEPTH="<<deepmax<< std::endl;

	PrintTree(pNode->pRight);      
}











