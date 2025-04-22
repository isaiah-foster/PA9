#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using std::string;

class TextLabel : public sf::Text {
public:
    TextLabel(const sf::Font& font, const string& text = "", unsigned int charSize = 30, sf::Color color = sf::Color::White, sf::Vector2f position = { 0.f, 0.f })
        : sf::Text(text, font)
    {
        setCharacterSize(charSize);
        setFillColor(color);
        setPosition(position);
    }

    void setText(const string& newText) {
        setString(newText);
    }

    void setTextColor(const sf::Color& color) {
        setFillColor(color);
    }

    void setTextSize(unsigned int size) {
        setCharacterSize(size);
    }

    void setTextPosition(const sf::Vector2f& pos) {
        setPosition(pos);
    }
};