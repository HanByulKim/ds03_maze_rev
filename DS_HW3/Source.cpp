/**
*********************************************
2016 Autumn DataStructure HW03
SNU Dept. of Electrical & Computer Engineering
2014-13261
Han-Byul Kim
*********************************************
Rev. log.
look for https://github.com/HanByulKim/ds03_maze_rev
*********************************************
**/

#include <opencv2\opencv.hpp>
#include "Set.h"
#include "Stack.h"
#include "Prev.h"
#include "Queue.h"
#include <iostream>

#define WINDOW_SIZE 600

using namespace std;
using namespace cv;

int maze_size;
int scale_factor;

int random_n();
void maze_builder(Mat& image, Set* set, int** mazeidx, int** mazemap, int pixel_ratio);
void DFS(Mat& image, Set* set, int** mazeidx, int** mazemap, int pixel_ratio);
bool DFS(int** mazemap, Stack* route, int x, int y);
void Random_Mouse(Mat& image, Set* set, int** mazeidx, int** mazemap, int pixel_ratio);
bool Random_Mouse(int** mazemap, Stack* route, int x, int y);
void Wall_Follower(Mat& image, Set* set, int** mazeidx, int** mazemap, int pixel_ratio);
bool Wall_Follower(int** mazemap, Stack* route, int x, int y, int dir_x, int dir_y);
void BFS(Mat& image, Set* set, int** mazeidx, int** mazemap, int pixel_ratio);
void BFS(int** mazemap, Queue* route, Prev** prev);

int main(int argc, char **argv)
{
	std::cout << " *********************************************\n 2016 Autumn DataStructure HW03 \n SNU Dept.of Electrical & Computer Engineering \n 2014 - 13261 \n Han - Byul Kim \n ********************************************* \n Rev.log. \n look for https://github.com/HanByulKim/ds03_maze_rev \n ********************************************* \n" << std::endl;

	std::cout << "Eneter the size of maze(n by n): ";
	std::cin >> maze_size;
	int pixel_ratio = 600 / maze_size;
	Mat WhiteImage(maze_size*pixel_ratio + 150, maze_size*pixel_ratio, CV_8UC3, Scalar(255, 255, 255));
	Mat image = WhiteImage.clone();	
	scale_factor = 10 / maze_size;
	
	for (int i = 0; i < maze_size; i++) {
		for (int j = 0; j < maze_size; j++) {			
			Point p1((j+1)*pixel_ratio, i*pixel_ratio);
			Point p2((j+1)*pixel_ratio, (i+1)*pixel_ratio -1);
			Point p3(i*pixel_ratio, (j+1)*pixel_ratio);
			Point p4((i + 1)*pixel_ratio-1, (j + 1)*pixel_ratio);

			line(image, p1, p2, Scalar(0, 0, 0));
			line(image, p3, p4, Scalar(0, 0, 0));
		}		
	}
	cv::putText(image, "PUSH SPACE BUTTON BY 5TIMES!", cv::Point(10, maze_size*pixel_ratio + 40), 2, 1, Scalar(0, 0, 0));
	imshow("maze", image);

	Set* set = new Set[maze_size*maze_size]; // set

	int** mazeidx = new int*[maze_size]; // index arr
	int** mazemap = new int*[2 * maze_size + 1]; // real maze
	int** mazemap_randmouse = new int*[2 * maze_size + 1];
	for (int i = 0; i < maze_size; i++)
		mazeidx[i] = new int[maze_size];
	for (int i = 0; i < 2*maze_size+1; i++)
		mazemap[i] = new int[2*maze_size+1];
	for (int i = 0; i < 2 * maze_size + 1; i++)
		mazemap_randmouse[i] = new int[2 * maze_size + 1];
	
	for (int i = 0; i < maze_size; i++) {
		for (int j = 0; j < maze_size; j++) {
			mazeidx[i][j] = j + i*maze_size;
			set[j + i*maze_size].add(j + i*maze_size);
			set[j + i*maze_size].setunioned(j + i*maze_size);
		}
	}
	for (int i = 0; i < 2 * maze_size + 1; i++) {
		for (int j = 0; j < 2 * maze_size + 1; j++) {
			if (i % 2 == 1 && j % 2 == 1)
				mazemap[i][j] = 0;
			else
				mazemap[i][j] = 2;
		}
	}
	
	char c;
	int cnt = 0;
	std::cout << "***********************" << std::endl;
	std::cout << "SPACE 1번 : 미로생성" << std::endl;
	std::cout << "SPACE 2번 : Shortest Path(DFS)" << std::endl;
	std::cout << "SPACE 3번 : Random Mouse" << std::endl;
	std::cout << "SPACE 4번 : Wall Follower" << std::endl;
	std::cout << "SPACE 5번 : BFS" << std::endl;
	std::cout << "***********************" << std::endl;
	std::cout << " ] 버튼을 누르면 다음 알고리즘이 스킵됩니다." << std::endl;
	std::cout << "Random Mouse 알고리즘을 생략하시고 테스트할 때 좋습니다." << std::endl;
	std::cout << "***********************" << std::endl;
	std::cout << "미로생성, Shortest Path는 큰 미로에서도 가능하나 나머지 알고리즘은 숫자가 너무 크면 렉이걸립니다." << std::endl;
	std::cout << "***********************" << std::endl;

	while (1) {
		c = cvWaitKey(30);
		if (c == 27) break;
		else if (c == 13) {
			cout << "ENTER" << endl;
		}
		else if (c == 32) {
			cout << "SPACE" << endl;
			if (cnt == 0) {
				std::cout << "Wait Please.." << std::endl;
				std::cout << "응답없음이 떠도 기다려주세요ㅜㅜ 70*70부터 시간이 생각보다 오래걸립니다." << std::endl;
				maze_builder(image, set, mazeidx, mazemap, pixel_ratio);
				std::cout << "size " << maze_size << " maze" << std::endl;
				cnt++;
				for (int i = 0; i < 2 * maze_size + 1; i++) {
					for (int j = 0; j < 2 * maze_size + 1; j++) {
						mazemap_randmouse[i][j] = mazemap[i][j];
					}
				}
			}
			else if (cnt == 1) {
				DFS(image, set, mazeidx, mazemap, pixel_ratio);
				cnt++;
			}
			else if (cnt == 2) {
				Random_Mouse(image, set, mazeidx, mazemap, pixel_ratio);
				cnt++;
			}
			else if (cnt == 3) {
				Wall_Follower(image, set, mazeidx, mazemap, pixel_ratio);
				cnt++;
			}
			else if (cnt == 4) {
				BFS(image, set, mazeidx, mazemap_randmouse, pixel_ratio);
				cnt=11;
			}
		}
		else if (cnt>=1 && c == 93) {
			std::cout << "Skip Algorithm " << cnt << std::endl;
			cnt++;
		}
	}
	
	delete[] set;
	for (int i = 0; i < maze_size; i++)
		delete mazeidx[i];
	delete[] mazeidx;
	for (int i = 0; i < 2*maze_size+1; i++)
		delete mazemap[i];
	delete[] mazemap;
	for (int i = 0; i < 2 * maze_size + 1; i++)
		delete mazemap_randmouse[i];
	delete[] mazemap_randmouse;
	return 0;
}

