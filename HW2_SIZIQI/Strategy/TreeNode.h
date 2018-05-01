#pragma once
#include "Point.h"
class TreeNode
{
public:
	Point* point; //��¼�ýڵ�ʱ���ߵ�λ��
	int father; //���ڵ�
	int* children; //�ӽڵ���
	int childrenMaxIndex; //�ӽڵ�����������λ��
	bool isMyStep; //�洢�ò��ǲ����ҷ��ߣ�trueΪ�ҷ��ߣ�falseΪ�Է���
	bool isLeaf; //�ж��Ƿ�ΪҶ�ڵ�

public:
	TreeNode(void);
	TreeNode(int x, int y, bool isMySteps, int fatherIndex);
	~TreeNode(void);
};

