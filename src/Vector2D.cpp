#include "Vector2D.hpp"

Vector2D::Vector2D() {
    x = 0;
    y = 0;
}

Vector2D::Vector2D(double xpos, double ypos) {
    this -> x = xpos;
    this -> y = ypos;
}

Vector2D & Vector2D::Add(const Vector2D & vector) {
    this -> x += vector.x;
    this -> y += vector.y;
    return * this;
}

Vector2D & Vector2D::Subtract(const Vector2D & vector) {
    this -> x -= vector.x;
    this -> y -= vector.y;
    return * this;
}

Vector2D & Vector2D::Divide(const Vector2D & vector) {
    this -> x /= vector.x;
    this -> y /= vector.y;
    return * this;
}

Vector2D & Vector2D::Multiply(const Vector2D & vector) {
    this -> x *= vector.x;
    this -> y *= vector.y;
    return * this;
}

double Vector2D::Dot(const Vector2D & vector) {
    return this -> x * vector.x + this -> y * vector.y;
}

Vector2D & Vector2D::Cross(const Vector2D & vector) {
    this -> x = -vector.x;
    this -> y = vector.y;
    return * this;
}

Vector2D & Vector2D::Normalize() {
    double len = this -> norm();
    if(len != 0) {
        this -> x /= len;
        this -> y /= len;
    }
    return * this;
}

Vector2D & operator+(Vector2D & v1, const Vector2D & v2) {
    return v1.Add(v2);
}

Vector2D & operator-(Vector2D & v1, const Vector2D & v2) {
    return v1.Subtract(v2);
}

Vector2D & operator/(Vector2D & v1, const Vector2D & v2) {
    return v1.Divide(v2);
}

Vector2D & operator*(Vector2D & v1, const Vector2D & v2) {
    return v1.Multiply(v2);
}

Vector2D & Vector2D::operator+=(const Vector2D & vector) {
    return this -> Add(vector);
}

Vector2D & Vector2D::operator-=(const Vector2D & vector) {
    return this -> Subtract(vector);
}

Vector2D & Vector2D::operator/=(const Vector2D & vector) {
    return this -> Divide(vector);
}

Vector2D & Vector2D::operator*=(const Vector2D & vector) {
    return this -> Multiply(vector);
}

Vector2D & Vector2D::operator*(const int & i) {
    this -> x *= i;
    this -> y *= i;

    return * this;
}

Vector2D & Vector2D::Zero() {
    this -> x = 0;
    this -> y = 0;

    return * this;
}

std::ostream & operator<<(std::ostream & stream, const Vector2D & vector) {
    stream << "( " << vector.x << " , " << vector.y << " )" << std::endl;
    return stream;
}