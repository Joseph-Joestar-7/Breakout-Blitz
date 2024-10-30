#pragma once
#include "glm/glm.hpp"
#include "SFML/Graphics.hpp"
#include <variant>
class CTransform {
public:
	glm::vec2 position = { 0.0f,0.0f };
	glm::vec2 velocity = { 0.0f,0.0f };
	float angle = 0.0f;

	CTransform(const glm::vec2& p, const glm::vec2& v, float a)
		:position(p), velocity(v), angle(a)
	{}
};

class CShape {
public:
	std::variant<sf::RectangleShape, sf::CircleShape> shape;  // Holds either a rectangle or circle

	CShape(float width, float height, const sf::Color& fill,
		const sf::Color& outline, float thickness)
	{
		// If height is zero, create a circle
		if (height == 0) {
			sf::CircleShape circleShape(width);
			circleShape.setFillColor(fill);
			circleShape.setOutlineColor(outline);
			circleShape.setOutlineThickness(thickness);
			circleShape.setOrigin(width, width);  // center origin for circle
			shape = circleShape;
		}
		// Otherwise, create a rectangle
		else {
			sf::RectangleShape rectangleShape(sf::Vector2f(width, height));
			rectangleShape.setFillColor(fill);
			rectangleShape.setOutlineColor(outline);
			rectangleShape.setOutlineThickness(thickness);
			rectangleShape.setOrigin(width / 2, height / 2);  // center origin for rectangle
			shape = rectangleShape;
		}
	}
};

class CCollision {
public:
	float collisionRadius = 0;

	CCollision(float r)
		:collisionRadius(r)
	{}
};

class CScore {
public:
	int score = 0;

	CScore(int s) :score(s) {}
};

class CLifespan{
public:
	int remaining = 0;
	int total = 0;

	CLifespan(int total) :
		remaining(total),total(total) {}
};

class CInput {
public:
	bool left = false;
	bool right = false;
	CInput()
	{}
};