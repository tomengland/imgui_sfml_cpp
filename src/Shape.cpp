//
// Created by THOMAS ENGLAND on 5/28/25.
//
#include "Shape.h"

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

void Shape::update()
{
    m_positionX += m_speedX;
    m_positionY += m_speedY;
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
int Shape::getRed() const { return m_red; }
int Shape::getGreen() const { return m_green; }
int Shape::getBlue() const { return m_blue; }

Rectangle::Rectangle(const std::string &shapeType, const std::string &shapeName, float positionX, float positionY,
                     float speedX, float speedY,
                     int red,
                     int green, int blue, float sizeWidth, float sizeHeight)
    : Shape(shapeType, shapeName, positionX, positionY, speedX, speedY, red, green, blue),
      m_sizeWidth(sizeWidth),
      m_sizeHeight(sizeHeight)
{
}

float Rectangle::getSizeWidth() const { return m_sizeWidth; }
float Rectangle::getSizeHeight() const { return m_sizeHeight; }

Circle::Circle(const std::string &shapeType, const std::string &shapeName, float positionX, float positionY,
               float speedX, float speedY, int red,
               int green, int blue, float radius)
    : Shape(shapeType, shapeName, positionX, positionY, speedX, speedY, red, green, blue),
      m_radius(radius)
{
}

float Circle::getRadius() const { return m_radius; }
