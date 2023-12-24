#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#ifndef classeshpp
#define classeshpp
using namespace std;
using namespace sf;
int r = 110;
int g = 237;
int b = 35;
class game 
{

private: 
    int state;
    int speed;

public: 

    int getSpeed()
    {
        return speed;
    }

    void setSpeed(int value)
    {
        speed = value;
    }

    int getGameState()
    {
        return state;
    }

    void setGameState(int value)
    {
        state = value;
    }

    game(): state{0}, speed{120}
    {
        cout << "It's time to start the game!" << endl;
    }

    game(int speed): state{0}
    {
        this->speed = speed;
    }

};

    game game;
    int length = 2; 
    int score = 0; 
class cell 
{
    private:
    int size;
    int objectInside;
    RectangleShape square;

    public:

    int getSize() 
    {
        return size;
    }

    void setSize(int value)
    {
        this->size = value;
    }

    RectangleShape getShape()
    {
        return square;
    }

    void setObject(int objCode)
    {
        this->objectInside = objCode;
    }

    int getObject()
    {
        return objectInside;
    }

    cell()
    {
    }

    cell(int thick) : size{740}, objectInside{0}
    {
        square.setSize(Vector2f(size, size));
        square.setFillColor(Color:: Black);
        square.setOutlineColor(Color:: White);
        square.setOutlineThickness(thick);
        square.setPosition(400.f, 100.f);
    }
    cell(int size, int border, double x, double y) : objectInside{0}
    {
        square.setSize(Vector2f(size, size));
        this->size = size;
        square.setFillColor(Color:: Black);
        square.setOutlineColor(Color:: White);
        square.setOutlineThickness(border);
        square.setPosition(x*size + 400.f, y*size + 100.f);
    }
};

enum class Direction
{
    Up,
    Down,
    Right,
    Left,
};

class Snake
{
    private:
    int x;
    int y;
    Direction direction;

    public:
    void setX(int x)
    {
        this->x = x;
    }

    void setY(int y)
    {
        this->y = y;
    }

    void setD(Direction direction)
    {
        this->direction = direction;
    }

    Direction getDirection()
    {
        return this->direction;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    Direction getD() 
    {
        return this->direction;
    }

    void changeDir(Direction direction)
    {
        if (((int)direction + (int)this->direction) != 1 && ((int)direction + (int)this->direction) != 5)
            this->direction = direction;
    }

    void virtual print(RenderWindow *window) = 0;

    Snake()
    {
        this->x = 0;
        this->y = 0;
        this->direction = Direction:: Down;
    }
    Snake(int x, int y, Direction direction)
    {
        this->x = x;
        this->y = y;
        this->direction = direction;
    }
};

class head: public Snake
{
    public:

    void print(RenderWindow *window) override
    {
        RectangleShape head(Vector2f(750/20.f, 750/20.f));
        head.setFillColor(Color(r, g, b));
        CircleShape eye(5);
        eye.setFillColor(Color(35, 42, 237));
        head.setPosition(750/20 * getX() + 400.f, 750/20 * getY() + 100.f);
        eye.setPosition(Vector2f(750/20 * getX() + 413.f, 750/20 * getY() + 113.f));
        window->draw(head);
        window->draw(eye);

    }

    head()
    {
        setX(0);
        setY(1);
        setD(Direction::Down);
    }
    head(int x, int y, Direction direction)
    {
        setX(x);
        setY(y);
        setD(direction);
    }

};

class body: public Snake
{
    public:
    void print(RenderWindow *window) override
    {
        ConvexShape print;
        print.setPointCount(8);
        print.setPoint(0, Vector2f(750/20 * getX() + 411.f, 750/20 * getY() + 137.f));
        print.setPoint(1, Vector2f(750/20 * getX() + 400.f, 750/20 * getY() + 123.f));
        print.setPoint(2, Vector2f(750/20 * getX() + 424.f, 750/20 * getY() + 108.f));
        print.setPoint(3, Vector2f(750/20 * getX() + 411.f, 750/20 * getY() + 100.f));
        print.setPoint(4, Vector2f(750/20 * getX() + 426.f, 750/20 * getY() + 100.f));
        print.setPoint(5, Vector2f(750/20 * getX() + 437.f, 750/20 * getY() + 114.f));
        print.setPoint(6, Vector2f(750/20 * getX() + 412.f, 750/20 * getY() + 128.f));
        print.setPoint(7, Vector2f(750/20 * getX() + 426.f, 750/20 * getY() + 137.f));
        print.setFillColor(Color(79, 122, 36));
        RectangleShape body(Vector2f(750/20.f, 750/20.f));
        body.setFillColor(Color(r, g, b));
        body.setPosition(750/20 * getX() + 400.f, 750/20 * getY() + 100.f);
        window->draw(body);
        window->draw(print);
    }
        body()
        {
            setX(0);
            setY(0);
            setD(Direction::Down);
        }
        
        body(int x, int y, Direction direction)
        {
            setX(x);
            setY(y);
            setD(direction);
        }
};

class tail: public Snake
{
    public:
        void print(RenderWindow *window) override
        {
            RectangleShape tail(Vector2f(750/20.f, 750/20.f));
            tail.setFillColor(Color(r, g, b));
            tail.setPosition(750/20 * getX() + 400.f, 750/20 * getY() + 100.f);
            window->draw(tail);
        }

        tail()
        {
            setX(0);
            setY(0);
            setD(Direction::Down);
        }
        
        tail(int x, int y, Direction direction)
        {
            setX(x);
            setY(y);
            setD(direction);
        }
};

class Fruits
{
    private:
    int x;
    int y;

    public:

