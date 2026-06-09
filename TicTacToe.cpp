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
    sf::Vector2f winStart;
    sf::Vector2f winEnd;
    bool hasWinLine = false;
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
    void resetGame()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';

        isXTurn = true;
        gameOver = false;
        winner = ' ';
        hasWinLine = false;
    }
    bool checkDraw()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ')
                    return false;

        return true;
    }
};
enum GameState
{
    MENU,
    PLAYING,
    GAMEOVER
};
GameState state = MENU;
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

        window.clear(sf::Color(15, 15, 35));
        render();
        window.display();
    }
}

void Game::handleEvents()
{
    while (auto event = window.pollEvent())
    {
        if (state == MENU)
        {
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                state = PLAYING;
            }
            return;
        }
        if (event->is<sf::Event::Closed>())
            window.close();
        if (event->is<sf::Event::KeyPressed>())
        {
            auto keyEvent = event->getIf<sf::Event::KeyPressed>();

            if (keyEvent && keyEvent->code == sf::Keyboard::Key::R)
            {
                resetGame();
            }
        }
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
                    else if (checkDraw())
                    {
                        gameOver = true;
                        winner = 'D'; // D = Draw
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
    {
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p)
        {
            winStart = sf::Vector2f(0.f, i * CELL_SIZE + CELL_SIZE / 2);
            winEnd   = sf::Vector2f(WINDOW_SIZE, i * CELL_SIZE + CELL_SIZE / 2);
            hasWinLine = true;
            return true;
        }
    }

    // columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p)
        {
            winStart = sf::Vector2f(i * CELL_SIZE + CELL_SIZE / 2, 0.f);
            winEnd   = sf::Vector2f(i * CELL_SIZE + CELL_SIZE / 2, WINDOW_SIZE);
            hasWinLine = true;
            return true;
        }
    }

    // diagonal top-left -> bottom-right
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p)
    {
        winStart = sf::Vector2f(0.f, 0.f);
        winEnd   = sf::Vector2f(WINDOW_SIZE, WINDOW_SIZE);
        hasWinLine = true;
        return true;
    }

    // diagonal top-right -> bottom-left
    if (board[0][2] == p && board[1][1] == p && board[2][0] == p)
    {
        winStart = sf::Vector2f(WINDOW_SIZE, 0.f);
        winEnd   = sf::Vector2f(0.f, WINDOW_SIZE);
        hasWinLine = true;
        return true;
    }

    return false;
}

void Game::render()
{
    if (state == MENU)
    {
        sf::Text title(font, "TIC TAC TOE", 60);
        title.setFillColor(sf::Color(215, 215, 0));
        title.setPosition(sf::Vector2f(120.f, 150.f));
        window.draw(title);

        sf::Text start(font, "Click Anywhere to Start", 30);
        start.setFillColor(sf::Color(0, 255, 100));
        start.setPosition(sf::Vector2f(150.f, 300.f));
        window.draw(start);

        return;
    }
    auto mousePos = sf::Mouse::getPosition(window);

    int hoverCol = mousePos.x / CELL_SIZE;
    int hoverRow = mousePos.y / CELL_SIZE;
    if (hoverRow >= 0 && hoverRow < 3 && hoverCol >= 0 && hoverCol < 3 && !gameOver)
    {
        sf::RectangleShape hoverBox;

        hoverBox.setSize(
            sf::Vector2f(CELL_SIZE - 4.f,
                        CELL_SIZE - 4.f));

        hoverBox.setPosition(
            sf::Vector2f(
                hoverCol * CELL_SIZE + 2.f,
                hoverRow * CELL_SIZE + 2.f));

        hoverBox.setFillColor(
            sf::Color(0, 255, 255, 40));

        window.draw(hoverBox);
    }
    // GRID
    sf::RectangleShape line;
    line.setFillColor(sf::Color(0, 255, 255));

    float thickness = 8.f;

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
    sf::Text text(font, "", 100);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                text.setString(board[i][j]);

                if (board[i][j] == 'X')
                    text.setFillColor(sf::Color(255, 80, 80));
                else
                    text.setFillColor(sf::Color(255, 220, 0));

                text.setPosition(sf::Vector2f(
                    j * CELL_SIZE + CELL_SIZE / 3.f,
                    i * CELL_SIZE + CELL_SIZE / 5.f));

                window.draw(text);
            }
        }
    }
    if (gameOver && hasWinLine)
    {
        sf::RectangleShape line;

        sf::Vector2f direction = winEnd - winStart;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        line.setSize(sf::Vector2f(length, 8.f));
        line.setPosition(winStart);

        float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
        line.setRotation(sf::degrees(angle));

        line.setFillColor(sf::Color(215, 215, 0));

        window.draw(line);
    }
    if (gameOver)
    {
        sf::RectangleShape overlay;
        overlay.setSize(sf::Vector2f(WINDOW_SIZE, WINDOW_SIZE));
        overlay.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(overlay);
        sf::Text msg(font, "", 40);
        msg.setFillColor(sf::Color(0, 255, 100));

        if (winner == 'X')
            msg.setString("PLAYER X WINS!");
        else if (winner == 'O')
            msg.setString("PLAYER O WINS!");
        else if (winner == 'D')
            msg.setString("GAME DRAW!");
        msg.setPosition(sf::Vector2f(100.f, 250.f));
        if (winner == 'D')
        msg.setFillColor(sf::Color(255, 200, 0));   // yellow for draw
        else
        msg.setFillColor(sf::Color(0, 255, 100));   // green for win
        window.draw(msg);

        sf::Text restart(font, "Press R to Restart", 30);
        restart.setFillColor(sf::Color(200, 200, 200));
        restart.setPosition(sf::Vector2f(140.f, 320.f));
        window.draw(restart);
    }
}
int main()
{
    Game game;
    game.run();
    return 0;
}