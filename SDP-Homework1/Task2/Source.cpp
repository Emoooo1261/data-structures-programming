#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Point {
	int x;
	int y;
};

bool isValidCoord(int n, int x) {
	return x < n && x >= 0; //if its on the grid
}

int getMinimumMoves(char** grid, int startX, int startY, int endX, int endY) {
	if (startX == endX && startY == endY) {
		return 0;
	}
	int gridSize = strlen(grid[0]);
	int** steps = new int*[gridSize]; //stores number of steps needed to get to that point
	bool** visited = new bool*[gridSize]; //stores if a point was visited

	for (int i = 0; i < gridSize; ++i) {
		steps[i] = new int[gridSize];
		visited[i] = new bool[gridSize];
		for (int j = 0; j < gridSize; ++j) {
			visited[i][j] = 0;	//in the beginning there are no visited points
			if (grid[i][j] == '.')
				steps[i][j] = 0; //default steps to every available point is 0
			else {
				steps[i][j] = -2; //unless its blocked
			}
		}
	}

	queue<Point> move; //queue that will store every point thats been visited
	Point start;
	start.x = startX;
	start.y = startY;
	visited[startX][startY] = 1;
	move.push(start); //push the starting point into the queue

	while (!move.empty()) { //while there are points in the queue
		Point curr = move.front(); //starting from some point, it will push every possible point that can be visited from this one

		//trying to visit every possible, not visited, not blocked, point increasing the x coord
		while (isValidCoord(gridSize, curr.x + 1) && steps[curr.x + 1][curr.y] != -2 && visited[curr.x + 1][curr.y] == false) {
			curr.x += 1;
			steps[curr.x][curr.y] += steps[move.front().x][move.front().y] + 1; //increase the steps from the previous point + 1
			visited[curr.x][curr.y] = true; //it gets visited
			if (curr.x == endX && curr.y == endY) { //if its the end point returns the steps
				return steps[curr.x][curr.y];
			}
			move.push(curr); //gets pushed in the queue
		}
		curr = move.front();
		//same thing but decreasing x coord
		while (isValidCoord(gridSize, curr.x - 1) && steps[curr.x - 1][curr.y] != -2 && visited[curr.x - 1][curr.y] == false) {
			curr.x -= 1;
			steps[curr.x][curr.y] += steps[move.front().x][move.front().y] + 1;
			visited[curr.x][curr.y] = true;
			if (curr.x == endX && curr.y == endY) {
				return steps[curr.x][curr.y];
			}
			move.push(curr);
		}
		curr = move.front();
		//same thing increasing y coord
		while (isValidCoord(gridSize, curr.y + 1) && steps[curr.x][curr.y + 1] != -2 && visited[curr.x][curr.y + 1] == false) {
			curr.y += 1;
			steps[curr.x][curr.y] += steps[move.front().x][move.front().y] + 1;
			visited[curr.x][curr.y] = true;
			if (curr.x == endX && curr.y == endY) {
				return steps[curr.x][curr.y];
			}
			move.push(curr);
		}
		curr = move.front();
		//same thing decreasing x coord
		while (isValidCoord(gridSize, curr.y - 1) && steps[curr.x][curr.y - 1] != -2 && visited[curr.x][curr.y - 1] == false) {
			curr.y -= 1;
			steps[curr.x][curr.y] += steps[move.front().x][move.front().y] + 1;
			visited[curr.x][curr.y] = true;
			if (curr.x == endX && curr.y == endY) {
				return steps[curr.x][curr.y];
			}
			move.push(curr);
		}
		move.pop(); //after it pushes every possible point it pops this one
	}
	return steps[endX][endY];
}

int main() {
	int n;
	char** grid;
	int startX = 0, startY = 0, endX = 0, endY = 0;
	cin >> n;

	grid = new char*[n];
	for (int i = 0; i < n; ++i) {
		grid[i] = new char[n];
		cin >> grid[i];
	}

	cin >> startX;
	cin >> startY;
	cin >> endX;
	cin >> endY;

	cout << getMinimumMoves(grid, startX, startY, endX, endY) << endl;

	return 0;
}