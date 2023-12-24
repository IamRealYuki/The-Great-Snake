#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <winuser.h>
#include <fstream>
#include "classes.hpp"

const int width = GetSystemMetrics(SM_CXSCREEN);
const int heigth = GetSystemMetrics(SM_CYSCREEN);
using namespace std;
using namespace sf;

void printField(cell cells[][20], RenderWindow *window)
{
        for(int i = 0; i < 20; i++)
            for(int j = 0; j < 20; j++)
                window->draw(cells[i][j].getShape());

}

bool move(Snake *array[], cell cells[][20], Fruits *fruits[])
{
    cells[array[0]->getY()][array[0]->getX()].setObject(-1);
    switch((int)array[0]->getD())
    {
        case 0: 
            array[0]->setY(array[0]->getY() - 1);
            break;
        case 1: 
            array[0]->setY(array[0]->getY() + 1);
            break;
        case 2:
            array[0]->setX(array[0]->getX() + 1);
            break;
        case 3:
            array[0]->setX(array[0]->getX() - 1);
            break;

    }
    if((cells[array[0]->getY()][array[0]->getX()].getObject()) == 1)
    {
        array[length] = array[length - 1];
        array[length - 1] = new body(array[length]->getX(), array[length]->getY(), array[length]->getD());
    }  
    cells[array[length-1]->getY()][array[length-1]->getX()].setObject(0);
    for(int i = length -1; i >= 1; i--)
    {    
    switch((int)array[i]->getD())
    {
        case 0: 
            array[i]->setY(array[i]->getY() - 1);
            break;
        case 1: 
            array[i]->setY(array[i]->getY() + 1);
            break;
        case 2:
            array[i]->setX(array[i]->getX() + 1);
            break;
        case 3:
            array[i]->setX(array[i]->getX() - 1);
            break;
    }
    array[i]->changeDir(array[i-1]->getD()); 
    }
    if (array[0]->getY() > 19 || array[0]->getY() < 0 || array[0]->getX() > 19 || array[0]->getX() < 0 || cells[array[0]->getY()][array[0]->getX()].getObject() == -1)
        return 0;

    if((cells[array[0]->getY()][array[0]->getX()].getObject()) == 1)
        length++;
    score+=5;
        for(int i = 0; i < 5; i++)
        {
            if(fruits[i]->getX() == array[0]->getX() && fruits[i]->getY() == array[0]->getY())
            {   
                fruits[i]->effect(array);
                int p = rand()%100;
                if(p < 50)
                    fruits[i] = new apple(cells);
                else if(p < 80)
                    fruits[i] = new pineapple(cells);
                else 
                    fruits[i] = new blueberry(cells);
            }
        }
    return 1;
}

void print(RenderWindow *window, Snake *snake[], Fruits *fruits[])
{

    for(int i = 0; i < length; i++)
    {
        snake[i]->print(window);
    }
    for(int i = 0; i < 5; i++)
    {
        fruits[i]->print(window);
    }
}  

