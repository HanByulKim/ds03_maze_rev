#include <opencv2\opencv.hpp>
#include "Set.h"
#include "Stack.h"
#include <iostream>

#define WINDOW_SIZE 600

using namespace std;
using namespace cv;

int maze_size;

int random_n();
void maze_builder(Mat& image, Set* set, Node* maze, int** mazeidx, int** mazemap, int pixel_ratio);
void DFS(Mat& image, Set* set, Node* maze, int** mazeidx, int** mazemap, int pixel_ratio);

int main(int argc, char **argv)
{
	cout << "Eneter the size of maze(n by n): ";
	cin >> maze_size;
	int pixel_ratio = 600 / maze_size;
	Mat WhiteImage(maze_size*pixel_ratio, maze_size*pixel_ratio, CV_8UC3, Scalar(255, 255, 255));
	Mat image = WhiteImage.clone();	
	
	for (int i = 0; i < maze_size; i++) {
		for (int j = 0; j < maze_size - 1; j++) {			
			Point p1((j+1)*pixel_ratio, i*pixel_ratio);
			Point p2((j+1)*pixel_ratio, (i+1)*pixel_ratio -1);
			Point p3(i*pixel_ratio, (j+1)*pixel_ratio);
			Point p4((i + 1)*pixel_ratio-1, (j + 1)*pixel_ratio);

			line(image, p1, p2, Scalar(0, 0, 0));
			line(image, p3, p4, Scalar(0, 0, 0));
		}		
	}
	imshow("maze", image);

	Node* maze = new Node[maze_size*maze_size]; // node
	Set* set = new Set[maze_size*maze_size]; // set

	int** mazeidx = new int*[maze_size]; // index arr
	int** mazemap = new int*[2 * maze_size + 1]; // real maze
	for (int i = 0; i < maze_size; i++)
		mazeidx[i] = new int[maze_size];
	for (int i = 0; i < 2*maze_size+1; i++)
		mazemap[i] = new int[2*maze_size+1];
	
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
			//std::cout << mazemap[i][j] << " ";
		}
		//std::cout << std::endl;
	}
	//set[0].union_set(set[1]);
	//for (int i = 0; i < maze_size*maze_size; i++)
	//	set[i].print();
	
	char c;
	int cnt = 0;
	while (1) {
		c = cvWaitKey(30);
		if (c == 27) break;
		else if (c == 13) {
			cout << "ENTER" << endl;
		}
		else if (c == 32) {
			cout << "SPACE" << endl;
			if (cnt++ == 0) {
				maze_builder(image, set, maze, mazeidx, mazemap, pixel_ratio);
			}
			else if (cnt++ == 1) {
				DFS(image, set, maze, mazeidx, mazemap, pixel_ratio);
			}
		}
	}


	delete maze;
	delete set;
	for (int i = 0; i < maze_size; i++)
		delete mazeidx[i];
	delete mazeidx;
	for (int i = 0; i < 2*maze_size+1; i++)
		delete mazemap[i];
	delete mazemap;
	return 0;
}

int random_n() { return rand() % (maze_size*maze_size); }
int random_vec() { return rand() % 4; }

void maze_builder(Mat& image, Set* set, Node* maze, int** mazeidx, int** mazemap, int pixel_ratio) {
	int target=0;
	int arr;
	int vector;
	int xtemp, ytemp;
	bool condition;
	int working = 0;

	while (set[target].size != maze_size*maze_size) {
		system("cls");
		if (working == 0) std::cout << "working \ " << std::endl;
		else if (working == 1) std::cout << "working | "<<std::endl;
		else if (working == 2) std::cout << "working / "<<std::endl;
		else { std::cout << "working - " << std::endl; }
		working++;

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
	for (int i = 0; i < maze_size; i++) {
		for (int j = 0; j < maze_size-1; j++) {
			if (i == 0 || j == 0) {
				if (mazemap[(2 * (i % maze_size) + 1)][(2 * (j % maze_size) + 2)] == 0) // vertical line
					line(image, cv::Point(pixel_ratio*(j + 1), pixel_ratio*i), cv::Point(pixel_ratio*(j + 1), pixel_ratio*i + pixel_ratio - 1), Scalar(255, 255, 255));
				if (mazemap[(2 * (j % maze_size) + 2)][(2 * (i % maze_size) + 1)] == 0) // horizontal line
					line(image, cv::Point(pixel_ratio*i, pixel_ratio*(j + 1)), cv::Point(pixel_ratio*i + pixel_ratio, pixel_ratio*(j + 1)), Scalar(255, 255, 255));
			}
			else {
				if (mazemap[(2 * (i % maze_size) + 1)][(2 * (j % maze_size) + 2)] == 0) // vertical line
					line(image, cv::Point(pixel_ratio*(j + 1), pixel_ratio*i + 1), cv::Point(pixel_ratio*(j + 1), pixel_ratio*i + pixel_ratio - 1), Scalar(255, 255, 255));
				if (mazemap[(2 * (j % maze_size) + 2)][(2 * (i % maze_size) + 1)] == 0) // horizontal line
					line(image, cv::Point(pixel_ratio*i + 1, pixel_ratio*(j + 1)), cv::Point(pixel_ratio*i + pixel_ratio - 1, pixel_ratio*(j + 1)), Scalar(255, 255, 255));
			}
		}
	}
	

	imshow("maze", image);
}

void DFS(Mat& image, Set* set, Node* maze, int** mazeidx, int** mazemap, int pixel_ratio) {
	int vector_x[4] = {0,1,0,-1};
	int vector_y[4] = {1,0,-1,0};
	Stack route();

	while (1) {

	}
}

