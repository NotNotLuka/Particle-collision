#include "vectors.cpp"
#include <unordered_set>

using namespace std;

class Particle {
    public:
        Vector pos;
        Vector v;
        double radius; Vector center;
        unordered_set<int> collisions;

    Particle(int x_size, int y_size)
        {
        bool overlap = true;

        pos[0] = rand() % x_size;
        pos[1] = rand() % y_size;

        //radius = rand() % 5 + 5;
        radius = 10;
        center = pos + (Vector (cos(45), sin(45)) * radius);

        v[0] = rand() % 10 - 5;
        v[1] = rand() % 10 - 5;
        }

    void update_position(int x_size, int y_size, double delta)
    {  
        pos = pos + v / delta;
        center = pos + (Vector (cos(45), sin(45)) * radius); 

        if (center[0] - radius < 0) {pos[0] += - (center[0] - radius) / 2; v[0] = -v[0];}
        if (center[1] - radius < 0) {pos[1] += - (center[1] - radius) / 2; v[1] = -v[1];}

        if (x_size < center[0] + radius){pos[0] -= 2 * (center[0] + radius - x_size); v[0] = -v[0];}
        if (y_size < center[1] + radius){pos[1] -= 2 * (center[1] + radius - y_size); v[1] = -v[1];}

    }

    void collision(vector<Particle>& all)
    {   int i = 0;
        bool in;
        for(Particle& particle : all)
        {   i += 1;
            in = collisions.find(i) != collisions.end();

            if(&particle != this && (((particle.center[0] - center[0]) * (particle.center[0] - center[0])) + ((particle.center[1] - center[1]) * (particle.center[1] - center[1]))) <= (particle.radius + radius) * (particle.radius + radius))
            {   
                collisions.insert(i);
                if(!in)
                {
                    // double m1 = radius;
                    // double m2 = particle.radius;

                    // double k1 = (m1 - m2) / (m1 + m2);
                    // double k2 = (2 * m2) / (m1 + m2);

                    // v = v * k1 + particle.v * k2;

                    double x_collision = particle.pos[0] - (abs(particle.pos[0] - pos[0]) / (radius + particle.radius)) * particle.radius;
                    double y_collision = particle.pos[1] - (abs(particle.pos[1] - pos[1]) / (radius + particle.radius)) * particle.radius;
                    
                    double k;
                    double dx;
                    double dy;
                    if((y_collision - pos[1]) == 0)
                    {
                        dy = 10;
                        dx = 0;

                    }else 
                        {
                    
                            k = (pos[0] - x_collision) / (y_collision - pos[1]);

                            double n = y_collision - k * x_collision;

                            double new_x = -100;
                            double new_y = k * (new_x) + n;

                            dy = y_collision - new_y;
                            dx = x_collision - new_x;
                        }

                    Vector b = Vector(dy, -dx);
                    b = b / b.length();
                    v = v + b * (v * b * -2);
                }

            }else{if(in)collisions.erase(i);}
        }
    }


    sf::CircleShape draw()
    {   
        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color(255, 255, 255));
        shape.setPosition(pos[0], pos[1]);
        return shape;
    }
};