#include <SFML/Graphics.hpp>

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

        window.clear(sf::Color::White);

        render();

        window.display();
    }
}
void Game::render()
{
    sf::RectangleShape line;

    // Vertical line 1
    line.setSize({5.f, 600.f});
    line.setPosition({200.f, 0.f});
    line.setFillColor(sf::Color::Black);
    window.draw(line);

    // Vertical line 2
    line.setPosition({400.f, 0.f});
    window.draw(line);

    // Horizontal line 1
    line.setSize({600.f, 5.f});
    line.setPosition({0.f, 200.f});
    window.draw(line);

    // Horizontal line 2
    line.setPosition({0.f, 400.f});
    window.draw(line);
}

int main()
{
    Game game;
    game.run();

    return 0;
}