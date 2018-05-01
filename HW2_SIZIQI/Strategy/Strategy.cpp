#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <conio.h>
#include <atlstr.h>
#include "Point.h"
#include "Strategy.h"
#include "TreeNode.h"
#include "Judge.h"

using namespace std;

//type=1:�鿴��λ���Ƿ���ҷ�������в;type=2:�鿴�ҷ��ԶԷ��Ƿ�����в
bool hasThreadInPoint(int x, int y, const int M, const int N, int** board, int type) {
	//��������������
	int bottomIndex = x; //��׶���1��λ��
	while (bottomIndex < M-1) {
		if (board[bottomIndex+1][y] != type) {
			break;
		}
		bottomIndex++;
	}
	//_cprintf("(%d,%d) = %d\n", x, y, bottomIndex-x+1);
	if (bottomIndex - x >= 3) {
		return true;
	} 
	//���Ǻ���������
	int leftIndex = y; //�������1��λ��
	while (leftIndex > 0) {
		if (board[x][leftIndex-1] != type) {
			break;
		}
		leftIndex--;
	}
	int rightIndex = y; //���Ҷ���1��λ��
	while (rightIndex < N-1) {
		if (board[x][rightIndex+1] != type) {
			break;
		}
		rightIndex++;
	}
	//_cprintf("(%d,%d) = %d\n", x, y, rightIndex-leftIndex+1);
	if (rightIndex - leftIndex >= 3) {
		return true;
	}
	//������б��������
	int leftDelta = 0; //�������չ�ĸ���
	while (y - leftDelta > 0 && x - leftDelta > 0) {
		if (board[x-leftDelta-1][y-leftDelta-1] != type) {
			break;
		}
		leftDelta++;
	}
	int rightDelta = 0; //���Ҷ���չ�ĸ���
	while (y + rightDelta < N-1 && x + rightDelta < M-1) {
		if (board[x+rightDelta+1][y+rightDelta+1] != type) {
			break;
		}
		rightDelta++;
	}
	//_cprintf("(%d,%d) = %d\n", x, y, rightIndex-leftIndex+1);
	if (rightDelta + leftDelta >= 3) {
		return true;
	}
	//���Ƿ�б��������
	leftDelta = 0; //�������չ�ĸ���
	while (y - leftDelta > 0 && x + leftDelta < M-1) {
		if (board[x+leftDelta+1][y-leftDelta-1] != type) {
			break;
		}
		leftDelta++;
	}
	rightDelta = 0; //���Ҷ���չ�ĸ���
	while (y + rightDelta < N-1 && x - rightDelta > 0) {
		if (board[x-rightDelta-1][y+rightDelta+1] != type) {
			break;
		}
		rightDelta++;
	}
	//_cprintf("(%d,%d) = %d\n", x, y, rightIndex-leftIndex+1);
	if (rightDelta + leftDelta >= 3) {
		return true;
	}
	return false;
}

