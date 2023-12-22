#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <winuser.h>

const int width = GetSystemMetrics(SM_CXSCREEN);
const int heigth = GetSystemMetrics(SM_CYSCREEN);
int r = 110;
int g = 237;
int b = 35;

using namespace std;
using namespace sf;

class game 
{

private: 
    int state;
    int speed;

public: 

    getSpeed()
    {
        return speed;
    }

    setSpeed(int value)
    {
        speed = value;
    }

    getGameState()
    {
        return state;
    }

    setGameState(int value)
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
    // glob vars
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

    getSize() 
    {
        return size;
    }

    setSize(int value)
    {
        this->size = value;
    }

    RectangleShape getShape()
    {
        return square;
    }

    setObject(int objCode)
    {
        this->objectInside = objCode;
    }

    getObject()
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
    setX(int x)
    {
        this->x = x;
    }

    setY(int y)
    {
        this->y = y;
    }

    setD(Direction direction)
    {
        this->direction = direction;
    }

    Direction getDirection()
    {
        return this->direction;
    }

    getX()
    {
        return x;
    }

    getY()
    {
        return y;
    }

    Direction getD() 
    {
        return this->direction;
    }

    changeDir(Direction direction)
    {
        if (((int)direction + (int)this->direction) != 1 && ((int)direction + (int)this->direction) != 5)
            this->direction = direction;
    }

    virtual print(RenderWindow *window)
    {
    }

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

    print(RenderWindow *window) override
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
    print(RenderWindow *window) override
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
        print(RenderWindow *window) override
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

    getX()
    {
        return x;
    }

    setX(int x)
    {
        this->x = x;
    }

    getY()
    {
        return y;
    }

    setY(int y)
    {
        this->y = y;
    }

    virtual print(RenderWindow *window) = 0;

    virtual effect(Snake *array[]) = 0;
};
class apple: public Fruits
{
    public:

    print(RenderWindow *window) override
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

    effect(Snake *array[]) override
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

    print(RenderWindow *window) override
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

    effect(Snake *array[]) override
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
    print(RenderWindow *window) override
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

    effect(Snake *array[]) override
    {
        r = 104;
        g = 66;
        b = 207;
        score+=225;
        if(game.getSpeed() > 120)
            game.setSpeed(120);
        if(game.getSpeed() <= 160 && game.getSpeed() > 120)
            game.setSpeed(game.getSpeed() +10);
        if(game.getSpeed() > 160)
            game.setSpeed(game.getSpeed() + 5);
        if(game.getSpeed() > 200)
            game.setSpeed(200);
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
    blueberry(int x, int y)
    {
        setX(x);
        setY(y);
    }
};

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
                if(p < 33)
                    fruits[i] = new apple(cells);
                else if(p < 66)
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
                {
                    cout << "Игра началась!"<< endl;
                    game.setGameState(1);
                }
            }
            if (closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                closeButton.setFillColor(Color(200, 10, 20));
            if (!closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                closeButton.setFillColor(Color(220, 30, 45));
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    cout << "Выхожу..."<< endl;
                    game.setGameState(-1);
                }
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
        {
            cout << "Спасибо, что поиграли. Надеюсь, ещё увидимся!"<< endl;
            window.close();
        }
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
                {
                    cout << "Игра началась сначала!" << endl;
                    game.setGameState(1);
                }
            }
            if (closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                closeButton.setFillColor(Color(200, 10, 20));
            if (!closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                closeButton.setFillColor(Color(220, 30, 45));
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (closeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    cout << "Выходим..."<< endl;
                    game.setGameState(-1);
                }
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
        else if(game.getGameState() == 3)
        {
            Text text("", font, 100);
            text.setFillColor(Color(255, 25, 25)); 
            text.setString("Do not cheat!!");
            text.setPosition(width/2 -45, heigth/2 -heigth/5.5);
            Sleep(5000);
            game.setGameState(1);
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