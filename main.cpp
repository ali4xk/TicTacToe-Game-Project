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
    Board();
    void display();
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
