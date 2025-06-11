#include "SFML/Graphics.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1536, 1024), "Lucian - Sentinel of Light");
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/main-menu-background.png")) {
        return -1;
    }

    // Create background
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    sf::Font font;
    std::string fontPath = "C:/Windows/Fonts/consola.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cout << "Failed to load font from: " << fontPath << std::endl;
        return -1;
    }

    // Set up title text
    sf::Text titleLine1("Lucian", font, 96);
    titleLine1.setFillColor(sf::Color(200, 200, 200));

    sf::Text titleLine2("Sentinel of Light", font, 72);
    titleLine2.setFillColor(sf::Color(200, 200, 200));

    titleLine1.setOrigin(titleLine1.getLocalBounds().width / 2, 0);
    titleLine2.setOrigin(titleLine2.getLocalBounds().width / 2, 0);

    float centerX = window.getSize().x / 2.0f;
    float topOffset = window.getSize().y * 0.13f;

    titleLine1.setPosition(centerX, topOffset);
    titleLine2.setPosition(centerX, topOffset + titleLine1.getLocalBounds().height + 60);

    titleLine1.setStyle(sf::Text::Bold);
    titleLine2.setStyle(sf::Text::Bold);

    titleLine1.setOutlineThickness(3.f);
    titleLine1.setOutlineColor(sf::Color::Black);

    titleLine2.setOutlineThickness(2.f);
    titleLine2.setOutlineColor(sf::Color::Black);

    sf::Text titleShadow1 = titleLine1;
    titleShadow1.setFillColor(sf::Color::Black);
    titleShadow1.move(2.f, 2.f);
    sf::Text titleShadow2 = titleLine2;
    titleShadow2.setFillColor(sf::Color::Black);
    titleShadow2.move(2.f, 2.f);

    // Set up buttons
    const float buttonWidth = 300.f;
    const float buttonHeight = 60.f;
    const float buttonSpacing = 30.f;
    const float buttonStartY = window.getSize().y * 0.5f;

    sf::RectangleShape startButtonRect(sf::Vector2f(buttonWidth, buttonHeight));
    startButtonRect.setFillColor(sf::Color(20, 30, 60));
    startButtonRect.setOutlineThickness(2.f);
    startButtonRect.setOutlineColor(sf::Color(80, 80, 110));
    startButtonRect.setOrigin(buttonWidth / 2, 0);
    startButtonRect.setPosition(centerX, buttonStartY);

    sf::Text startButtonText("Start", font, 32);
    startButtonText.setFillColor(sf::Color(200, 200, 200));
    startButtonText.setStyle(sf::Text::Bold);
    sf::FloatRect startBounds = startButtonText.getLocalBounds();
    startButtonText.setOrigin(startBounds.width / 2.f, startBounds.top + startBounds.height / 2.f);
    startButtonText.setPosition(centerX, startButtonRect.getPosition().y + buttonHeight / 2.f);

    // Options Button
    sf::RectangleShape optionsButtonRect(sf::Vector2f(buttonWidth, buttonHeight));
    optionsButtonRect.setFillColor(sf::Color(20, 30, 60));
    optionsButtonRect.setOutlineThickness(2.f);
    optionsButtonRect.setOutlineColor(sf::Color(80, 80, 110));
    optionsButtonRect.setOrigin(buttonWidth / 2, 0);
    optionsButtonRect.setPosition(centerX, buttonStartY + (buttonHeight + buttonSpacing));

    sf::Text optionsButtonText("Options", font, 32);
    optionsButtonText.setFillColor(sf::Color(200, 200, 200));
    sf::FloatRect optionsBounds = optionsButtonText.getLocalBounds();
    optionsButtonText.setOrigin(optionsBounds.width / 2.f, optionsBounds.top + optionsBounds.height / 2.f);
    optionsButtonText.setPosition(centerX, optionsButtonRect.getPosition().y + buttonHeight / 2.f);

    // Exit Button
    sf::RectangleShape exitButtonRect(sf::Vector2f(buttonWidth, buttonHeight));
    exitButtonRect.setFillColor(sf::Color(20, 30, 60));
    exitButtonRect.setOutlineThickness(2.f);
    exitButtonRect.setOutlineColor(sf::Color(80, 80, 110));
    exitButtonRect.setOrigin(buttonWidth / 2, 0);
    exitButtonRect.setPosition(centerX, buttonStartY + 2 * (buttonHeight + buttonSpacing));

    sf::Text exitButtonText("Exit", font, 32);
    exitButtonText.setFillColor(sf::Color(200, 200, 200));
    sf::FloatRect exitBounds = exitButtonText.getLocalBounds();
    exitButtonText.setOrigin(exitBounds.width / 2.f, exitBounds.top + exitBounds.height / 2.f);
    exitButtonText.setPosition(centerX, exitButtonRect.getPosition().y + buttonHeight / 2.f);



    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(backgroundSprite);
        window.draw(titleShadow1);
        window.draw(titleShadow2);
        window.draw(titleLine1);
        window.draw(titleLine2);
        window.draw(startButtonRect);
        window.draw(startButtonText);
        window.draw(optionsButtonRect);
        window.draw(optionsButtonText);
        window.draw(exitButtonRect);
        window.draw(exitButtonText);
        window.display();
    }

    return 0;
}