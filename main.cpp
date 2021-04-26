#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

#include "particle.cpp"


int main()
{   
    double dy = 1; double dx = 3; double sx = 0;
    int size;int elapsed;
    int x = 1000;int y = 600;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(x, y), "Particle collison", sf::Style::Close);

    vector<Particle> particles;
    for(int i = 0; i < 1; i++)particles.push_back(Particle(x, y));


    particles[0].pos = {50, 300};
    particles[0].radius = 10;
    particles[0].v = {2, -3};


    // particles[1].pos = {200, 300};
    // particles[1].radius = 10;
    // particles[1].v = {0, 0};
    sf::RectangleShape line(sf::Vector2f(10000, 3));
    line.setPosition(sx, 0);
    line.rotate(atan2(dy, dx) * 180 / 3.1415926535897932386);

    while(window.isOpen())
    {
        window.clear(sf::Color::Black);
        window.draw(line);
        size = particles.size();
        for(int i = 0; i < size; i++)
        {   for(int j = 0; j < 1000; j++)
            {
                particles[i].collision(dx, dy, dy / dx * sx);
                particles[i].update_position(x, y, 3000);
            }
            sf::CircleShape shape = particles[i].draw();
            window.draw(shape);
        }
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:break;
            }
           
        }

        window.display();
    }
    return 0;
}


