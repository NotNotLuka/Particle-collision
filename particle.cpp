class Particle {
    public:
        int x;int y;
        int vx; int vy;
        int radius; int center[2];
    Particle(int x_size, int y_size, vector<Particle> all)
        {
        bool overlap = true;
        while(overlap)
        {
            x = rand() % x_size;
            y = rand() % y_size;
            int max_radius = 5;

            if(x_size < x + (max_radius + 5) * 2)max_radius = (x_size - x) / 2 - 5;
            if(y_size < y + (max_radius + 5) * 2)max_radius = (y_size - y) / 2 - 5;

            radius = rand() % max_radius + 5;
            center[0] = int(x + cos(45) * radius);
            center[1] = int(y + sin(45) * radius);

            overlap = check_overlap(all);
        }
        vx = rand() % 10 - 5;vy = rand() % 10 - 5;
        while(vx ==  0)vx = rand() % 10 - 5;
        while(vy ==  0)vy = rand() % 10 - 5;

    }
    bool check_overlap(vector<Particle> all)
    {
        for(Particle particle : all)
        {
            if((pow(particle.center[0] - center[0], 2) + pow(particle.center[1] - center[1], 2)) <= particle.radius + radius)return true;
        }
        return false;
    }

    void update_position(int x_size, int y_size)
    { 
        x += vx; y += vy;
        center[0] = int(x + cos(45) * radius);
        center[1] = int(y + sin(45) * radius);

        if (center[0] - radius < 0) {x += - int((center[0] - radius) / 2); vx = -vx;}
        if (center[1] - radius < 0) {y += - int((center[1] - radius) / 2); vy = -vy;}

        if (x_size < center[0] + radius){x -= 2 * (center[0] + radius - x_size); vx = -vx;}
        if (y_size < center[1] + radius){y -= 2 * (center[1] + radius - y_size); vy = -vy;}
    }

    sf::CircleShape draw()
    {   
        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color(255, 255, 255));
        shape.setPosition(x, y);
        return shape;
    }
};