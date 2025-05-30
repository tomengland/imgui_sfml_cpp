#pragma once
#include <string>

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

    virtual void update();

    const std::string &getShapeName() const;

    void setShapeName(const std::string &shapeName);

    const std::string &getShapeType() const;

    float getPositionX() const;

    float getPositionY() const;

    int getRed() const;

    int getGreen() const;

    int getBlue() const;
};

class Rectangle : public Shape {
private:
    float m_sizeWidth;
    float m_sizeHeight;

public:
    Rectangle(const std::string &shapeType, const std::string &shapeName, float positionX, float positionY,
              float speedX, float speedY, int red,
              int green, int blue, float sizeWidth, float sizeHeight);

    float getSizeWidth() const;

    float getSizeHeight() const;
};

class Circle : public Shape {
private:
    float m_radius;

public:
    Circle(const std::string &shapeType, const std::string &shapeName, float positionX, float positionY, float speedX,
           float speedY, int red,
           int green, int blue, float radius);

    float getRadius() const;
};
