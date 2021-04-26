#include "vectors.cpp"

class Particle {
    public:
        Vector pos;
        Vector v;
        double radius; Vector center;
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
    {
        for(Particle& particle : all)
        {   
            if(&particle != this && sqrt(pow(particle.center[0] - center[0], 2) + pow(particle.center[1] - center[1], 2)) <= particle.radius + radius)
            {   
                double k = dy / dx;
                Vector b = Vector(dy, -dx);
                b = b / b.length();
                v = v + b * (v * b * -2);
                

                double m1 = radius;
                double m2 = particle.radius;

                double k1 = (m1 - m2) / (m1 + m2);
                double k2 = (2 * m2) / (m1 + m2);

                v = v * k1 + particle.v * k2;
            }
        }
    }


    void collision(double dx, double dy, double n)
    {
        double k = dy / dx;
        Vector b = Vector(dy, -dx);
        b = b / b.length();
        if(abs(pos[1] - k * pos[0] - n) <= radius)
        {   
            //cout << "collision" << endl;
            v = v + b * (v * b * -2);
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