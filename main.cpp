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
        cout << "\n";
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << "\n";
    }
    bool makeMove(int row, int col, char symbol);
    bool isFull();
    bool checkWin(char symbol);
    void reset();
};
class Game
{
    private:
    Board board;
    Player p1, p2;
    Player* currentPlayer;

    public:
    Game();
    void switchTurn();
    void play();
};
