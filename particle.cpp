#include "particle.h"
#include <cmath>

Particle::Particle(sf::Vector2f position, float radius, sf::Color color)
: position_current(position)
, position_old(position)
, m_radius(radius)
, m_color(color)
, acceleration(0.0f, 0.0f)
{
  shape.setRadius(radius);
  shape.setFillColor(color);
  shape.setPosition(position);

  // velocity.x = static_cast<float>((rand() % 200 - 100) / 100.0);
  // velocity.y = static_cast<float>((rand() % 200 - 100) / 100.0);
}

void Particle::update(float deltaTime)
{
  const sf::Vector2f velocity = position_current - position_old;

  position_old = position_current;

  position_current = position_current + velocity + acceleration * deltaTime * deltaTime;

  acceleration = {};

  shape.setPosition(position_current);

  //shape.move(velocity * deltaTime * 100.0f);
}

void Particle::accelerate(sf::Vector2f a)
{
  acceleration += a;
}

void Particle::setVelocity(sf::Vector2f v, float deltaTime)
{
  position_old = position_current - (v * deltaTime);
}

void Particle::addVelocity(sf::Vector2f v, float deltaTime)
{
  position_old -= v * deltaTime;
}

sf::Vector2f Particle::getVelocity()
{
  return (position_current - position_old);
}


void Particle::gravityUpdate(float gravity)
{
  const sf::Vector2f vec {0.0f, gravity};
  accelerate(vec);
}


void Particle::draw(sf::RenderWindow& window) const 
{
  window.draw(shape);
}

float Particle::getRadius()
{
  return m_radius;
}

sf::Vector2f Particle::getCurrentPosition()
{
  return position_current;
}
