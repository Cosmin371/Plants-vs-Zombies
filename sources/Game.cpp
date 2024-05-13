//
// Created by Cosmin on 04.04.2024.
//

#include "../headers/Game.h"

Game::Game():
    window{sf::RenderWindow(sf::VideoMode(1500, 850), "Cats vs. Boxes", sf::Style::Titlebar | sf::Style::Close)} {

    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f (150.f, 150.f));
    tile.setFillColor(sf::Color(144, 238, 144));
    tile.setOutlineThickness(3.f);
    tile.setOutlineColor(sf::Color(165, 42, 42));

    window.setFramerateLimit(60);

    /// construire background
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            tile.setPosition(float(j) * 150.f, 100.f + 150.f * float(i));
            background_tiles.push_back(tile);
        }
    }

    /// construire butoane
    entities.push_back(new Button(sf::Vector2f(200.f, 100.f), 0.f, 0.f, sf::Color(202, 209, 12)));
    entities.push_back(new Button(sf::Vector2f(200.f, 100.f), 200.f, 0.f, sf::Color(12, 209, 28)));
    entities.push_back(new Button(sf::Vector2f(200.f, 100.f), 400.f, 0.f, sf::Color(12, 182, 209)));
    entities.push_back(new Button(sf::Vector2f(300.f, 100.f), 600.f, 0.f, sf::Color(209, 12, 195)));
    entities.push_back(new Button(sf::Vector2f(300.f, 100.f), 900.f, 0.f, sf::Color(209, 15, 12)));
    entities.push_back(new Button(sf::Vector2f(300.f, 100.f), 1200.f, 0.f, sf::Color(12, 209, 166)));

}
void Game::update() {

    /// Spawn Enemies
    sf::Time deltaTime = spawnTimer.getElapsedTime();
    if (deltaTime >= sf::seconds(2)) {
        spawnEnemy();
        spawnTimer.restart();
    }

    /// Move Enemies
    for (auto &enemy : enemies)
        enemy.move();
}

void Game::render() {
    for (auto &tile : background_tiles)
        window.draw(tile);
    for (auto &enemy : enemies)
        enemy.draw(window, sf::RenderStates::Default);
    for (auto &entity : entities)
        entity->draw(window, sf::RenderStates::Default);

    window.display();
}

bool Game::isRunning() const {
    return window.isOpen();
}

void Game::closeIfNeeded() {
    /// Fereastra se inchide cand apasam X-ul ferestrei sau Esc
    sf::Event ev{};
    while (window.pollEvent(ev)) {
        switch (ev.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                    window.close();
            default:
                break;
        }
    }
}

void Game::run() {
    while (isRunning()) {
        closeIfNeeded();

        update();
        render();
    }
}

void Game::setHighScore(const int &s) {
    Game::highScore = s;
}

void Game::spawnEnemy() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Randomly generate a line between 0 and 4
    std::uniform_int_distribution<> dis(0, 4);
    int randomLine = dis(gen);

    // Create and initialize the enemy with the random line
    Enemy enemy(randomLine); // NOLINT(*-use-auto)

    // Add the enemy to your collection or perform further actions
    // For example, you might have a vector of enemies
    enemies.push_back(enemy);
}