/*
	���Ժ����ӿ�,�ú������Կ�ƽ̨����,ÿ�δ��뵱ǰ״̬,Ҫ�����������ӵ�,�����ӵ������һ��������Ϸ��������ӵ�,��Ȼ�Կ�ƽ̨��ֱ����Ϊ��ĳ�������
	
	input:
		Ϊ�˷�ֹ�ԶԿ�ƽ̨ά����������ɸ��ģ����д���Ĳ�����Ϊconst����
		M, N : ���̴�С M - ���� N - ���� ����0��ʼ�ƣ� ���Ͻ�Ϊ����ԭ�㣬����x��ǣ�����y���
		top : ��ǰ����ÿһ���ж���ʵ��λ��. e.g. ��i��Ϊ��,��_top[i] == M, ��i������,��_top[i] == 0
		_board : ���̵�һά�����ʾ, Ϊ�˷���ʹ�ã��ڸú����տ�ʼ���������Ѿ�����ת��Ϊ�˶�ά����board
				��ֻ��ֱ��ʹ��board���ɣ����Ͻ�Ϊ����ԭ�㣬�����[0][0]��ʼ��(����[1][1])
				board[x][y]��ʾ��x�С���y�еĵ�(��0��ʼ��)
				board[x][y] == 0/1/2 �ֱ��Ӧ(x,y)�� ������/���û�����/�г������,�������ӵ㴦��ֵҲΪ0
		lastX, lastY : �Է���һ�����ӵ�λ��, ����ܲ���Ҫ�ò�����Ҳ������Ҫ�Ĳ������ǶԷ�һ����
				����λ�ã���ʱ��������Լ��ĳ����м�¼�Է������ಽ������λ�ã�����ȫȡ�������Լ��Ĳ���
		noX, noY : �����ϵĲ������ӵ�(ע:��ʵ���������top�Ѿ����㴦���˲������ӵ㣬Ҳ����˵���ĳһ��
				������ӵ�����ǡ�ǲ������ӵ㣬��ôUI�����еĴ�����Ѿ������е�topֵ�ֽ�����һ�μ�һ������
				��������Ĵ�����Ҳ���Ը�����ʹ��noX��noY��������������ȫ��Ϊtop������ǵ�ǰÿ�еĶ�������,
				��Ȼ�������ʹ��lastX,lastY�������п��ܾ�Ҫͬʱ����noX��noY��)
		���ϲ���ʵ���ϰ����˵�ǰ״̬(M N _top _board)�Լ���ʷ��Ϣ(lastX lastY),��Ҫ���ľ�������Щ��Ϣ�¸������������ǵ����ӵ�
	output:
		������ӵ�Point
*/
extern "C" __declspec(dllexport) Point* getPoint(const int M, const int N, const int* top, const int* _board, 
	const int lastX, const int lastY, const int noX, const int noY){
	clock_t startTime = clock();
	srand((unsigned)time(NULL)); 

	/*
		��Ҫ������δ���
	*/
	int x = -1, y = -1;//���ս�������ӵ�浽x,y��
	int** board = new int*[M];
	for(int i = 0; i < M; i++){
		board[i] = new int[N];
		for(int j = 0; j < N; j++){
			board[i][j] = _board[i * N + j];
		}
	}
	
	/*
		�������Լ��Ĳ������������ӵ�,Ҳ���Ǹ�����Ĳ�����ɶ�x,y�ĸ�ֵ
		�ò��ֶԲ���ʹ��û�����ƣ�Ϊ�˷���ʵ�֣�����Զ����Լ��µ��ࡢ.h�ļ���.cpp�ļ�
	*/
	//Add your own code below
	//AllocConsole();
	/*
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			_cprintf("%d ",board[i][j]);
		}
		_cprintf("\n");
	}
	*/
	//��һ�����ȿ�����û�б�ʤ��λ��
	bool hasThread = false;
	for (int i = 0; i < N; i++) {
		if (top[i] > 0) {
			if (hasThreadInPoint(top[i]-1, i, M, N, board, 2)) {
				//����вλ��ֱ��������вλ����
				x = top[i]-1;
				y = i;
				hasThread = true;
				break;
			}
		}
	}
	//�ڶ����������Է���û����в�Լ���λ��
	if (!hasThread) {
		for (int i = 0; i < N; i++) {
			if (top[i] > 0) {
				if (hasThreadInPoint(top[i]-1, i, M, N, board, 1)) {
					//����вλ��ֱ��������вλ����
					x = top[i]-1;
					y = i;
					hasThread = true;
					break;
				}
			}
		}
	}
	//�������������û�еĻ������ǽ������ؿ�������
	if (!hasThread) {
		const int STATE_NUM = 2000000;
		double C = 1.0; //�����ؿ��������е�ϵ��C
		double epsilon = 0.1; //���ڷ�ĸ�ϱ���Ϊ0�ĵ�����
		TreeNode** states = new TreeNode* [STATE_NUM];
		states[0] = new TreeNode(-1, -1, true, -1); //���ڵ�ĸ��ڵ���Ϊ-1
		states[0]->isLeaf = false; //��Ȼ���ڵ㲻��Ҷ�ӽڵ㣬������Ϸ�Ѿ���������ǰ�����Ѿ��������
		int stateSize = 1; //״̬�ռ�Ĵ�С
		int* currentTop = new int [N]; //��ǰ��top��Ϣ
		int** currentBoard = new int* [M]; //��¼�ڳ��Թ����е�ǰ�������Ϣ
		for (int i = 0; i < M; i++) {
			currentBoard[i] = new int [N];
		}
		while (true) {
			clock_t nowTime = clock();
			if (nowTime - startTime >= 2.5 * CLOCKS_PER_SEC || stateSize >= STATE_NUM) {
				break; //�ﵽʱ����ֵ�������Ѿ�������ֹͣ��չ
			}
			//��ʼ��Ϊ�����״̬
			for (int i = 0; i < N; i++) {
				currentTop[i] = top[i];
			}
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					currentBoard[i][j] = board[i][j];
				}
			}
			int currentIndex = 0; //��ǰ����״̬���±�
			while (true) {
				if (isTie(N, currentTop)) { //�ж��Ƿ�Ϊƽ�ֵ�״̬
					int backIndex = currentIndex; //�����ڵ�index��Ϊ���ݵ����
						while (true) {
							states[backIndex]->winTimes += 0.5; //ƽ�����ҷ�Ӯ�Ĵ�����0.5
							states[backIndex]->totalTimes++;
							backIndex = states[backIndex]->father;
							if (backIndex == -1) {
								break; //���ݵ����ڵ���˳�ѭ��
							}
						}
						break; //������ɺ���ֹ������̽
				}
				if (states[currentIndex]->isMyStep) {
					bool hasSucceedPoint = false; //����ʤ��
					for (int i = 0; i < N; i++) {
						if (currentTop[i] > 0) {
							if (hasThreadInPoint(currentTop[i]-1, i, M, N, currentBoard, 2)) {
								hasSucceedPoint = true;
								break;
							}
						}
					}
					if (hasSucceedPoint) { //��������ʤ��ʱ���ϻ��ݽ��
						int backIndex = currentIndex; //�����ڵ�index��Ϊ���ݵ����
						while (true) {
							states[backIndex]->winTimes++;
							states[backIndex]->totalTimes++;
							backIndex = states[backIndex]->father;
							if (backIndex == -1) {
								break; //���ݵ����ڵ���˳�ѭ��
							}
						}
						break; //������ɺ���ֹ������̽
					} else { //û����ʤ��ʱ����������ؿ��������Ĺ�ʽ���ҵ���һ��״̬�Ľڵ�
						double* topProb = new double [N]; //�洢����λ���ϵĸ��ʴ�С
						int* topIndex = new int [N]; //�����ڵ�λ����children�����е�index,-1��ʾ����������
						for (int i = 0; i < N; i++) {
							topIndex[i] = -1;
						}
						//�ȸ��ϳ�ʼ����
						double zeroProb = sqrt(log(1+states[0]->totalTimes) / epsilon); //δ����չ�ڵ�������ֵ
						for (int i = 0; i < N; i++) {
							if (currentTop[i] > 0) {
								topProb[i] = zeroProb; //�Ƚ�����չ�ڵ�ĸ��ʶ���Ϊ�����ֵ
							} else {
								topProb[i] = 0.0; //������չ�ڵ�ĸ�����Ϊ0
							}
						}
						//�����Ѿ���չ������Ϣ
						for (int i = 0; i < states[currentIndex]->childrenMaxIndex; i++) {
							int childIndex = states[currentIndex]->children[i]; //�ӽڵ��index
							int childTopIndex = states[childIndex]->point->y;
							topIndex[childTopIndex] = i; //��¼��λ���ϵ��ӽڵ��ӦindexΪi
							double thisProb = states[childIndex]->winTimes / (epsilon + states[childIndex]->totalTimes) + 
								C * sqrt(log(1+states[0]->totalTimes) / (epsilon+states[childIndex]->totalTimes)); //����ô�ʵ�ʵĸ���
							topProb[childTopIndex] = thisProb; //�滻��Ĭ�ϵĸ���
						}
						//�Ը��ʽ��й�һ��
						double totalProb = 0.0;
						for (int i = 0; i < N; i++) {
							totalProb += topProb[i];
						}
						for (int i = 0; i < N; i++) {
							topProb[i] /= totalProb;
						}
						//ȡ�����������һ�����չ
						double randNum = rand() / double(RAND_MAX);
						int nextStep = 0; //��һ����y����
						double nowTotalProb = 0.0;
						for (int i = 0; i < N; i++) {
							nowTotalProb += topProb[i];
							if (randNum <= nowTotalProb) {
								nextStep = i;
								break; //�ҵ�����һ����չ��λ��
							}
						}
						if (topIndex[nextStep] != -1) {
							currentIndex = states[currentIndex]->children[topIndex[nextStep]]; //�ҵ�����һ��Ŀ���λ��
						} else {
							states[stateSize] = new TreeNode(currentTop[nextStep]-1, nextStep, false, currentIndex); //��һ���ֵ��Է�����
							states[currentIndex]->children[states[currentIndex]->childrenMaxIndex] = stateSize;
							states[currentIndex]->childrenMaxIndex++;
							currentIndex = stateSize;
							stateSize++;	
						}
						delete []topProb;
						delete []topIndex;
					}
				}
			}
		}

		for (int i = 0; i < stateSize; i++) {
			delete states[i];
		}
		delete []states;
		
		for (int i = N-1; i >= 0; i--) {
			if (top[i] > 0) {
				x = top[i] - 1;
				y = i;
				break;
			}
		}
	
	}

	/*
     //a naive example
	for (int i = N-1; i >= 0; i--) {
		if (top[i] > 0) {
			x = top[i] - 1;
			y = i;
			break;
		}
	}
	*/
	
	
	/*
		��Ҫ������δ���
	*/
	clearArray(M, N, board);
	return new Point(x, y);
}


/*
	getPoint�������ص�Pointָ�����ڱ�dllģ���������ģ�Ϊ��������Ѵ���Ӧ���ⲿ���ñ�dll�е�
	�������ͷſռ䣬����Ӧ�����ⲿֱ��delete
*/
extern "C" __declspec(dllexport) void clearPoint(Point* p){
	delete p;
	return;
}

/*
	���top��board����
*/
void clearArray(int M, int N, int** board){
	for(int i = 0; i < M; i++){
		delete[] board[i];
	}
	delete[] board;
}


/*
	������Լ��ĸ�������������������Լ����ࡢ����������µ�.h .cpp�ļ�������ʵ������뷨
*/
