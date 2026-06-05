#include <SFML/Graphics.hpp>
#include <iostream>

const int WINDOW_SIZE = 600;
const int GRID_SIZE = 3;
const float CELL_SIZE = WINDOW_SIZE / GRID_SIZE;

class Game
{
private:
    sf::RenderWindow window;
    sf::Font font;

    char board[3][3];
    bool isXTurn = true;

    bool gameOver = false;
    char winner = ' ';

public:
    Game();
    void run();
    void handleEvents();
    void render();
    bool checkWin(char p);
};

Game::Game()
    : window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "Tic Tac Toe")
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';

    if (!font.openFromFile("arial.ttf"))
        std::cout << "Font failed to load!" << std::endl;
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();

        window.clear(sf::Color(245, 245, 245));
        render();
        window.display();
    }
}

void Game::handleEvents()
{
    while (auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (gameOver)
            continue;

        if (event->is<sf::Event::MouseButtonPressed>())
        {
            auto mousePos = sf::Mouse::getPosition(window);

            int col = mousePos.x / CELL_SIZE;
            int row = mousePos.y / CELL_SIZE;

            if (row >= 0 && row < 3 && col >= 0 && col < 3)
            {
                if (board[row][col] == ' ')
                {
                    board[row][col] = (isXTurn ? 'X' : 'O');
                    isXTurn = !isXTurn;

                    if (checkWin('X'))
                    {
                        gameOver = true;
                        winner = 'X';
                    }
                    else if (checkWin('O'))
                    {
                        gameOver = true;
                        winner = 'O';
                    }
                }
            }
        }
    }
}

bool Game::checkWin(char p)
{
    // rows
    for (int i = 0; i < 3; i++)
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p)
            return true;

    // columns
    for (int i = 0; i < 3; i++)
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p)
            return true;

    // diagonals
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p)
        return true;

    if (board[0][2] == p && board[1][1] == p && board[2][0] == p)
        return true;

    return false;
}

void Game::render()
{
    // GRID
    sf::RectangleShape line;
    line.setFillColor(sf::Color::Black);

    float thickness = 6.f;

    for (int i = 1; i < GRID_SIZE; i++)
    {
        line.setSize(sf::Vector2f(thickness, WINDOW_SIZE));
        line.setPosition(sf::Vector2f(i * CELL_SIZE, 0.f));
        window.draw(line);
    }

    for (int i = 1; i < GRID_SIZE; i++)
    {
        line.setSize(sf::Vector2f(WINDOW_SIZE, thickness));
        line.setPosition(sf::Vector2f(0.f, i * CELL_SIZE));
        window.draw(line);
    }

    // X & O
    sf::Text text(font, "", 80);
    text.setFillColor(sf::Color::Black);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                text.setString(board[i][j]);

                text.setPosition(sf::Vector2f(
                    j * CELL_SIZE + 70.f,
                    i * CELL_SIZE + 40.f));

                window.draw(text);
            }
        }
    }

    // WIN MESSAGE
    if (gameOver)
    {
        sf::Text msg(font, "", 50);
        msg.setFillColor(sf::Color::Red);

        if (winner == 'X')
            msg.setString("X Wins!");
        else if (winner == 'O')
            msg.setString("O Wins!");

        msg.setPosition(sf::Vector2f(200.f, 250.f));
        window.draw(msg);
    }
}

int main()
{
    Game game;
    game.run();
    return 0;
}