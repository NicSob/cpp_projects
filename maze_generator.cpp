#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <time.h>
#include <stdlib.h>

class Cell
{
public:
    void SetCell(std::string a) { cell = a; }
    void PrintCell() { std::cout << cell; }
    std::string returnCell() { return cell; }

private:
    std::string cell;
};

class Maze
{
public:
    void gridGenerator(std::vector<std::vector<Cell>> &maze, int rows, int columns);

    void mazePrinter(std::vector<std::vector<Cell>> maze, int rows, int columns) const;

    void wallDemolisher(std::vector<std::vector<Cell>> &maze, int i, int j);

    bool inBoundaries(int rows, int columns, int i, int j);

    void optionsForNextMove(std::vector<std::vector<Cell>> maze, int rows, int columns, int i, int j, std::vector<int> &possibleVerticalMove, std::vector<int> &possibleHorizontalMove);

    void mazeGenerator(std::vector<std::vector<Cell>> &maze, int rows, int columns, int i, int j, int seed);

    void dotCleaner(std::vector<std::vector<Cell>> &maze, int rows, int columns);

    bool pathFinder(std::vector<std::vector<Cell>> &maze, int rows, int columns, int startX, int startY, int endX, int endY);

    void neighbouringCells(std::vector<std::vector<Cell>> maze, int rows, int columns, int j, int k, std::vector<int> &neighbouringVerticalMove, std::vector<int> &neighbouringHorizontalMove);
};

void Maze::gridGenerator(std::vector<std::vector<Cell>> &maze, int rows, int columns)
{
    Cell empty;
    empty.SetCell("   ");
    std::string corner = "+", horizontalWall = "---", verticalWall = "|";

    for (int i = 0; i < (rows * 2) + 1; i++)
    {
        maze.push_back({});
    }

    for (int i = 0; i < (rows * 2) + 1; i++)
    {
        for (int j = 0; j < (columns * 2) + 1; j++)
        {
            maze.at(i).push_back(empty);
        }
    }

    for (int i = 0; i < (rows * 2) + 1; i++)
    {
        for (int j = 0; j < (columns * 2) + 1; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
            {
                maze.at(i).at(j).SetCell(corner);
            }
            else if (i % 2 == 0)
            {
                maze.at(i).at(j).SetCell(horizontalWall);
            }
            else if (i % 2 == 1 && j % 2 == 0)
            {
                maze.at(i).at(j).SetCell(verticalWall);
            }
        }
    }
}

void Maze::mazePrinter(std::vector<std::vector<Cell>> maze, int rows, int columns) const
{
    for (int i = 0; i < (rows * 2) + 1; i++)
    {
        for (int j = 0; j < (columns * 2) + 1; j++)
        {
            maze.at(i).at(j).PrintCell();
        }
        std::cout << std::endl;
    }
}

void Maze::wallDemolisher(std::vector<std::vector<Cell>> &maze, int i, int j)
{
    if (maze.at(i).at(j).returnCell() == "|")
    {
        maze.at(i).at(j).SetCell(" ");
    }
    else if (maze.at(i).at(j).returnCell() == "---")
    {
        maze.at(i).at(j).SetCell("   ");
    }
}

bool Maze::inBoundaries(int rows, int columns, int i, int j)
{
    if (i > 0 && i < (rows * 2) + 1)
    {
        if (j > 0 && j < (columns * 2) + 1)
        {
            return true;
        }
    }
    return false;
}

void Maze::optionsForNextMove(std::vector<std::vector<Cell>> maze, int rows, int columns, int j, int k, std::vector<int> &possibleVerticalMove, std::vector<int> &possibleHorizontalMove)
{
    std::vector<int> verticalMoves = {-2, 2, 0, 0};
    std::vector<int> horizontalMoves = {0, 0, 2, -2};

    for (int i = 0; i < verticalMoves.size(); i++)
    {
        if (inBoundaries(rows, columns, j + verticalMoves.at(i), k + horizontalMoves.at(i)))
        {
            if (maze.at(j + verticalMoves.at(i)).at(k + horizontalMoves.at(i)).returnCell() == "   ")
            {
                possibleVerticalMove.push_back(verticalMoves.at(i));
                possibleHorizontalMove.push_back(horizontalMoves.at(i));
            }
        }
    }
}

