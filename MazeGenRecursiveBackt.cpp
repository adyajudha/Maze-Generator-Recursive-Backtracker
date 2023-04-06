#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAZE_SIZE = 10;

class MazeGenerator
{
private:
    int maze[MAZE_SIZE][MAZE_SIZE];
    int width, height;

public:
    MazeGenerator(int w, int h) : width(w), height(h)
    {
        // Initialize maze with all walls
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                maze[i][j] = 1;
            }
        }
        generateMaze(0, 0);
    }

    void generateMaze(int row, int col)
    {
        maze[row][col] = 0;
        vector<int> neighbors = getNeighbors(row, col);
        while (!neighbors.empty())
        {
            int randomIndex = rand() % neighbors.size();
            int nRow = neighbors[randomIndex] / width;
            int nCol = neighbors[randomIndex] % width;
            neighbors.erase(neighbors.begin() + randomIndex);
            if (maze[nRow][nCol] == 1)
            {
                maze[(nRow + row) / 2][(nCol + col) / 2] = 0;
                generateMaze(nRow, nCol);
            }
        }
    }

    vector<int> getNeighbors(int row, int col)
    {
        vector<int> neighbors;
        if (row - 2 >= 0 && maze[row - 2][col] == 1)
        {
            neighbors.push_back((row - 2) * width + col);
        }
        if (col - 2 >= 0 && maze[row][col - 2] == 1)
        {
            neighbors.push_back(row * width + col - 2);
        }
        if (row + 2 < height && maze[row + 2][col] == 1)
        {
            neighbors.push_back((row + 2) * width + col);
        }
        if (col + 2 < width && maze[row][col + 2] == 1)
        {
            neighbors.push_back(row * width + col + 2);
        }
        return neighbors;
    }

    void printMaze()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (maze[i][j] == 1)
                {
                    cout << "# ";
                }
                else
                {
                    cout << "  ";
                }
            }
            cout << endl;
        }
    }
};

int main()
{
    srand(time(nullptr));
    MazeGenerator maze(MAZE_SIZE, MAZE_SIZE);
    maze.printMaze();
    return 0;
}
