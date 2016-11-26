#include <opencv2\opencv.hpp>
#include "Set.h"
#include <iostream>

#define WINDOW_SIZE 600

using namespace std;
using namespace cv;

int maze_size;

int random_n();
void maze_builder(Mat& image, Node* maze, int** mazeidx);

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

	Node* maze = new Node[maze_size*maze_size];
	Set* set = new Set[maze_size*maze_size];

	int** mazeidx = new int*[maze_size];
	for (int i = 0; i < maze_size; i++)
		mazeidx[i] = new int[maze_size];
	
	for (int i = 0; i < maze_size; i++) {
		for (int j = 0; j < maze_size; j++) {
			mazeidx[i][j] = j + i*maze_size;
			set[j + i*maze_size].add(j + i*maze_size);
		}
	}
	set[0].union_set(set[1]);
	for (int i = 0; i < maze_size*maze_size; i++)
		set[i].print();
	
	char c;
	while (1) {
		c = cvWaitKey(30);
		if (c == 27) break;
		else if (c == 13) {
			cout << "ENTER" << endl;
		}
		else if (c == 32) {
			cout << "SPACE" << endl;
			maze_builder(image, maze, mazeidx);
		}
	}

	delete maze;
	delete set;
	for (int i = 0; i < maze_size; i++)
		delete mazeidx[i];
	delete mazeidx;
	return 0;
}

int random_n() { return rand() % (maze_size*maze_size); }

void maze_builder(Mat& image, Node* maze, int** mazeidx) {

}

