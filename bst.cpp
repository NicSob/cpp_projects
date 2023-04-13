#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include <sstream>
#include"bst.h"

class Grid
{
public:
    void gridCreator(int height, int elements, std::vector<std::vector<std::string>>& grid);
    void gridPrinter(std::vector<std::vector<std::string>> grid, int elements);
    void gridModifier(std::vector<std::vector<std::string>>& grid, int height, int elements, std::vector<int> values, std::vector<int> valueDepth, std::vector<int> valueIndex);
};

void Grid::gridCreator(int height, int elements, std::vector<std::vector<std::string>>& grid)
{
    for(int i = 0; i < height; i++)
    {
        grid.push_back({});
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (elements * 2) + 1; j++)
        {
            grid.at(i).push_back("    ");
            if(j % 2 == 0)
            {
            grid.at(i).at(j) = "|";
            }
        }
    }
}

void Grid::gridPrinter(std::vector<std::vector<std::string>> grid, int elements)
{
    std::cout << std::setfill('-') << std::setw((elements*4) + (elements + 1)) << "" << std::endl;
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid.at(0).size(); j++)
        {
            if(j % 2 == 1){
                std::cout << std::setfill(' ') << std::setw(4) << grid.at(i).at(j);
            }
            else{
                std::cout << grid.at(i).at(j);
            }
        }
        std::cout << std::endl << std::setfill('-') << std::setw((elements*4) + (elements + 1)) << "" << std::endl;
    }
}

void Grid::gridModifier(std::vector<std::vector<std::string>>& grid, int height, int elements, std::vector<int> values, std::vector<int> valueDepth, std::vector<int> valueIndex)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (elements * 2) + 1; j++)
        {
            for(int k = 0; k < values.size(); k++)
            {
                if(i == valueDepth.at(k) && j == ((valueIndex.at(k) * 2) + 1))
                {
                    grid.at(i).at(j) = std::to_string(values.at(k));
                }
            }
        }
    }
}

int main()
{
    int elements, height, data;
    BST tree;
    BST *root = nullptr;
    Grid grid;
    std::istringstream inSS;
    std::string lineString; 

    std::vector<std::vector<std::string>> mainGrid;
    
    std::vector<int> values;

    std::cout << "Enter the numbers to be stored: ";
    std::getline(std::cin, lineString);
    inSS.str(lineString);

    while(inSS >> data){
        values.push_back(data);
    }

    if(values.size() > 0)
    {
        root = tree.insertKey(root, values.at(0));

        for(int i = 1; i < values.size(); i++)
        {
            tree.insertKey(root, values.at(i));
        }
    }

    elements = values.size();
    std::vector<int> ordered;
    std::vector<int> valueIndex(elements);
    std::vector<int> valueDepth(elements);
    
    for(int i = 0; i < values.size(); i++)
    {
        valueDepth.at(i) = tree.getDepth(root, values.at(i));
    }  

    height = tree.getHeight(root);
    grid.gridCreator(height, elements, mainGrid);
    tree.inorder(root, ordered);

    for(int i = 0; i < values.size(); i++)
    {
        for(int j = 0; j < values.size(); j++)
        {
            if(values.at(i) == ordered.at(j))
            {
                valueIndex.at(i) = j;
            }
        }    
    } 

    std::cout << std::endl << "The numbers in sorted order: ";
    for(int i = 0; i < ordered.size(); i++)
    {
        std::cout << ordered.at(i) << " ";
    }
    
    grid.gridModifier(mainGrid, height, elements, values, valueDepth, valueIndex);

    std::cout << std::endl;
    if(values.size() > 0)
    {
        grid.gridPrinter(mainGrid, elements);
    }

    delete root;

    return 0;
}
