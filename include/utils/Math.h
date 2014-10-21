#ifndef MATH_H
#define MATH_H

#include "SFML/System/Vector2.hpp"

namespace math
{

float magnitude(const sf::Vector2f& v);

void normalize(sf::Vector2f& v);

float dotProduct(const sf::Vector2f& v1,
                 const sf::Vector2f& v2);

float angleBetween(const sf::Vector2f& v1,
                   const sf::Vector2f& v2);

}

#endif // MATH_H