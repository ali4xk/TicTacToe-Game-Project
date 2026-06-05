#include <iostream>
#include <SFML/Graphics.hpp>
const int WINDOW_SIZE = 600;
const int GRID_SIZE = 3;
const float CELL_SIZE = WINDOW_SIZE / GRID_SIZE;
class Game
{
private:
    sf::RenderWindow window;
    char board[3][3];
public:
    Game();
    void run();
    void render();
    void handleEvents();
};

Game::Game() : window(sf::VideoMode({600, 600}), "Tic Tac Toe")
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
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
void Game::render()
{
    sf::RectangleShape line;
    line.setFillColor(sf::Color::Black);

    float thickness = 6.f;

    // vertical lines
    for (int i = 1; i < GRID_SIZE; i++)
    {
        line.setSize(sf::Vector2f(thickness, WINDOW_SIZE));
        line.setPosition(sf::Vector2f(i * CELL_SIZE, 0.f));
        window.draw(line);
    }

    // horizontal lines
    for (int i = 1; i < GRID_SIZE; i++)
    {
        line.setSize(sf::Vector2f(WINDOW_SIZE, thickness));
        line.setPosition(sf::Vector2f(0.f, i * CELL_SIZE));
        window.draw(line);
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

            std::cout << "Clicked cell: " << row << ", " << col <<std:: endl;
        }
    }
}
int main()
{
    Game game;
    game.run();

    return 0;
}