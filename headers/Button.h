//
// Created by Cosmin on 13.05.2024.
//

#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#include "SFML/Graphics.hpp"
#include "Drawable.h"
#include "Cats/ShooterCat.h"
#include "Cats/GeneratorCat.h"
#include "Cats/WallCat.h"

template<typename T>
class Button : public Drawable{
    static std::unique_ptr<Cat> entity;
    [[maybe_unused]] static bool dragging;
    sf::Font font;
    int cost;
    sf::Text costText;
public:
    Button(sf::Vector2f, float, float, sf::Color, int);
    void draw(sf::RenderTarget& target, sf::RenderStates states) override;

    static void drag(sf::Vector2f&);
    static void place(sf::Vector2f&, std::vector<std::unique_ptr<Cat>>&, std::vector<std::vector<bool>>&);
    static void instantiate(sf::Vector2f&);
    static bool isDragging();
    static void displayEntity(sf::RenderTarget&, sf::RenderStates);
};


#endif //OOP_BUTTON_H
