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

public:
    Game();
    void run();
    void handleEvents();
    void render();
};

Game::Game()
    : window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "Tic Tac Toe")
{
    // init board
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }

    // load font
    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "Font failed to load!" << std::endl;
    }
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
                }
            }
        }
    }
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

    // TEXT (X and O)
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
                    i * CELL_SIZE + 40.f
                ));

                window.draw(text);
            }
        }
    }
}

int main()
{
    Game game;
    game.run();
    return 0;
}