#ifndef SNAKE_H
#define SNAKE_H

#include "head.h"
class GameController;
class information;

class Snake : public QGraphicsItem
{
public:
    enum Direction {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    Snake(GameController & controller);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void setMoveDirection(Direction direction);
    int getGrowing();
    int get_tail(){
        return tail.size();
    }


protected:
    void advance(int step);

private:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void handleCollisions();

    QPointF head;
    int speed,growing;
    QList<QPointF> tail;
    int tickCounter;
    Direction      moveDirection;
    GameController &controller;
};

#endif // SNAKE_H
