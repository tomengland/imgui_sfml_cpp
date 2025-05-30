//
// Created by THOMAS ENGLAND on 5/28/25.
//
#include "Shape.h"

#include "SFML/System/Vector2.hpp"

Shape::Shape(const std::string &shapeType, const std::string &shapeName, float positionX, float positionY, float speedX,
             float speedY, int red,
             int green, int blue)
    : m_ShapeName(shapeName),
      m_ShapeType(shapeType),
      m_positionX(positionX),
      m_positionY(positionY),
      m_speedX(speedX),
      m_speedY(speedY),
      m_red(red),
      m_green(green),
      m_blue(blue)
{
}


const std::string &Shape::getShapeName() const { return m_ShapeName; }

const std::string &Shape::getShapeType() const
{
    return m_ShapeType;
}

void Shape::setShapeName(const std::string &shapeName)
{
    m_ShapeName = shapeName;
}

float Shape::getPositionX() const { return m_positionX; }
float Shape::getPositionY() const { return m_positionY; }

sf::Vector2f Shape::getPosition() const
{
    return sf::Vector2f(m_positionX + m_speedX, m_positionY + m_speedY);
}

int Shape::getRed() const { return m_red; }
int Shape::getGreen() const { return m_green; }
int Shape::getBlue() const { return m_blue; }

Rectangle::Rectangle(const std::string &shapeType, const std::string &shapeName, float positionX, float positionY,
                     float speedX, float speedY,
                     int red,
                     int green, int blue, float sizeWidth, float sizeHeight)
    : Shape(shapeType, shapeName, positionX, positionY, speedX, speedY, red, green, blue),
      m_sizeWidth(sizeWidth),
      m_sizeHeight(sizeHeight),
      m_rectangle(sf::Vector2f(m_sizeWidth, m_sizeHeight))
{
    updateSFMLShape();
}

float Rectangle::getSizeWidth() const { return m_sizeWidth; }

void Rectangle::update(const sf::Vector2u &windowSize)
{
    // Rectangle-specific update logic
    m_positionX += m_speedX;
    m_positionY += m_speedY;

    // Rectangle boundary checking (using width/height)
    if (m_positionX < 0 || m_positionX + m_sizeWidth > windowSize.x)
    {
        m_speedX = -m_speedX;
    }
    if (m_positionY < 0 || m_positionY + m_sizeHeight > windowSize.y)
    {
        m_speedY = -m_speedY;
    }
    // ... more rectangle logic
    updateSFMLShape();
}

float Rectangle::getSizeHeight() const { return m_sizeHeight; }

void Rectangle::updateSFMLShape()
{
    m_rectangle.setPosition(sf::Vector2f(m_positionX, m_positionY));
    m_rectangle.setFillColor(sf::Color(m_red, m_green, m_blue));
    m_rectangle.setSize(sf::Vector2f(m_sizeWidth, m_sizeHeight));
}

void Rectangle::draw(sf::RenderWindow &window) const
{
    window.draw(m_rectangle);
}


Circle::Circle(const std::string &shapeType, const std::string &shapeName, float positionX, float positionY,
               float speedX, float speedY, int red,
               int green, int blue, float radius)
    : Shape(shapeType, shapeName, positionX, positionY, speedX, speedY, red, green, blue),
      m_radius(radius),
      m_circle(m_radius)
{
    updateSFMLShape();
}

float Circle::getRadius() const { return m_radius; }

void Circle::updateSFMLShape()
{
    m_circle.setPosition(sf::Vector2f(m_positionX, m_positionY));
    m_circle.setFillColor(sf::Color(m_red, m_green, m_blue));
    m_circle.setRadius(m_radius);
}

void Circle::update(const sf::Vector2u &windowSize)
{
    // Circle-specific update logic
    m_positionX += m_speedX;
    m_positionY += m_speedY;

    // Circle boundary checking (using radius * 2 for diameter)
    if (m_positionX < 0 || m_positionX + (m_radius * 2) > windowSize.x)
    {
        m_speedX = -m_speedX;
    }
    if (m_positionY < 0 || m_positionY + (m_radius * 2) > windowSize.y)
    {
        m_speedY = -m_speedY;
    }
    // ... more circle logic
    updateSFMLShape();
}

void Circle::draw(sf::RenderWindow &window) const
{
    window.draw(m_circle);
}