void Maze::mazeGenerator(std::vector<std::vector<Cell>> &maze, int rows, int columns, int startX, int startY, int seed)
{
    std::stack<int> stack;

    srand(seed);

    maze.at(startX).at(startY).SetCell(" . ");
    stack.push(startX);
    stack.push(startY);

    while (stack.size() > 0)
    {
        int currY = stack.top();
        stack.pop();
        int currX = stack.top();
        stack.pop();

        std::vector<int> possibleVerticalMove;
        std::vector<int> possibleHorizontalMove;

        optionsForNextMove(maze, rows, columns, currX, currY, possibleVerticalMove, possibleHorizontalMove);

        if (possibleVerticalMove.size() > 0)
        {
            stack.push(currX);
            stack.push(currY);

            int randomIndex = rand() % (possibleVerticalMove.size());

            int nextX = currX + possibleVerticalMove.at(randomIndex);
            int nextY = currY + possibleHorizontalMove.at(randomIndex);

            wallDemolisher(maze, currX + (possibleVerticalMove.at(randomIndex) / 2), currY + (possibleHorizontalMove.at(randomIndex) / 2));

            maze.at(nextX).at(nextY).SetCell(" . ");

            stack.push(nextX);
            stack.push(nextY);
        }
    }
    dotCleaner(maze, rows, columns);
}

void Maze::dotCleaner(std::vector<std::vector<Cell>> &maze, int rows, int columns)
{
    std::string empty = "   ";
    for (int i = 0; i < (rows * 2); i++)
    {
        for (int j = 0; j < (columns * 2); j++)
        {
            if (maze.at(i).at(j).returnCell() == " . ")
            {
                maze.at(i).at(j).SetCell(empty);
            }
        }
    }
}

void Maze::neighbouringCells(std::vector<std::vector<Cell>> maze, int rows, int columns, int j, int k, std::vector<int> &neighbouringVerticalMove, std::vector<int> &neighbouringHorizontalMove)
{
    std::vector<int> possibleVerticalMove;
    std::vector<int> possibleHorizontalMove;

    optionsForNextMove(maze, rows, columns, j, k, possibleVerticalMove, possibleHorizontalMove);

    for (int i = 0; i < possibleVerticalMove.size(); i++)
    {
        if (maze.at(j + (possibleVerticalMove.at(i) / 2)).at(k + (possibleHorizontalMove.at(i) / 2)).returnCell() != "|" &&
            maze.at(j + (possibleVerticalMove.at(i) / 2)).at(k + (possibleHorizontalMove.at(i) / 2)).returnCell() != "---")
        {
            neighbouringVerticalMove.push_back(j + possibleVerticalMove.at(i));
            neighbouringHorizontalMove.push_back(k + possibleHorizontalMove.at(i));
        }
    }
}

bool Maze::pathFinder(std::vector<std::vector<Cell>> &maze, int rows, int columns, int startX, int startY, int endX, int endY)
{
    maze.at(startX).at(startY).SetCell(" . ");

    std::vector<int> neighbouringVerticalMove;
    std::vector<int> neighbouringHorizontalMove;

    neighbouringCells(maze, rows, columns, startX, startY, neighbouringVerticalMove, neighbouringHorizontalMove);

    if (startX == endX && startY == endY)
    {
        return true;
    }
    for (int i = 0; i < neighbouringVerticalMove.size(); i++)
    {
        if (maze.at(neighbouringVerticalMove.at(i)).at(neighbouringHorizontalMove.at(i)).returnCell() == "   ")
        {
            if (pathFinder(maze, rows, columns, neighbouringVerticalMove.at(i), neighbouringHorizontalMove.at(i), endX, endY))
            {
                return true;
            }
        }
    }
    maze.at(startX).at(startY).SetCell("   ");
    return false;
}

int main(int argc, char *argv[])
{
    try
    {
        std::vector<std::vector<Cell>> maze;
        int randomSeed = time(0);
        
        if (argc == 4)
        {
            randomSeed = std::stoi(argv[3]);
        }

        else if (argc != 3 && argc != 4)
        {
            throw std::runtime_error("invalid parameter list");
        }

        int rows = std::stoi(argv[1]), columns = std::stoi(argv[2]), endX = (rows * 2) - 1, endY = (columns * 2) - 1;

        

        Maze mainMaze;

        mainMaze.gridGenerator(maze, rows, columns);
        mainMaze.mazeGenerator(maze, rows, columns, 1, 1, randomSeed);
        mainMaze.pathFinder(maze, rows, columns, 1, 1, endX, endY);
        mainMaze.mazePrinter(maze, rows, columns);
    }

    catch (std::runtime_error &except)
    {
        std::cout << except.what() << std::endl;
    }

    return 0;
}
