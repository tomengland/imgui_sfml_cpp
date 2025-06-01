#pragma once
#include <string>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

class Shape {
protected:
    std::string m_ShapeName;
    std::string m_ShapeType;
    float m_positionX;
    float m_positionY;
    float m_speedX;
    float m_speedY;
    int m_red;
    int m_green;
    int m_blue;

public:
    Shape(const std::string &shapeType, const std::string &shapeName, float positionX, float positionY, float speedX,
          float speedY, int red,
          int green, int blue);

    virtual void update(const sf::Vector2u &windowSize) = 0;

    virtual void draw(sf::RenderWindow &window) const = 0;

    const std::string &getShapeName() const;

    void setShapeName(const std::string &shapeName);

    const std::string &getShapeType() const;

    float getPositionX() const;

    float getPositionY() const;

    sf::Vector2f getPosition() const;


    int getRed() const;

    int getGreen() const;

    int getBlue() const;
};

class Rectangle : public Shape {
private:
    float m_sizeWidth;
    float m_sizeHeight;
    sf::RectangleShape m_rectangle;
    float m_scaleFactor = 1.0f;
    bool m_Drawable     = true;

public:
    Rectangle(const std::string &shapeType, const std::string &shapeName, float positionX, float positionY,
              float speedX, float speedY, int red,
              int green, int blue, float sizeWidth, float sizeHeight);

    void setDrawable(bool value);

    void update(const sf::Vector2u &windowSize) override;

    void updateSFMLShape();


    void draw(sf::RenderWindow &window) const override;

    float getScaleFactor();

    void setScaleFactor(float scaleFactor);

    bool &getDrawableRef();
};

class Circle : public Shape {
private:
    float m_radius;
    sf::CircleShape m_circle;
    bool m_Drawable = true;

public:
    Circle(const std::string &shapeType, const std::string &shapeName, float positionX, float positionY, float speedX,
           float speedY, int red,
           int green, int blue, float radius);

    float getRadius() const;

    void setDrawable(bool value);

    bool &getDrawableRef();

    void setRadius(float radius);

    void updateSFMLShape();

    void update(const sf::Vector2u &windowSize) override;


    void draw(sf::RenderWindow &window) const override;
};