int random_n() { return rand() % (maze_size*maze_size); }
int random_vec() { return rand() % 4; }

void maze_builder(Mat& image, Set* set, int** mazeidx, int** mazemap, int pixel_ratio) {
	int target=0;
	int arr;
	int vector;
	int xtemp, ytemp;
	bool condition;
	int working = 0;

	while (set[target].size != maze_size*maze_size) {

		target = random_n();
		arr = random_vec();
		int tempidx;
		condition = true;
		switch (arr) {
		case 0: // top
			vector = -maze_size;
			if (target - maze_size < 0) condition = false;
			break;
		case 1: // right
			vector = 1;
			if (target % maze_size == maze_size-1) condition = false;
			break;
		case 2: // bottom
			vector = maze_size;
			if (target + maze_size >= maze_size*maze_size) condition = false;
			break;
		case 3: // left
			vector = -1;
			if (target % maze_size == 0) condition = false;
			break;
		}
		//->y
		if (condition && mazeidx[target / maze_size][target % maze_size] != mazeidx[(target + vector) / maze_size][(target + vector) % maze_size]) {
			set[mazeidx[target / maze_size][target % maze_size]].union_set(set[mazeidx[(target + vector) / maze_size][(target + vector) % maze_size]]);
			//set[mazeidx[target / maze_size][target % maze_size]].print();
			xtemp = ((2 * (target / maze_size) + 1) + (2 * ((target + vector) / maze_size) + 1)) / 2;
			ytemp = ((2 * (target % maze_size) + 1) + (2 * ((target + vector) % maze_size) + 1)) / 2;
			mazemap[xtemp][ytemp] = 0;
			tempidx = mazeidx[(target + vector) / maze_size][(target + vector) % maze_size];
			//std::cout << tempidx << " " << target+vector << std::endl;
			for (int i = 0; i < maze_size; i++) {
				for (int j = 0; j < maze_size; j++) {
					if (mazeidx[i][j] == tempidx)
						mazeidx[i][j] = mazeidx[target / maze_size][target % maze_size];
					//std::cout << mazeidx[i][j] << " ";
				}
				//std::cout << std::endl;
			}
			/*for (int i = 0; i < 2 * maze_size + 1; i++) {
				for (int j = 0; j < 2 * maze_size + 1; j++) {
					std::cout << mazemap[i][j] << " ";
				}
				std::cout << std::endl;
			}*/
		}
	}

	// Drawing
	for (int i = 0; i < maze_size; i++) {
		for (int j = 0; j < maze_size-1; j++) {
			if (i == 0 || j == 0) {
				if (mazemap[(2 * (i % maze_size) + 1)][(2 * (j % maze_size) + 2)] == 0) // vertical line
					line(image, cv::Point(pixel_ratio*(j + 1), pixel_ratio*i+1), cv::Point(pixel_ratio*(j + 1), pixel_ratio*i + pixel_ratio-1), Scalar(255, 255, 255));
				if (mazemap[(2 * (j % maze_size) + 2)][(2 * (i % maze_size) + 1)] == 0) // horizontal line
					line(image, cv::Point(pixel_ratio*i+1, pixel_ratio*(j + 1)), cv::Point(pixel_ratio*i + pixel_ratio-1, pixel_ratio*(j + 1)), Scalar(255, 255, 255));
			}
			else {
				if (mazemap[(2 * (i % maze_size) + 1)][(2 * (j % maze_size) + 2)] == 0) // vertical line
					line(image, cv::Point(pixel_ratio*(j + 1), pixel_ratio*i+1), cv::Point(pixel_ratio*(j + 1), pixel_ratio*i + pixel_ratio-1), Scalar(255, 255, 255));
				if (mazemap[(2 * (j % maze_size) + 2)][(2 * (i % maze_size) + 1)] == 0) // horizontal line
					line(image, cv::Point(pixel_ratio*i+1, pixel_ratio*(j + 1)), cv::Point(pixel_ratio*i + pixel_ratio-1, pixel_ratio*(j + 1)), Scalar(255, 255, 255));
			}


			if (i == 0) {
				if (mazemap[(2 * (i % maze_size) + 1)][(2 * (j % maze_size) + 2)] == 0) // vertical line
					line(image, cv::Point(pixel_ratio*(j + 1), pixel_ratio*i), cv::Point(pixel_ratio*(j + 1), pixel_ratio*i + pixel_ratio - 1), Scalar(255, 255, 255));
				if (mazemap[(2 * (j % maze_size) + 2)][(2 * (i % maze_size) + 1)] == 0) // horizontal line
					line(image, cv::Point(pixel_ratio*i, pixel_ratio*(j + 1)), cv::Point(pixel_ratio*i + pixel_ratio - 1, pixel_ratio*(j + 1)), Scalar(255, 255, 255));
			}
		}
	}

	imshow("maze", image);
}

