#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define maxsize 64
#define M 8
typedef struct {
	int x, y, p;
}qtype;																	  /*队中元素类型*/
typedef struct {															/*定义队列*/
		qtype data[maxsize];
		int front, rear;
}sqtype, * sqlink;


struct {																	   /*定义8个方向*/
		int u, v;
}madd[4] = { {0,1},{1,0},{0,-1},{-1,0} };


void path(sqlink q) {
	int i = q->rear;
	do {
		printf("\n(%d,%d)", q->data[i].x, q->data[i].y);
		i = q->data[i].p;
	} while (i);
}



int mazepath(int maze[M][M]) {			/*求最短路径*/
	int i, j, k, x, y, ma[M][M];
	sqlink q = (sqlink)malloc(sizeof(sqtype));
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++) {
			ma[i][j] = maze[i][j];		/*获取迷宫*/
		}
	}
	q->front = q->rear = 1;
	q->data[q->rear].x = q->data[q->rear].y = 2;			/*牛郎坐标进队*/
	q->data[q->rear].p = 0;
	ma[2][2] = -1;									/*牛郎已到达带点*/	while (q->front <= q->rear) {
		x = q->data[q->front].x;
		y = q->data[q->front].y;
		for (k = 0; k <= 3; k++) {				/*搜寻8个方向*/
			i = x + madd[k].u;
			j = y + madd[k].v;
			if (ma[i][j] == 0) {
				q->rear++;
				q->data[q->rear].x = i;
				q->data[q->rear].y = j;
				q->data[q->rear].p = q->front;
				ma[i][j] = -1;						/*标记该点*/
			}
			if (i == 5 && j == 5) {					/*判断牛郎是否到达织女坐标*/
				path(q);
				return(1);
			}
		}
		q->front++;

	}
	return(0);						/*无法找到*/
}


int main() {
	int maze[M][M] = { 0 };												/*初始化迷宫为0*/
	maze[0][1] = maze[2][6] = maze[4][4] = maze[7][1] = 1;						/*确定迷宫，1为不可行*/
	mazepath(maze);
	return 0;
}