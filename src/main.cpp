#include <iostream>
#include <memory>
#include <fstream>
#include <vector>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "Shape.h" // Include the Shape header file

struct WindowConfig {
    unsigned int wWidth  = 1920;
    unsigned int wHeight = 1080;
    std::string fontPath = "fonts/Roboto-Regular.ttf";
    int fontSize         = 18;
    int font_r           = 255;
    int font_g           = 255;
    int font_b           = 255;
};

void readFile(const std::string &filePath, std::vector<std::shared_ptr<Shape> > &shapes, WindowConfig &config)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }
    std::string tempLine;
    while (file >> tempLine)
    {
        if (tempLine == "Window")
        {
            file >> config.wWidth >> config.wHeight;
        } else if (tempLine == "Font")
        {
            file >> config.fontPath >> config.fontSize >> config.font_r >> config.font_g >> config.font_b;
        } else if (tempLine == "Circle" || tempLine == "Rectangle")
        {
            std::string shapeName;
            float positionX, positionY, speedX, speedY;
            int red, green, blue;

            file >> shapeName >> positionX >> positionY >> speedX >> speedY >> red >> green >> blue;

            if (tempLine == "Circle")
            {
                float radius;
                file >> radius;
                shapes.push_back(std::make_shared<Circle>(tempLine, shapeName, positionX, positionY, speedX, speedY,
                                                          red, green, blue, radius));
            } else if (tempLine == "Rectangle")
            {
                float sizeWidth, sizeHeight;
                file >> sizeWidth >> sizeHeight;
                shapes.push_back(std::make_shared<Rectangle>(tempLine, shapeName, positionX, positionY, speedX, speedY,
                                                             red, green, blue, sizeWidth, sizeHeight));
                std::cout << "Shape added" << std::endl;
            }
        }
    }
}


int main()
{
    WindowConfig config;
    std::vector<std::shared_ptr<Shape> > shapes;
    readFile("config.txt", shapes, config);
    for (auto &shape: shapes)
    {
        std::cout << "Shape Type: " << shape->getShapeType() << std::endl;
    }
    sf::RenderWindow window(sf::VideoMode({config.wWidth, config.wHeight}), "SFML Works!");
    window.setFramerateLimit(60);

    // initialize IMGUI
    ImGui::SFML::Init(window);
    sf::Clock deltaTime;
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;


    // set up default circle (keeping for compatibility)


    float circleRadius = 50;
    int circleSegments = 32;
    float circleSpeedX = 1.0f;
    float circleSpeedY = 1.0f;
    bool drawCircle    = true;
    bool drawText      = true;

    // create sfml elements
    sf::CircleShape circle(circleRadius, circleSegments);
    circle.setPosition(sf::Vector2f(10.0f, 10.0f));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        ImGui::SFML::Update(window, deltaTime.restart());

        // draw the ui
        ImGui::Begin("Shape Controller");
        ImGui::Text("Active Shapes: %zu", shapes.size());
        ImGui::End();

        sf::Vector2f newPosition = {circle.getPosition().x + circleSpeedX, circle.getPosition().y + circleSpeedY};
        circle.setPosition(newPosition);

        window.clear();
        // Draw all shapes
        if (drawCircle)
        {
            window.draw(circle);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    // Clean up SFML shapes

    ImGui::SFML::Shutdown();
    return 0;
}
