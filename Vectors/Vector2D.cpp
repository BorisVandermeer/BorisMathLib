/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A Simple implement of Vec2D
 * 
*********************************************************************/

#include <cmath>
#include <ostream>

#include<Vectors/Vector2D.h>

namespace Vectors {

Vector2D::Vector2D(){x = 0.0F,y=0.0F;}

Vector2D Vector2D::operator-() const { return Vector2D(-x, -y); }

double Vector2D::operator*(const Vector2D &vector) const {
    return x * vector.x + y * vector.y;
}

Vector2D Vector2D::operator*(double scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(double scalar) const {
    const double invScalar = 1.0F / scalar;
    return Vector2D(x * invScalar, y * invScalar);
}

Vector2D Vector2D::operator+(const Vector2D &vector) const {
    return Vector2D(x + vector.x, y + vector.y);
}

Vector2D Vector2D::operator-(const Vector2D &vector) const {
    return Vector2D(x - vector.x, y - vector.y);
}

bool Vector2D::operator==(const Vector2D &vector) const {
    return x == vector.x && y == vector.y;
}

bool Vector2D::operator!=(const Vector2D &vector) const {
    return x != vector.x || y != vector.y;
}

Vector2D &Vector2D::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;

    return *this;
}

Vector2D &Vector2D::operator/=(double scalar) {
    const double invScalar = 1.0F / scalar;
    x *= invScalar;
    y *= invScalar;

    return *this;
}

Vector2D &Vector2D::operator+=(const Vector2D &vector) {
    x += vector.x;
    y += vector.y;

    return *this;
}

Vector2D &Vector2D::operator-=(const Vector2D &vector) {
    x -= vector.x;
    y -= vector.y;

    return *this;
}

Vector2D operator*(double scalar, const Vector2D &vector) {
    return Vector2D(scalar * vector.x, scalar * vector.y);
}

std::ostream &operator<<(std::ostream &stream, const Vector2D &vector) {
    stream << "(" << vector.x << "," << vector.y << ")";

    return stream;
}

double abs(const Vector2D &vector) { return std::sqrt(vector * vector); }

double absSq(const Vector2D &vector) { return vector * vector; }

double det(const Vector2D &vector1, const Vector2D &vector2) {
    return vector1.x * vector2.y - vector1.y * vector2.x;
}

double leftOf(const Vector2D &vector1, const Vector2D &vector2,
             const Vector2D &vector3) {
    return det(vector1 - vector3, vector2 - vector1);
}

Vector2D normalize(const Vector2D &vector) { return vector / abs(vector); }
} // namespace Vectors
