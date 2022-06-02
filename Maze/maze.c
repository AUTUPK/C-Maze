#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define maxsize 64
#define M 8
typedef struct {
	int x, y, p;
}qtype;																	  /*����Ԫ������*/
typedef struct {															/*�������*/
		qtype data[maxsize];
		int front, rear;
}sqtype, * sqlink;


struct {																	   /*����8������*/
		int u, v;
}madd[4] = { {0,1},{1,0},{0,-1},{-1,0} };


void path(sqlink q) {
	int i = q->rear;
	do {
		printf("\n(%d,%d)", q->data[i].x, q->data[i].y);
		i = q->data[i].p;
	} while (i);
}



int mazepath(int maze[M][M]) {			/*�����·��*/
	int i, j, k, x, y, ma[M][M];
	sqlink q = (sqlink)malloc(sizeof(sqtype));
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++) {
			ma[i][j] = maze[i][j];		/*��ȡ�Թ�*/
		}
	}
	q->front = q->rear = 1;
	q->data[q->rear].x = q->data[q->rear].y = 2;			/*ţ���������*/
	q->data[q->rear].p = 0;
	ma[2][2] = -1;									/*ţ���ѵ������*/	while (q->front <= q->rear) {
		x = q->data[q->front].x;
		y = q->data[q->front].y;
		for (k = 0; k <= 3; k++) {				/*��Ѱ8������*/
			i = x + madd[k].u;
			j = y + madd[k].v;
			if (ma[i][j] == 0) {
				q->rear++;
				q->data[q->rear].x = i;
				q->data[q->rear].y = j;
				q->data[q->rear].p = q->front;
				ma[i][j] = -1;						/*��Ǹõ�*/
			}
			if (i == 5 && j == 5) {					/*�ж�ţ���Ƿ񵽴�֯Ů����*/
				path(q);
				return(1);
			}
		}
		q->front++;

	}
	return(0);						/*�޷��ҵ�*/
}


int main() {
	int maze[M][M] = { 0 };												/*��ʼ���Թ�Ϊ0*/
	maze[0][1] = maze[2][6] = maze[4][4] = maze[7][1] = 1;						/*ȷ���Թ���1Ϊ������*/
	mazepath(maze);
	return 0;
}