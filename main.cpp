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
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(grid[i][j] != 'X' && grid[i][j] != 'O')
                return false;
            }
        }
        return true;
    }
    bool checkWin(char symbol)
    {
        for(int i = 0; i < 3; i++)
        {
            if(grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol)
            return true;
        }
        for(int j = 0; j < 3; j++)
        {
            if(grid[0][j] == symbol && grid[1][j] == symbol && grid[2][j] == symbol)
            return true;
        }
        if(grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol)
        return true;

        if(grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol)
        return true;

        return false;
    }
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
    void play()
    {
        int move;

        while(true)
        {
            board.display();

            cout << "Player " << currentPlayer << ", enter move (1-9): ";
            cin >> move;

            if(move < 1 || move > 9)
            {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            if(board.makeMove(move, currentPlayer))
            {
                switchTurn();
            }
            else
            {
                cout << "Cell already occupied! Try again.\n";
            }
        }
    }
};