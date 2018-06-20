#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "head.h"
class QGraphicsScene;
class QKeyEvent;

class Snake;
class Food;
class Wall;
class information;
class sql;

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);
    ~GameController();

    void snakeAteFood(Snake *snake, Food *food);
    void snakeHitWall(Snake *snake, Wall *wall);
    void snakeAteItself(Snake *snake);
    void snakeSleep();
public slots:
    void pause();
    void resume();
    void gameOver();

protected:
     bool eventFilter(QObject *object, QEvent *event);

private:
    void handleKeyPressed(QKeyEvent *event);
    void addNewFood();

    QTimer timer;
    QGraphicsScene &scene;
    bool flag;
    Snake *snake;
};

#endif // GAMECONTROLLER_H
