#include "gamecontroller.h"
#include "food.h"
#include "snake.h"
#include "information.h"
#include "sql.h"
sql yun;
information getM;
GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(*this))
{
    timer.start( 1000/16 );
    flag=0;
    Food *a1 = new Food(0, -50);
    scene.addItem(a1);

    scene.addItem(snake);
    //添加蛇和食物这俩个事物
    scene.installEventFilter(this);
    //事件过滤器
    resume();
}

GameController::~GameController()
{
}
//蛇吃食物
void GameController::snakeAteFood(Snake *snake, Food *food)
{
    scene.removeItem(food);
    delete food;

    addNewFood();
}
//蛇撞墙
void GameController::snakeHitWall(Snake *snake, Wall *wall)
{

}
//蛇撞自己
void GameController::snakeAteItself(Snake *snake)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}
void GameController::snakeSleep(){
    if(flag==0){

    }
}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        snake->setMoveDirection(Snake::MoveLeft);
        break;
    case Qt::Key_Right:
        snake->setMoveDirection(Snake::MoveRight);
        break;
    case Qt::Key_Up:
        snake->setMoveDirection(Snake::MoveUp);
        break;
    case Qt::Key_Down:
        snake->setMoveDirection(Snake::MoveDown);
        break;
    }
}

void GameController::addNewFood()
{
    int x, y;

    do {
        x = (int) (qrand() % 100) / 10;
        y = (int) (qrand() % 100) / 10;

        x *= 10;
        y *= 10;
    } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));

    Food *food = new Food(x , y);
    scene.addItem(food);
}

int Snake::getGrowing(){
    QString s = QString::number(tail.size());
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    QMessageBox *message;
    QString en=yun.User_Write(tail.size());
    if(en[0]!='O'){
        message=new QMessageBox(QMessageBox::NoIcon, "结束",
                                "用户名称： "+getM.getName()+
                                "\n娱乐时间： "+current_date+
                                "\n用户成绩："+s+"\n"+en

                                );
    }
    else{
        message=new QMessageBox(QMessageBox::NoIcon, "结束",
                                "网络连接失败\n请检查您的网络"
                                +en
                                );
    }
    message->setIconPixmap(QPixmap(":/new/prefix/huaji.jpg"));
    message->exec();
    //yun.Ranking_Select();
    return 1;
}

void GameController::gameOver()
{
    if(snake->getGrowing()){
        snake = new Snake(*this);
        scene.clear();
        scene.addItem(snake);
        addNewFood();
    }
}

void GameController::pause()
{
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
}
//pause()和resume()函数很简答：我们只是连接或者断开定时器的信号
void GameController::resume()
{
    connect(&timer, SIGNAL(timeout()),
            &scene, SLOT(advance()));
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}
