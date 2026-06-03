#include<iostream>
using namespace std;
class Player
{
    public:
    char symbol;
    string name;
    Player(string n, char s)
    {
        name = n;
        symbol = s;
    }
};
class Board
{
    private:
    char grid[3][3];

    public:
    Board()
    {
        int num = 1;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                grid[i][j] = num;
                num++;
            }
        }
    }
    void display()
    {
         cout << "\n+---+---+---+\n";

        for(int i = 0; i < 3; i++)
        {
            cout << "| ";

            for(int j = 0; j < 3; j++)
            {
                cout << grid[i][j] << " | ";
            }

            cout << "\n+---+---+---+\n";
        }
    }
    bool makeMove(int move, char symbol)
    {
        int row = (move - 1) / 3;
        int col = (move - 1) % 3;

        if(grid[row][col] != 'X' && grid[row][col] != 'O')
        {
            grid[row][col] = symbol;
            return true;
        }

        return false;
    }
    bool isFull()
    {

    }
    bool checkWin(char symbol);
    void reset();
};
class Game
{
    private:
    Board board;
    char currentPlayer;

    public:
    Game()
    {
        currentPlayer = 'X';
    }
    void switchTurn()
    {
        if(currentPlayer == 'X')
            currentPlayer = 'O';
        else
            currentPlayer = 'X';
    }
    void play();
};