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
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

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
        line.setSize({thickness, WINDOW_SIZE});
        line.setPosition(i * CELL_SIZE, 0);
        window.draw(line);
    }

    // horizontal lines
    for (int i = 1; i < GRID_SIZE; i++)
    {
        line.setSize({WINDOW_SIZE, thickness});
        line.setPosition(0, i * CELL_SIZE);
        window.draw(line);
    }
}

int main()
{
    Game game;
    game.run();

    return 0;
}