void DFS(Mat& image, Set* set, int** mazeidx, int** mazemap, int pixel_ratio) {
	Stack* route = new Stack();

	route->push(1, 1);
	DFS(mazemap, route, 1, 1);
	
	int x1, y1;
	int x2, y2;
	int size = route->sizeis();
	for (int i = 0; i < size-1; i++) {
		x1 = route->topx();
		y1 = route->topy();
		route->pop();
		x2 = route->topx();
		y2 = route->topy();
		line(image, cv::Point(y1*pixel_ratio / 2, x1*pixel_ratio / 2), cv::Point(y2*pixel_ratio / 2, x2*pixel_ratio / 2), Scalar(0, 0, 255));
		imshow("maze", image);
	}
	cv::putText(image, "DFS", cv::Point(10, maze_size*pixel_ratio + 90), 2, 1, Scalar(0, 0, 255));
	imshow("maze", image);

	delete route;
}

bool DFS(int** mazemap, Stack* route, int x, int y) {
	int vector_x[4] = { 0,1,0,-1 };
	int vector_y[4] = { 1,0,-1,0 };
	bool pan = false;

	if (x == 2 * maze_size - 1 && y == 2 * maze_size - 1) {
		mazemap[x][y] = 1;
		pan = true;
	}

	mazemap[x][y] = 1;
	for (int i = 0; i < 4 && pan==false; i++) {
		if (mazemap[x + vector_x[i]][y + vector_y[i]] == 0) {
			route->push(x + vector_x[i], y + vector_y[i]);
			pan = DFS(mazemap, route, x + vector_x[i], y + vector_y[i]);
		}
	}
	if (pan == false) {
		mazemap[x][y] = 0;
		route->pop();
	}
	return pan;
}

