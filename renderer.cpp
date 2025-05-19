#ifndef RENDERER_H
#define RENDERER_H

#include "renderer.h"

Renderer::Renderer(sf::RenderTarget& target)
: m_target(target)
{

}

void Renderer::render(Solver& solver) const 
{
  const sf::Vector3f boundary = solver.getBoundary();
  sf::CircleShape boundary_ring{boundary.z};
  boundary_ring.setOrigin(boundary.z, boundary.z);
  boundary_ring.setFillColor(sf::Color::Black);
  boundary_ring.setPosition(boundary.x, boundary.y);
  boundary_ring.setPointCount(128);
  m_target.draw(boundary_ring);

  sf::CircleShape circle{1.0f};
  circle.setOrigin(1.0f, 1.0f);
  circle.setPointCount(32);
  const auto& objects = solver.getObjects();
  for (const auto& obj : objects)
  {
    circle.setPosition(obj.position_current);
    circle.setScale(obj.m_radius, obj.m_radius);
    circle.setFillColor(obj.m_color);
    m_target.draw(circle);
  }

}


#endif