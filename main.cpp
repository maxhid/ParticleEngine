#include "constants.h"
#include "particle.h"
#include "renderer.h"
#include "solver.h"
#include <iostream>
#include <SFML/Graphics.hpp>

sf::CircleShape create_particle(double radius);

sf::CircleShape apply_gravity (sf::CircleShape shape);

int main()
{
  const uint32_t window_width = 1920;
  const uint32_t window_height = 1080;

  sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");

  const uint32_t frame_rate = 60;
  window.setFramerateLimit(frame_rate);

  std::vector<Particle> particles;
  int particleCounter {};
  
  sf::Clock clock;
  sf::Clock fpsTimer;
  float fps = 0.0f;


  //const sf::Vector2f gravityVector {0.0f, constants::gravity};
  const sf::Vector2f gravityVector {0.0f, 1000.0f};


  Renderer renderer {window};
  Solver solver;
  solver.setBoundary({static_cast<float>(window_width) * 0.5f, static_cast<float>(window_height) * 0.5f}, 450.0f);
  solver.setFramerate(frame_rate);
  solver.setGravity(gravityVector);

  std::cout << "Set boundary center: " 
          << static_cast<float>(window_width) * 0.5f << ", " 
          << static_cast<float>(window_height) * 0.5f << "\n";
  
  sf::Vector3f boundary = solver.getBoundary();
  std::cout << "Solver boundary center: " 
          << boundary.x << ", " 
          << boundary.y << "\n";

  // auto& object = solver.addObject(sf::Vector2f(500.0f, 500.0f),10.0f, sf::Color::Black);

  // particles.emplace_back(sf::Vector2f(500.0f, 500.0f),10.0f, sf::Color::Black);

  while (window.isOpen()) 
  {
    sf::Event event;
    while (window.pollEvent(event)) 
    {
      if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    }

    float deltaTime = clock.restart().asSeconds();
    if (fpsTimer.getElapsedTime().asSeconds() >= 0.2f) {  // update every 0.2 sec
        fps = 1.0f / deltaTime;
        std::cout << "Current FPS: " << fps << '\n';
        particleCounter = solver.getNumberOfObjects();
        std::cout << "Number of Particles: " << particleCounter << '\n';
        fpsTimer.restart();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            for (int i = 0; i < 1; ++i)
              auto& object = solver.addObject(sf::Vector2f(mouse),10.0f, sf::Color::Red);
                //particles.emplace_back(static_cast<sf::Vector2f>(mouse), 10.0f, sf::Color::Black);
    }

    solver.update();

    window.clear(sf::Color::White);

    renderer.render(solver);
 
    window.display();
  }
  return 0; 
}

sf::CircleShape create_particle(double radius)
{
  sf::CircleShape shape(radius);
  shape.setFillColor(sf::Color::Green);
  shape.setPosition(350.0f, 350.0f);
  return shape;
}