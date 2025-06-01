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
        std::cerr << "Error opening config file: " << filePath << std::endl;
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
            }
        }
    }
}


int main()
{
    WindowConfig config;
    std::vector<std::shared_ptr<Shape> > shapes;
    size_t selectedShapeIndex = 0;
    char buffer[255]          = "";
    readFile("config.txt", shapes, config);
    if (shapes.empty())
    {
        std::cerr << "No shapes found in the configuration file." << std::endl;
        return 1;
    }
    sf::RenderWindow window(sf::VideoMode({config.wWidth, config.wHeight}), "Clair Expedition: 34 .. heh",
                            sf::Style::Close);
    window.setFramerateLimit(60);

    // initialize IMGUI
    if (!ImGui::SFML::Init(window))
    {
        std::cerr << "Failed to initialize ImGui-SFML" << std::endl;
        return 1;
    }
    sf::Clock deltaTime;
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;


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
        // Create dropdown for shapes
        if (!shapes.empty())
        {
            if (ImGui::BeginCombo("Select Shape", shapes[selectedShapeIndex]->getShapeName().c_str()))
            {
                for (size_t i = 0; i < shapes.size(); i++)
                {
                    bool isSelected = (selectedShapeIndex == i);
                    if (ImGui::Selectable(shapes[i]->getShapeName().c_str(), isSelected))
                    {
                        selectedShapeIndex = i;
                    }
                    if (isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                        buffer[0] = '\0';
                    }
                }
                ImGui::EndCombo();
            }

            // Get reference to the selected shape for easier access
            auto &selectedShape = shapes[selectedShapeIndex];

            ImGui::Separator();
            ImGui::Text("Shape Properties");
            ImGui::Text("Selected: %s (%s)", selectedShape->getShapeName().c_str(),
                        selectedShape->getShapeType().c_str());
            ImGui::InputText("Shape Name", buffer, sizeof(buffer));
            if (ImGui::Button("Change Shape Text"))
            {
                selectedShape->setShapeName(buffer);
            }

            // Shape-specific properties
            if (selectedShape->getShapeType() == "Circle")
            {
                if (auto circle = std::dynamic_pointer_cast<Circle>(selectedShape))
                {
                    float radius = circle->getRadius();
                    if (ImGui::SliderFloat("Radius", &radius, 1.0f, 200.0f))
                    {
                        circle->setRadius(radius);
                    }
                    ImGui::Checkbox("Draw Shape", &circle->getDrawableRef());
                }
            } else if (selectedShape->getShapeType() == "Rectangle")
            {
                if (auto rectangle = std::dynamic_pointer_cast<Rectangle>(selectedShape))
                {
                    float scaleFactor = rectangle->getScaleFactor();
                    if (ImGui::SliderFloat("Scale Factor", &scaleFactor, 0.5f, 5.0f))
                    {
                        rectangle->setScaleFactor(scaleFactor);
                    }
                    ImGui::Checkbox("Draw Shape", &rectangle->getDrawableRef());
                }
            }

            ImGui::Separator();
        }

        // Update shapes
        window.clear();
        // Draw shapes
        for (auto &shape: shapes)
        {
            shape->update(window.getSize());
            shape->draw(window);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    // Clean up SFML shapes

    ImGui::SFML::Shutdown();
    return 0;
}
