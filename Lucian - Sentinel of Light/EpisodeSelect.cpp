#include <SFML/Graphics.hpp>
#include <iostream>

void runEpisodeSelect(sf::RenderWindow& window, sf::Font& font) {
    // Background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/main-menu-background.png")) {
        std::cout << "Failed to load background\n";
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    const float boxWidth = 300.f;
    const float boxHeight = 150.f;
    const float spacingX = 80.f;
    const float spacingY = 60.f;

    const float totalWidth = boxWidth * 2 + spacingX;
    const float totalHeight = boxHeight * 2 + spacingY;

    const float startX = (window.getSize().x - totalWidth) / 2.f;
    const float startY = (window.getSize().y - totalHeight) / 2.f;

    std::vector<sf::RectangleShape> episodeBoxes;

    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 2; ++col) {
            sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
            box.setFillColor(sf::Color(40, 40, 60));
            box.setOutlineColor(sf::Color(120, 120, 160));
            box.setOutlineThickness(2.f);

            float x = startX + col * (boxWidth + spacingX);
            float y = startY + row * (boxHeight + spacingY);
            box.setPosition(x, y);

            episodeBoxes.push_back(box);
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Need a way to return to main menu later
        }

        window.clear();
        window.draw(backgroundSprite);
        for (const auto& box : episodeBoxes) {
            window.draw(box);
        }
        window.display();
    }
}