void Random_Mouse(Mat& image, Set* set, int** mazeidx, int** mazemap, int pixel_ratio) {
	Stack* route = new Stack();
	std::cout << "----Random Mouse coordinate list----" << std::endl;

	route->push(1, 1);
	Random_Mouse(mazemap, route, 1, 1);
	std::cout << std::endl;

	int x1, y1;
	int x2, y2;
	int size = route->sizeis();
	for (int i = 0; i < size - 1; i++) {
		x1 = route->topx();
		y1 = route->topy();
		route->pop();
		x2 = route->topx();
		y2 = route->topy();
		line(image, cv::Point(y1*pixel_ratio / 2 + 5 * scale_factor, x1*pixel_ratio / 2 - 5 * scale_factor), cv::Point(y2*pixel_ratio / 2 + 5 * scale_factor, x2*pixel_ratio / 2 - 5 * scale_factor), Scalar(0, 255, 0));
		imshow("maze", image);
	}
	cv::putText(image, "Random Mouse", cv::Point(75, maze_size*pixel_ratio + 90), 2, 1, Scalar(0, 255, 0));
	imshow("maze", image);

	delete route;
}

bool Random_Mouse(int** mazemap, Stack* route, int x, int y) {
	int vector_x[4] = { 0,1,0,-1 };
	int vector_y[4] = { 1,0,-1,0 };
	bool pan = false;
	std::cout << "(" << x << "," << y << ")";

	if (x == 2 * maze_size - 1 && y == 2 * maze_size - 1) {
		mazemap[x][y] = 1;
		pan = true;
	}

	mazemap[x][y] = 1;
	while (!pan) {
		int i = random_vec();
		if (mazemap[x + vector_x[i]][y + vector_y[i]] != 2) {
			route->push(x + vector_x[i], y + vector_y[i]);
			pan = Random_Mouse(mazemap, route, x + vector_x[i], y + vector_y[i]);
			if (pan)
				return true;
		}
	}
	if (pan == false) {
		mazemap[x][y] = 0;
	}
	return pan;
}

void Wall_Follower(Mat& image, Set* set, int** mazeidx, int** mazemap, int pixel_ratio) {
	Stack* route = new Stack();
	std::cout << "----Wall Follower coordinate list----" << std::endl;

	route->push(1, 1);
	int dir_x = 1;
	int dir_y = 0;
	Wall_Follower(mazemap, route, 1, 1, dir_x, dir_y);
	std::cout << std::endl;

	int x1, y1;
	int x2, y2;
	int size = route->sizeis();
	for (int i = 0; i < size - 1; i++) {
		x1 = route->topx();
		y1 = route->topy();
		route->pop();
		x2 = route->topx();
		y2 = route->topy();
		line(image, cv::Point(y1*pixel_ratio / 2 - 5 * scale_factor, x1*pixel_ratio / 2 + 5 * scale_factor), cv::Point(y2*pixel_ratio / 2 - 5 * scale_factor, x2*pixel_ratio / 2 + 5 * scale_factor), Scalar(255, 0, 0));
		imshow("maze", image);
	}
	cv::putText(image, "Wall Follower", cv::Point(335, maze_size*pixel_ratio + 90), 2, 1, Scalar(255, 0, 0));
	imshow("maze", image);

	delete route;
}

