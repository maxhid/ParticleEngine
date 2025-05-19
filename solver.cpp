#include "solver.h"
#include <math.h>


Particle& Solver::addObject(sf::Vector2f position, float radius, sf::Color color)
{
  return m_objects.emplace_back(position, radius, color);
}

void Solver::setFramerate(float frame_rate)
{
  m_step_dt = 1.0f / static_cast<float>(frame_rate);
}

std::vector<Particle>& Solver::getObjects()
{
  return m_objects;
}

int Solver::getNumberOfObjects()
{
  return static_cast<int>(m_objects.size());
}

void Solver::setBoundary(sf::Vector2f position, float radius)
{
  boundary_center = position;
  boundary_radius = radius;
}

sf::Vector3f Solver::getBoundary()
{
  return {boundary_center.x, boundary_center.y, boundary_radius};
}


void Solver::update() 
{
  float substep_dt = m_step_dt / m_sub_steps;
  for (int i {0}; i < m_sub_steps; i++)
  {
    apply_gravity();
    applyBoundary();
    checkCollisions();
    updateObjects(substep_dt);
  }
  
}

void  Solver::setGravity(sf::Vector2f g)
{
  m_gravity = g;
}

void Solver::apply_gravity()
{
  for (auto& obj : m_objects)
    obj.accelerate(m_gravity);
}

void Solver::applyBoundary()
{
  for (auto& obj : m_objects)
  {
    const sf::Vector2f v = boundary_center - obj.position_current;
    const float distance = sqrt(v.x * v.x + v.y * v.y);
    if (distance > (boundary_radius - obj.m_radius))
    {
      const sf::Vector2f n = v / distance;
      obj.position_current = boundary_center - n * (boundary_radius - obj.m_radius);
    }
  }
}

void Solver::updateObjects(float dt) 
{
  for (auto& obj : m_objects)
    obj.update(dt);
}

// TODO:
void Solver::checkCollisions()
{
  int num_objects {static_cast<int>(m_objects.size())};
  for (int i {0}; i < num_objects; i++)
  {
    Particle& obj_1 = m_objects[i];
    for (int j {i+1}; j < num_objects; j++)
    {
      Particle& obj_2 = m_objects[j];
      sf::Vector2f v = obj_1.position_current - obj_2.position_current;
      float distance = sqrt(v.x * v.x + v.y * v.y);
      float min_distance = obj_1.m_radius + obj_2.m_radius;
      if (distance < min_distance) {
        sf::Vector2f n = v / distance; // Normalize the vector
        float total_mass = obj_1.m_radius * obj_1.m_radius + obj_2.m_radius * obj_2.m_radius;
        float mass_ratio = (obj_1.m_radius * obj_1.m_radius) / total_mass;
        float delta = 0.5f * (min_distance - distance);
        // Larger particle move less
        obj_1.position_current += (n * (1 - mass_ratio) * delta);
        obj_2.position_current -= (n * mass_ratio * delta);
      }
    }
  }
 // for particle in particles
 //   for all_other_particles in particles without particle
          // check for collison
          // resolve collison
}