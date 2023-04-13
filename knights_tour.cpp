#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

bool isNumber(std::string boardSize)
{
    for (int i = 0; i < boardSize.length(); i++)
        if (isdigit(boardSize[i]) == false)
            return false;

    return true;
}

bool positionExists(std::vector<std::vector<std::string>> &vect, std::string position)
{
    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < vect.size(); j++)
        {
            if (position == vect.at(i).at(j))
            {
                return true;
            }
        }
    }
    return false;
}

bool isSafe(int x, int y, std::vector<std::vector<int>> vect, int boardSize)
{
    if (x >= 0 && x <= (boardSize - 1) && y >= 0 && y <= (boardSize - 1) && vect.at(x).at(y) == -1)
    {
        return true;
    }
    return false;
}

void initialBoardBuilding(int boardSize, std::vector<std::vector<int>> &vect)//Builds a board of 0s
{
    int maxRow = boardSize;

    for (int i = 0; i < boardSize; i++)
    {
        vect.push_back({});
    }
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            vect.at(i).push_back(-1);
        }
    }
}

void boardBuilding(int boardSize, std::vector<std::vector<std::string>> &vect)//Builds a board with names of fields on chessboard
{
    int charmax = 97;
    int maxRow = boardSize;
    for (int i = 0; i < boardSize; i++)
    {
        vect.push_back({});
    }

    for (int i = 0; i < boardSize; i++)
    {

        for (int j = 97; j < (charmax + boardSize); j++)
        {

            std::string pozycja;
            pozycja += char(j);
            pozycja += std::to_string(maxRow);
            vect.at(i).push_back(pozycja);
        }
        maxRow -= 1;
    }
}

bool findKnightsTour(std::vector<std::vector<int>> &vect, const int startingX, const int startingY, int endingX, int endingY, int boardSize, int stepCount)
{
    std::vector<int> xMoves = {-2, -1, 1, 2, 2, 1, -1, -2};
    std::vector<int> yMoves = {1, 2, 2, 1, -1, -2, -2, -1};

    int nextX = 0;
    int nextY = 0;

    if (startingX == endingX && startingY == endingY)
    {
        return true;
    }

    for (int i = 0; i < 8; i++)
    {
        nextX = startingX + xMoves.at(i);
        nextY = startingY + yMoves.at(i);

        if (isSafe(nextX, nextY, vect, boardSize))
        {
            vect.at(nextX).at(nextY) = stepCount;
            if (findKnightsTour(vect, nextX, nextY, endingX, endingY, boardSize, (stepCount + 1)))
            {
                return true;
            }
            vect.at(nextX).at(nextY) = -1;
        }
    }
    return false;
}//Fills the board consisting of 0s with the number of each step

void coordinateSearch(std::vector<std::vector<std::string>> &vect, std::string &searchedValue, int &xValue, int &yValue)
{
    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < vect.size(); j++)
        {
            if (searchedValue == vect.at(i).at(j))
            {
                xValue = i;
                yValue = j;
            }
        }
    }
}//Transforms a name of the field to it's vector index(a1 to 0,0)

void printResults(std::vector<std::vector<int>> initialBoard, std::vector<std::vector<std::string>> board, int boardSize)
{
    for (int k = 1; k <= (boardSize * boardSize); k++)
    {
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if (k == initialBoard.at(i).at(j))
                {
                    std::cout << board.at(i).at(j) << " ";
                }
            }
        }
    }
    std::cout << std::endl;
}//For each step number, compares vectors' indexes to print name of the field on the chessboard

int main(int argc, char *argv[])
{
    try
    {

        if (argc != 4 || !isNumber(argv[1]))
        {
            throw std::runtime_error("invalid parameter list");
        }

        std::vector<std::vector<int>> initialBoard;
        std::vector<std::vector<std::string>> board;
        int startX = -1, startY = -1, endX = -1, endY = -1, stepcount = 2, boardSize = 0;
        std::string startPosition = argv[2], endPosition = argv[3];
        std::stringstream str(argv[1]);
        str >> boardSize;

        if (boardSize < 1 || boardSize > 26)
        {
            throw std::runtime_error("invalid parameter list");
        }

        initialBoardBuilding(boardSize, initialBoard);

        boardBuilding(boardSize, board);

        if (positionExists(board, startPosition) && positionExists(board, endPosition))
        {
            coordinateSearch(board, startPosition, startX, startY);
            coordinateSearch(board, endPosition, endX, endY);
        }

        else
        {
            throw std::runtime_error("invalid parameter list");
        }

        initialBoard.at(startX).at(startY) = 1;

        if (!findKnightsTour(initialBoard, startX, startY, endX, endY, boardSize, stepcount))
        {
            throw std::runtime_error("could not find a knight's tour");
        }

        printResults(initialBoard, board, boardSize);
    }

    catch (std::runtime_error &except)
    {
        std::cout << except.what() << std::endl;
    }
    return 0;
}
