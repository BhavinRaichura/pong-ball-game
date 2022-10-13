#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Ball");
    //window.setVerticalSyncEnabled(true);

    // Fram-rate
    window.setFramerateLimit(120);

    ///////////////////
    //////////////
    // Create object

    // handler obj1
    sf::RectangleShape obj1(sf::Vector2f(20,100));
    obj1.setFillColor(sf::Color::Blue);
    obj1.setOrigin(10,100);
    obj1.setPosition(20,200);

    // boll obj2
    sf::CircleShape obj2(10.f);
    obj2.setFillColor(sf::Color::Red);
    obj2.setPosition(400,300);

    // Initial moving position
    int yPosPad = 0;
    int xPosBall = -4;
    int yPosBall = -2;

    ///////////////
    ///////////
    // Sounds

    // Ball Bounce sound
    sf::SoundBuffer ball_buffer;
    ball_buffer.loadFromFile("project-data/sound/bounce.wav");
    sf::Sound ball_bounce;
    ball_bounce.setBuffer(ball_buffer);

    // Wall touch sound
    sf::SoundBuffer wall_sound_buffer;
    wall_sound_buffer.loadFromFile("project-data/sound/wall_bump.wav");
    sf::Sound wall_touch;
    wall_touch.setBuffer(wall_sound_buffer);

    ///////////////
    //////////

    std::cout<<"\nGame Started\n";

    while(window.isOpen()){

        /////////////////
        ///////////
        //event part on the main game loop
        sf::Event event;

        while(window.pollEvent(event)) {

            //////////
            // process events

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::N) {
                    obj2.setPosition(400, 300);
                    xPosBall =-3;
                    yPosBall =-4;
                }
            }
            /*
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Up)
                    std::cout<< "up\n"<< event.key.control<<std::endl ;
            }
            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::Up)
                    std::cout<< "released\n"<< event.key.control<<std::endl ;
            }
            */

            // pad logic
            if(event.type == sf::Event::MouseMoved){
                yPosPad = event.mouseMove.y;
                obj1.setPosition(20,yPosPad);
            }

        }

        ///////////////////////
        //////////////
        // Logic Handling

        // Ball logic
        obj2.move(xPosBall,yPosBall);

        // out of boundary chech
        if(obj2.getPosition().y < 0){
            yPosBall = -yPosBall;
            wall_touch.play();
        }
        if(obj2.getPosition().y > 600){
            yPosBall = -yPosBall;
            wall_touch.play();
        }
        if(obj2.getPosition().x > 800){
            xPosBall = -xPosBall;
            wall_touch.play();
        }

        //////////////////////
        ////////////
        // movement

        if(obj2.getGlobalBounds().intersects(obj1.getGlobalBounds())==true)
        {
            xPosBall= -xPosBall;
            ball_bounce.play();
        }


        //////////////////////
        /////////////////
        // rendering part of the main game loop
        window.clear();

        // draw things
        window.draw(obj1);
        window.draw(obj2);

        window.display();


    }

    return 0;
}

/*
 *
 *
 * for complie the code
 g++ -c main.cpp
 *
 * it used to listen what are the thing we are using in this program from SFML
 g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
 *
 * for running the executable
 ./sfml-app
 *
 g++ -c main.cpp
 g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
  ./sfml-app
 */