#include <SFML/Graphics.hpp>
#include "CursorUtils.h"
#include "EpisodeOne.h"
#include <iostream>

void runEpisodeSelect(sf::RenderWindow& window, sf::Font& font) {
    sf::Cursor arrowCursor;
    sf::Cursor handCursor;

    arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    handCursor.loadFromSystem(sf::Cursor::Hand);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/main-menu-background.png")) {
        std::cout << "Failed to load background\n";
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    static sf::Texture episode1Texture;
    if (!episode1Texture.loadFromFile("assets/images/episode-one-background.png")) {
        std::cout << "Failed to load Episode 1 thumbnail\n";
    }

    const float boxWidth = 500.f;
    const float boxHeight = 250.f;
    const float labelHeight = 80.f;
    const float spacingX = 80.f;
    const float spacingY = 80.f;

    const float totalWidth = boxWidth * 2 + spacingX;
    const float totalHeight = boxHeight * 2 + spacingY;

    const float startX = (window.getSize().x - totalWidth) / 2.f;
    const float startY = (window.getSize().y - totalHeight) / 2.f;

    auto lerpColor = [](sf::Color a, sf::Color b, float t) {
        return sf::Color(
            static_cast<sf::Uint8>(a.r + t * (b.r - a.r)),
            static_cast<sf::Uint8>(a.g + t * (b.g - a.g)),
            static_cast<sf::Uint8>(a.b + t * (b.b - a.b))
        );
        };

    sf::RectangleShape backButton(sf::Vector2f(120.f, 50.f));
    backButton.setFillColor(sf::Color(40, 40, 60));
    backButton.setOutlineColor(sf::Color(120, 120, 160));
    backButton.setOutlineThickness(2.f);
    backButton.setPosition(60.f, window.getSize().y - 100.f);

    sf::Text backText;
    backText.setFont(font);
    backText.setString("Back");
    backText.setStyle(sf::Text::Bold);
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color(200, 200, 200));

    float backHoverAlpha = 0.f;

    sf::FloatRect textBounds = backText.getLocalBounds();
    backText.setOrigin(textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    backText.setPosition(
        backButton.getPosition().x + backButton.getSize().x / 2.f,
        backButton.getPosition().y + backButton.getSize().y / 2.f
    );

    std::vector<sf::RectangleShape> episodeBoxes;
    std::vector<sf::Text> episodeLabels;

    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 2; ++col) {
            sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));

            if (row == 0 && col == 0) {
                box.setFillColor(sf::Color::Transparent);
            }
            else {
                box.setFillColor(sf::Color(40, 40, 60));
            }

            box.setOutlineColor(sf::Color(120, 120, 160));
            box.setOutlineThickness(2.f);

            float x = startX + col * (boxWidth + spacingX);
            float y = startY + row * (boxHeight + spacingY);
            box.setPosition(x, y);

            episodeBoxes.push_back(box);

            sf::Text label;
            label.setFont(font);
            label.setString("Episode " + std::to_string(row * 2 + col + 1));
            label.setCharacterSize(24);
            label.setFillColor(sf::Color(200, 200, 200));
            label.setStyle(sf::Text::Bold);

            sf::FloatRect bounds = label.getLocalBounds();
            label.setOrigin(bounds.width / 2.f, 0.f);
            label.setPosition(x + boxWidth / 2.f, y + boxHeight + 15.f);

            episodeLabels.push_back(label);
        }
    }

    static sf::Sprite episode1Sprite;
    episode1Sprite.setTexture(episode1Texture);
    episode1Sprite.setScale(
        episodeBoxes[0].getSize().x / episode1Texture.getSize().x,
        episodeBoxes[0].getSize().y / episode1Texture.getSize().y
    );
    episode1Sprite.setPosition(episodeBoxes[0].getPosition());

    while (window.isOpen()) {
        static sf::Clock clock;
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (backButton.getGlobalBounds().contains(mousePos)) {
                    return;
                }

                if (episodeBoxes[0].getGlobalBounds().contains(mousePos)) {
                    runEpisodeOne(window, font);
                }
            }
        }

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        bool isBackHovered = backButton.getGlobalBounds().contains(mousePos);
        bool hoveringAnything = isBackHovered;

        for (const auto& box : episodeBoxes)
            if (box.getGlobalBounds().contains(mousePos))
                hoveringAnything = true;

        updateCursor(window, arrowCursor, handCursor, hoveringAnything);

        if (isBackHovered)
            backHoverAlpha = std::min(1.f, backHoverAlpha + deltaTime * 4.f);
        else
            backHoverAlpha = std::max(0.f, backHoverAlpha - deltaTime * 4.f);

        sf::Color baseColor(20, 30, 60);
        sf::Color hoverColor(45, 50, 85);
        backButton.setFillColor(lerpColor(baseColor, hoverColor, backHoverAlpha));
        sf::Color textBaseColor(200, 200, 200);
        sf::Color textGlowColor(255, 255, 255);
        backText.setFillColor(lerpColor(textBaseColor, textGlowColor, backHoverAlpha));

        float scale = 1.f + 0.05f * backHoverAlpha;
        backText.setScale(scale, scale);

        sf::FloatRect bounds = backText.getLocalBounds();
        backText.setOrigin(bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        backText.setPosition(
            backButton.getPosition().x + backButton.getSize().x / 2.f,
            backButton.getPosition().y + backButton.getSize().y / 2.f
        );

        // Draw
        window.clear();
        window.draw(backgroundSprite);
        for (int i = 0; i < episodeBoxes.size(); ++i) {
            if (i == 0) {
                window.draw(episode1Sprite); // Episode 1 image
                window.draw(episodeBoxes[i]); // Border over it
            }
            else {
                window.draw(episodeBoxes[i]);
            }
        }

        for (const auto& label : episodeLabels)
            window.draw(label);
        window.draw(backButton);
        window.draw(backText);
        window.display();
    }
}