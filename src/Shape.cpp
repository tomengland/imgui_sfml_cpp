//
// Created by THOMAS ENGLAND on 5/28/25.
//
#include "Shape.h"

#include <utility>

#include "SFML/System/Vector2.hpp"

Shape::Shape(std::string shapeType, std::string shapeName, float positionX, float positionY, float speedX,
             float speedY, int red,
             int green, int blue)
    : m_ShapeName(std::move(shapeName)),
      m_ShapeType(std::move(shapeType)),
      m_positionX(positionX),
      m_positionY(positionY),
      m_speedX(speedX),
      m_speedY(speedY),
      m_red(red),
      m_green(green),
      m_blue(blue), m_text(m_font)

{
    m_text.setFont(m_font);
    m_text.setPosition({m_positionX, m_positionY});
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::White);
    m_text.setString(m_ShapeName);
}

void Shape::setFont(const std::string &fontPath, int fontSize)
{
    m_font = sf::Font(fontPath.c_str());
    m_text.setFont(m_font);
    m_text.setCharacterSize(fontSize);
    m_text.setFillColor(sf::Color::White);
}

void Shape::updateFontSize(int fontSize)
{
    m_text.setCharacterSize(fontSize);
}

std::string Shape::getShapeName() const { return m_ShapeName; }

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
    return {m_positionX, m_positionY};
}

float &Shape::getSpeedX() { return m_speedX; }
float &Shape::getSpeedY() { return m_speedY; }

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

void Rectangle::setDrawable(bool value)
{
    m_Drawable = value;
}

void Rectangle::update(const sf::Vector2u &windowSize)
{
    // Rectangle-specific update logic
    m_positionX += m_speedX;
    m_positionY += m_speedY;
    updateSFMLShape();
    // Get global bounds for collision detection
    sf::FloatRect bounds = m_rectangle.getGlobalBounds();
    // convert windowSize to float.
    const sf::Vector2f windowSizeF(windowSize);
    // Check X boundaries
    if (bounds.position.x < 0)
    {
        m_speedX    = -m_speedX;
        m_positionX = 0; // Reset to left edge
    } else if (bounds.position.x + bounds.size.x > windowSizeF.x)
    {
        m_speedX    = -m_speedX;
        m_positionX = windowSizeF.x - (m_sizeWidth * m_scaleFactor); // Reset to right edge
    }
    // Check Y boundaries
    if (bounds.position.y < 0)
    {
        m_speedY    = -m_speedY;
        m_positionY = 0; // Reset to top edge
    } else if (bounds.position.y + bounds.size.y > windowSizeF.y)
    {
        m_speedY    = -m_speedY;
        m_positionY = windowSizeF.y - (m_sizeHeight * m_scaleFactor); // Reset to bottom edge
    }
    sf::FloatRect textBounds  = m_text.getGlobalBounds();
    sf::FloatRect shapeBounds = m_rectangle.getGlobalBounds();

    float textPosX = shapeBounds.position.x + (shapeBounds.size.x - textBounds.size.x) / 2;
    float textPosY = shapeBounds.position.y + (shapeBounds.size.y - textBounds.size.y) / 2;

    m_text.setPosition({textPosX, textPosY});

    updateSFMLShape();
}


void Rectangle::updateSFMLShape()
{
    m_rectangle.setPosition(sf::Vector2f(m_positionX, m_positionY));
    m_rectangle.setFillColor(sf::Color(m_red, m_green, m_blue));
    m_rectangle.setSize(sf::Vector2f(m_sizeWidth, m_sizeHeight));
    m_rectangle.setScale(sf::Vector2f(m_scaleFactor, m_scaleFactor));
    m_text.setString(m_ShapeName);
}

void Rectangle::draw(sf::RenderWindow &window) const
{
    if (m_Drawable)
    {
        window.draw(m_rectangle);
        window.draw(m_text);
    }
}

float Rectangle::getScaleFactor() const
{
    return m_scaleFactor;
}

sf::FloatRect Rectangle::getGlobalBounds() const
{
    return m_rectangle.getGlobalBounds();
}

void Rectangle::setScaleFactor(float scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

bool &Rectangle::getDrawableRef()
{
    return m_Drawable;
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

void Circle::setDrawable(bool value)
{
    m_Drawable = value;
}

bool &Circle::getDrawableRef()
{
    return m_Drawable;
}

void Circle::setRadius(float radius)
{
    m_radius = radius;
    updateSFMLShape();
}

sf::FloatRect Circle::getGlobalBounds() const
{
    return m_circle.getGlobalBounds();
}

void Circle::updateSFMLShape()
{
    m_circle.setPosition(sf::Vector2f(m_positionX, m_positionY));
    m_circle.setFillColor(sf::Color(m_red, m_green, m_blue));
    m_circle.setRadius(m_radius);
    m_text.setString(m_ShapeName);
}

void Circle::update(const sf::Vector2u &windowSize)
{
    // Circle-specific update logic
    m_positionX += m_speedX;
    m_positionY += m_speedY;
    const sf::Vector2f windowSizeF(windowSize);


    // Circle boundary checking (using radius * 2 for diameter)
    if (m_positionX < 0 || m_positionX + (m_radius * 2) > windowSizeF.x)
    {
        m_speedX = -m_speedX;
    }
    if (m_positionY < 0 || m_positionY + (m_radius * 2) > windowSizeF.y)
    {
        m_speedY = -m_speedY;
    }
    sf::FloatRect textBounds = m_text.getGlobalBounds();
    m_text.setPosition({
        (getPositionX() + m_radius) - textBounds.size.x / 2, (getPositionY() + m_radius) - textBounds.size.y / 2
    });
    // ... more circle logic
    updateSFMLShape();
}

void Circle::draw(sf::RenderWindow &window) const
{
    if (m_Drawable)
    {
        window.draw(m_circle);
        window.draw(m_text);
    }
}