int main()
{
    system("chcp 1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    
    RenderWindow window(VideoMode(width, heigth), "The Great Snake!"); //, sf::Style::Fullscreen); //Full screen mode 
    window.setVerticalSyncEnabled(true);
    RectangleShape startButton(Vector2f(250, 100));
    startButton.setOutlineColor(Color(186,28,28));
    startButton.setOutlineThickness(2);
    startButton.setPosition(width/2 - width/15, heigth/2 - heigth/5);
    RectangleShape closeButton(Vector2f(250, 100));
    closeButton.setOutlineColor(Color(255, 0, 0));
    closeButton.setOutlineThickness(2);
    closeButton.setPosition(width/2 - width/15, heigth/2);
    Font font;
    font.loadFromFile("CursiveFont.ttf");
    while (window.isOpen())
    {
        window.clear();

        if(game.getGameState() == 0)
        {                
            Vector2i mousePosition = Mouse:: getPosition(window);
            if (startButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                startButton.setFillColor(Color(230, 77, 0));
            if (!startButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                startButton.setFillColor(Color(255, 77, 0));
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (startButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    game.setGameState(1);

            }
            if (closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                closeButton.setFillColor(Color(200, 10, 20));
            if (!closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                closeButton.setFillColor(Color(220, 30, 45));
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    game.setGameState(-1);
            }
            Text text("", font, 50);
            text.setFillColor(Color(171, 31, 227)); 
            text.setString("Start!");
            text.setPosition(width/2 -45, heigth/2 -heigth/5.5);
            window.draw(startButton);
            window.draw(text);
            window.draw(closeButton);
            text.setFillColor(Color(0, 230, 144)); 
            text.setString("Quit?");
            text.setPosition(width/2 -45, heigth/2 + heigth/70);
            window.draw(text);
        }
        else if (game.getGameState() == 1)
        {
            cell cells[20][20];
            cell Field(5);
            for(int i = 0; i < 20; i++)
                for(int j = 0; j < 20; j++)
                {
                    cell field(750/20, 1, i, j);
                    cells[i][j] = field;
                }
            Snake *snake[400];
            head head(0, 1, Direction:: Down);
            snake[0] = &head;
            tail tail(0,0, Direction:: Down);
            snake[1] = &tail;
            Fruits *fruits[5];
            for(int i = 0; i < 5; i++)
            {
                int p = rand()%100;
                if(p < 33)
                    fruits[i] = new apple(cells);
                else if(p < 66)
                    fruits[i] = new pineapple(cells);
                else 
                    fruits[i] = new blueberry(cells);
            }
            bool condition = 1;
            while(condition)
            {
                window.clear();
                if(GetAsyncKeyState(VK_UP))
                    snake[0]->changeDir(Direction:: Up);
                if(GetAsyncKeyState(VK_DOWN))
                    snake[0]->changeDir(Direction:: Down);
                if(GetAsyncKeyState(VK_LEFT))
                    snake[0]->changeDir(Direction:: Left);
                if(GetAsyncKeyState(VK_RIGHT))
                    snake[0]->changeDir(Direction:: Right);

                window.draw(Field.getShape());
                printField(cells, &window);              
                condition = move(snake, cells, fruits);               
                print(&window, snake, fruits);
                string Score = "Score: ";
                Score.append(to_string(score));  
                Text msg("", font, 50);
                msg.setFillColor(Color(171, 31, 227)); 
                msg.setString(Score);
                window.draw(msg);
                Sleep(game.getSpeed());
                window.display(); 
            }
            for(int i = i; i < length-1; i++)
                delete snake[i];
            for(int i = 0; i < 5; i++)
                delete fruits[i];
            length = 2;
            score = 0;
            r = 110;
            g = 237;
            b = 35;
            game.setSpeed(120);
            game.setGameState(2);
        }
        else if (game.getGameState() == -1)
            window.close();
        else if(game.getGameState() == 2)
        {
                RectangleShape reStartButton(Vector2f(250, 100));
                reStartButton.setOutlineColor(Color(186,28,28));
                reStartButton.setOutlineThickness(2);
                reStartButton.setPosition(width/2 - width/15, heigth/2 - heigth/5);
            Vector2i mousePosition = Mouse:: getPosition(window);
            if (reStartButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                reStartButton.setFillColor(Color(230, 77, 0));
            if (!reStartButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                reStartButton.setFillColor(Color(255, 77, 0));
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (reStartButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    game.setGameState(1);
            }
            if (closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                closeButton.setFillColor(Color(200, 10, 20));
            if (!closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                closeButton.setFillColor(Color(220, 30, 45));
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    game.setGameState(-1);
            }
            Text text("", font, 50);
            text.setFillColor(Color(171, 31, 227)); 
            text.setString("restart");
            text.setPosition(width/2 -45, heigth/2 -heigth/5.5);
            window.draw(reStartButton);
            window.draw(text);
            window.draw(closeButton);
            text.setFillColor(Color(0, 230, 144)); 
            text.setString("Quit?");
            text.setPosition(width/2 -45, heigth/2 + heigth/70);
            window.draw(text);

        }
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
        Sleep(game.getSpeed()/100);
    }
    window.close();
    return 0;
}