#include <SFML/Graphics.hpp>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(200, 50)), "Digital Clock", sf::Style::None);
    window.setPosition(sf::Vector2i(1700, 10));
    sf::Font font;
    if (!font.openFromFile("/usr/share/fonts/TTF/DejaVuSans-BoldOblique.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Font loaded successfully!" << std::endl;

    window.setSize(sf::Vector2u(200, 100));
    sf::Text clockText(font, "Test Text", 150);
    clockText.setPosition({10, 150});
    clockText.setFillColor(sf::Color::Red);
    window.clear(sf::Color::Black);
    window.draw(clockText);
    window.display();
    std::cout << "Text should be visible now." << std::endl;
    
    while (window.isOpen()) {
        auto event = window.pollEvent();
        while (event.has_value()) {
            if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)) {
                window.close();
            }
            event = window.pollEvent();
        }

        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%H:%M:%S");
        clockText.setString(ss.str());

        window.clear(sf::Color::Black);
        
        clockText.setCharacterSize(150);
        window.draw(clockText);
        window.display();
    }

    return 0;
}