    int getX()
    {
        return x;
    }

    void setX(int x)
    {
        this->x = x;
    }

    int getY()
    {
        return y;
    }

    void setY(int y)
    {
        this->y = y;
    }

    void virtual print(RenderWindow *window) = 0;

    void virtual effect(Snake *array[]) = 0;
};
class apple: public Fruits
{
    public:

    void print(RenderWindow *window) override
    {
        CircleShape apple(11);
        apple.setPosition(750/20 * getX() + 404.f, 750/20 * getY() + 113.f);
        apple.setFillColor(Color(240, 19, 19));
        apple.setScale(1.2,1);
        RectangleShape tail(Vector2f(5.f, 10.f));
        tail.setPosition(750/20 * getX() + 419.f, 750/20 * getY() + 103.f);
        tail.setFillColor(Color(138, 74, 35));
        tail.rotate(13);
        CircleShape leaf(3);
        leaf.setPosition(750/20 * getX() + 421.f, 750/20 * getY() + 111.f);
        leaf.setScale(1,2);      
        leaf.rotate(-130);
        leaf.setFillColor(Color(69, 204, 53));
        window->draw(tail);
        window->draw(leaf);
        window->draw(apple);
    }

    void effect(Snake *array[]) override
    {
        r = 110;
        g = 237;
        b = 35;
        score+=150;
        if(game.getSpeed() < 120)
            game.setSpeed(game.getSpeed()+5);
        if(game.getSpeed() > 120)
            game.setSpeed(game.getSpeed()-5);
    }
    apple(cell cells[][20])
    {
    while(true)
    {
        int x = rand()%20;
        int y = rand()%20;
        if(cells[y][x].getObject() == 0)
            {
                setX(x);
                setY(y);
                cells[y][x].setObject(1);
                break;
            }
    }
    }
    apple(int x, int y)
    {
        setX(x);
        setY(y);
    }
};

class pineapple: public Fruits
{
    public:

    void print(RenderWindow *window) override
    {
        CircleShape pineapple(11);
        pineapple.setPosition(750/20 * getX() + 406.f, 750/20 * getY() + 108.f);
        pineapple.setFillColor(Color(219, 217, 63));
        pineapple.setScale(1,1.3);
        CircleShape leaf(5,3);
        leaf.setFillColor(Color(69, 204, 53));
        leaf.rotate(-50);
        leaf.setPosition(750/20 * getX() + 401.f, 750/20 * getY() + 106.f);
        leaf.setScale(1,2);
        CircleShape leaf1(5,3);
        leaf1.setFillColor(Color(69, 204, 53));
        leaf1.rotate(50);
        leaf1.setPosition(750/20 * getX() + 426.f, 750/20 * getY() + 100.f);
        leaf1.setScale(1,2);
        CircleShape leaf2(6,3);
        leaf2.setFillColor(Color(69, 204, 53));
        leaf2.setPosition(750/20 * getX() + 412.f, 750/20 * getY() + 98.f);
        leaf2.setScale(1,2);
        window->draw(pineapple);
        window->draw(leaf);
        window->draw(leaf1);
        window->draw(leaf2);
    }

    void effect(Snake *array[]) override
    {
        r = 219;
        g = 217;
        b = 63;
        score+=50;
        if(game.getSpeed() > 160)
            game.setSpeed(160);
        if(game.getSpeed() <= 160 && game.getSpeed() > 120)
            game.setSpeed(game.getSpeed() -10);
        if(game.getSpeed() <= 120)
            game.setSpeed(game.getSpeed() - 5);
        if(game.getSpeed() > 80)
            game.setSpeed(80);
    }
    pineapple(cell cells[][20])
    {
    while(true)
    {
        int x = rand()%20;
        int y = rand()%20;
        if(cells[y][x].getObject() == 0)
            {
                setX(x);
                setY(y);
                cells[y][x].setObject(1);
                break;
            }
    }
    }
    pineapple(int x, int y)
    {
        setX(x);
        setY(y);
    }

};

class blueberry: public Fruits
{
    public:
    void print(RenderWindow *window) override
    {
        CircleShape blueberry(15);
        blueberry.setPosition(750/20 * getX() + 402.5f, 750/20 * getY() + 103.5f);
        blueberry.setFillColor(Color(104, 66, 207));
        CircleShape blick(3);
        blick.setScale(1,2.5);
        blick.setPosition(750/20 * getX() + 420.f, 750/20 * getY() + 107.f);
        blick.rotate(-15);
        window->draw(blueberry);
        window->draw(blick);
    }

    void effect(Snake *array[]) override
    {
        r = 104;
        g = 66;
        b = 207;
        score+=225;
        if(game.getSpeed() < 120)
            game.setSpeed(120);
        else if(game.getSpeed() >= 120 && game.getSpeed() < 200)
            game.setSpeed(game.getSpeed() + 10);
        
        int d = rand()%4;
        switch(d)
        {
            case 0:
                array[0]->changeDir(Direction:: Up);
                break;
            case 1:
                array[0]->changeDir(Direction:: Down);
                break;
            case 2:
                array[0]->changeDir(Direction:: Right);
                break;
            case 3:
                array[0]->changeDir(Direction:: Left);
                break;
        }
    }

    blueberry(cell cells[][20])
    {
    while(true)
    {
        int x = rand()%16;
        int y = rand()%16;
        if(cells[y+2][x+2].getObject() == 0)
            {
                setX(x+2);
                setY(y+2);
                cells[y+2][x+2].setObject(1);
                break;
            }
    }
    }
    blueberry(int x, int y)
    {
        setX(x);
        setY(y);
    }
};

#endif