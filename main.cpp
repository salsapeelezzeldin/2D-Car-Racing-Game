#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>

using namespace std;
using namespace sf;

//Init game const
    const double SCREEN_WIDTH=800;
    const double SCREEN_HEIGH=600;

    const int borderLeft=130;
    const int borderRight=670;

    const int racerWidth=50;
    const int racerHeight=80;

    string stringscore="";
    int score=0;
    double gameSpeed=0.3;

//Create Main Windows
RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "Car Racing");

//Creat random Number for game loop
int getRandomNumber(int a, int b);

// Create gameover screen
int gameOver();
int win();

int main()
{

    //Init font
    Font myfont;
    myfont.loadFromFile("font/xirod.ttf");

    Texture background, racer, obs1, obs2, obs3, obs4,gameover,wins;

    //Load all images
    background.loadFromFile("images/background.png");
    racer.loadFromFile("images/racer.png");
    obs1.loadFromFile("images/car1.png");
    obs2.loadFromFile("images/car2.png");
    obs3.loadFromFile("images/car3.png");
    obs4.loadFromFile("images/platform.png");

    //Create sprite
    Sprite Background(background),Background1(background),Racer(racer),Obs1(obs1),Obs2(obs2),Obs3(obs3),Obs4(obs4),Gameover(gameover),Wins(wins);

    double RacerX, RacerY,Obs1X, Obs1Y,Obs2X, Obs2Y,Obs3X, Obs3Y,Obs4X, Obs4Y;

    //Set racer and Obs pos
	RacerX=SCREEN_WIDTH/2;
	RacerY=SCREEN_HEIGH-racerHeight;
	Obs1X=getRandomNumber(borderLeft,borderRight);
	Obs2X=getRandomNumber(borderLeft,borderRight);
	Obs3X=getRandomNumber(borderLeft,borderRight);
	Obs4X=getRandomNumber(borderLeft,borderRight);
    Obs1Y=0,Obs2Y=-100,Obs3Y=-200,Obs4Y=-300;
    double BackgroundY1=0;
    double BackgroundY2=-600;

    //GAME LOOP
    while (app.isOpen())
    {
        //Init and count score
        stringscore="SCORE: "+to_string(score);
        Text text(stringscore, myfont, 15);
        text.setPosition(5,0);

        //Set car position
        Racer.setPosition(RacerX,RacerY);
        Obs1.setPosition(Obs1X,Obs1Y);
        Obs2.setPosition(Obs2X,Obs2Y);
        Obs3.setPosition(Obs3X,Obs3Y);
        Obs4.setPosition(Obs4X,Obs4Y);

        //Creat scrolling background
        Background.setPosition(0,BackgroundY1);
        Background1.setPosition(0,BackgroundY2);
        if (BackgroundY2>0)
        {
            BackgroundY1=0;
            BackgroundY2=BackgroundY1-500;
        }
        BackgroundY1+=0.1;
        BackgroundY2+=0.1;

        //Set Obs LOOP
        if (Obs1Y>SCREEN_HEIGH)
            {Obs1Y=0;Obs1X=getRandomNumber(borderLeft,borderRight);} else {Obs1Y=Obs1Y+gameSpeed;}
        if (Obs2Y>SCREEN_HEIGH)
            {Obs2Y=0;Obs2X=getRandomNumber(borderLeft,borderRight);} else {Obs2Y=Obs2Y+gameSpeed;}
        if (Obs3Y>SCREEN_HEIGH)
            {Obs3Y=0;Obs3X=getRandomNumber(borderLeft,borderRight);} else {Obs3Y=Obs3Y+gameSpeed;}
        if (Obs4Y>SCREEN_HEIGH)
            {Obs4Y=0;Obs4X=getRandomNumber(borderLeft,borderRight); Obs4.setScale(1,1);} else {Obs4Y=Obs4Y+gameSpeed;}

        //Game level
        if(score>10 && score<40) {gameSpeed=0.4;}
        if(score>40 && score<70) {gameSpeed=0.5;}
        if(score>70 && score<100) {gameSpeed=0.6;}

        //Create event to handle input from keyboard
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                        {if(RacerX>borderLeft) {RacerX=RacerX-20;}}
                    if (event.key.code == sf::Keyboard::Right)
                        {if(RacerX<borderRight){RacerX=RacerX+20;}}
                    if (event.key.code == sf::Keyboard::Up)
                        {if(RacerY>0){RacerY=RacerY-20;}}
                    if (event.key.code == sf::Keyboard::Down)
                        {if(RacerY<SCREEN_HEIGH-70){RacerY=RacerY+20;}}
                }
        }

        //Check if accident happen
         if(Obs1.getGlobalBounds().intersects(Racer.getGlobalBounds()) == true
            || Obs2.getGlobalBounds().intersects(Racer.getGlobalBounds()) == true
            || Obs3.getGlobalBounds().intersects(Racer.getGlobalBounds()) == true )
            {
            gameOver();
            };

         if(RacerX < 140 || RacerX > 660)
            {
            gameOver();
            };

         if(Obs4.getGlobalBounds().intersects(Racer.getGlobalBounds()) == true)
         {
            Obs4.setScale(0,0);
            score += 10;
        };


         if(score > 90)
         {
             win();
         };

        //Clear and redraw position
        app.clear();
        app.draw(Background);
        app.draw(Background1);

        app.draw(Racer);
        app.draw(Obs1);
        app.draw(Obs2);
        app.draw(Obs3);
        app.draw(Obs4);

        app.draw(text);
        app.display();
    }
    return EXIT_SUCCESS;
}
int startGame()
{
    //TODO
}
//Game over
int gameOver()
{
    Texture gameover;
    gameover.loadFromFile("images/gameover.png");

    Sprite Gameover(gameover);

    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        }
        Font myfont;
        myfont.loadFromFile("font/xirod.ttf");
        stringscore="YOUR SCORE:"+to_string(score);


        Text text(stringscore, myfont, 30);
        text.setPosition(210,450);

        app.clear();
        app.draw(Gameover);
        app.draw(text);

        app.display();

    }

}

//Game over
int win()
{
    Texture wins;
    wins.loadFromFile("images/wins.png");

    Sprite Wins(wins);

    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        }
        Font myfont;
        myfont.loadFromFile("font/xirod.ttf");
        stringscore="YOUR SCORE:"+to_string(score);


        Text text(stringscore, myfont, 30);
        text.setPosition(210,450);

        app.clear();
        app.draw(Wins);
        app.draw(text);

        app.display();

    }

}

int getRandomNumber(int a, int b)
    {
        static bool first = true; if (first){srand( time(NULL) );first = false;}
        int result=a + rand() % (( b + 1 ) - a);
        result=(result/10)*10;
        return result;
    }