bool Wall_Follower(int** mazemap, Stack* route, int x, int y, int dir_x, int dir_y) {
	int vector_x[4];
	int vector_y[4];
	std::cout << "(" << x << "," << y << ")";

	switch (dir_x) {
	case 1://s
		vector_x[0] = 0; vector_x[1] = 1; vector_x[2] = 0; vector_x[3] = -1; // w,s,e,n // vector_x[4] = { 0,1,0,-1 };
		vector_y[0] = -1; vector_y[1] = 0; vector_y[2] = 1; vector_y[3] = 0; // vector_y[4] = { -1,0,1,0 };
		break;
	case 0:
		if (dir_y == 1) {//e
			vector_x[0] = 1; vector_x[1] = 0; vector_x[2] = -1; vector_x[3] = 0; // s,e,n,w // vector_x[4] = { 1,0,-1,0 };
			vector_y[0] = 0; vector_y[1] = 1; vector_y[2] = 0; vector_y[3] = -1; // vector_y[4] = { 0,1,0,-1 };
		}
		else{//w
			vector_x[0] = -1; vector_x[1] = 0; vector_x[2] = 1; vector_x[3] = 0; // n,w,s,e // vector_x[4] = { -1,0,1,0 };
			vector_y[0] = 0; vector_y[1] = -1; vector_y[2] = 0; vector_y[3] = 1; // vector_y[4] = { 0,-1,0,1 };
		}
		break;
	case -1://n
		vector_x[0] = 0; vector_x[1] = -1; vector_x[2] = 0; vector_x[3] = 1; // e,n,w,s // vector_x[4] = { 0,-1,0,1 };
		vector_y[0] = 1; vector_y[1] = 0; vector_y[2] = -1; vector_y[3] = 0; // vector_y[4] = { 1,0,-1,0 };
		break;
	}
	bool pan = false;

	if (x == 2 * maze_size - 1 && y == 2 * maze_size - 1) {
		mazemap[x][y] = 1;
		pan = true;
	}

	mazemap[x][y] = 1;
	for (int i = 0; i < 4 && pan == false; i++) {
		if (mazemap[x + vector_x[i]][y + vector_y[i]] != 2) {
			route->push(x + vector_x[i], y + vector_y[i]);
			pan = Wall_Follower(mazemap, route, x + vector_x[i], y + vector_y[i], vector_x[i], vector_y[i]);
		}
	}
	if (pan == false) {
		mazemap[x][y] = 0;
	}
	return pan;
}

void BFS(Mat& image, Set* set, int** mazeidx, int** mazemap, int pixel_ratio) {
	Queue* route = new Queue();
	Prev** prev = new Prev*[2 * maze_size + 1];
	for (int i = 0; i < 2 * maze_size + 1; i++)
		prev[i] = new Prev[2 * maze_size + 1];

	route->push(1, 1);
	BFS(mazemap, route, prev);

	delete route;

	int x1, y1;
	int x2=0, y2=0;
	int size = route->sizeis();

	std::cout << "----BFS previous coordinate map----" << std::endl;
	for (int i = 0; i < 2 * maze_size + 1; i++) {
		for (int j = 0; j < 2 * maze_size + 1; j++) {
			std::cout << prev[i][j].getx() << "," << prev[i][j].gety() << " ";
		}
		std::cout << std::endl;
	}
	x1 = 2 * maze_size - 1;
	y1 = 2 * maze_size - 1;
	while (!(x2 == 1 && y2 == 1)) {
		x2 = prev[x1][y1].getx();
		y2 = prev[x1][y1].gety();
		std::cout << x1 << "," << y1 << std::endl;
		route->pop();
		line(image, cv::Point(y1*pixel_ratio / 2 + 10 * scale_factor, x1*pixel_ratio / 2 - 10 * scale_factor), cv::Point(y2*pixel_ratio / 2 + 10 * scale_factor, x2*pixel_ratio / 2 - 10 * scale_factor), Scalar(230, 68, 253));
		imshow("maze", image);
		x1 = x2;
		y1 = y2;
	}
	cv::putText(image, "BFS", cv::Point(10, maze_size*pixel_ratio + 140), 2, 1, Scalar(230, 68, 253));
	imshow("maze", image);

	for (int i = 0; i < 2 * maze_size + 1; i++)
		delete prev[i];
	delete[] prev;
}

void BFS(int** mazemap, Queue* route, Prev** prev) {
	int x, y;
	int vector_x[4] = { 0,1,0,-1 };
	int vector_y[4] = { 1,0,-1,0 };
	bool pan = false;
	
	while (!pan) {
		x = route->frontx();
		y = route->fronty();
		route->pop();
		if (x == 2 * maze_size - 1 && y == 2 * maze_size - 1) {
			mazemap[x][y] = 1;
			pan = true;
		}

		mazemap[x][y] = 1;
		for (int i = 0; i < 4; i++) {
			if (mazemap[x + vector_x[i]][y + vector_y[i]] == 0) {
				route->push(x + vector_x[i], y + vector_y[i]);
				prev[x + vector_x[i]][y + vector_y[i]].designate(x, y);
			}
		}
	}
}

