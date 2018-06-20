#include "constants.h"
#include "gamecontroller.h"
#include "mainwindow.h"
#include "sql.h"
sql S;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameController(*scene, this))
{
    resize(610, 635);
    mysql=new sql;
    openAction = new QAction(tr("&查看我的游戏记录"), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("&Check my game history..."));

    openACtion = new QAction(tr("&查看成绩排名"), this);
    openACtion->setShortcuts(QKeySequence::Open);
    openACtion->setStatusTip(tr("&Check rankings..."));

    saveAction= new QAction(tr("&查看提示"), this);
    saveAction->setShortcuts(QKeySequence::Open);
    saveAction->setStatusTip(tr("&View Help..."));

    openAction->setShortcuts(QKeySequence::Open);
    openACtion->setShortcuts(QKeySequence::Open);
    saveAction->setShortcuts(QKeySequence::Open);
    QObject::connect(openAction,&QAction::triggered,this,&MainWindow::view_data);
    QObject::connect(openACtion,&QAction::triggered, this,&MainWindow::view_rank);
    QObject::connect(saveAction,&QAction::triggered, this,&MainWindow::view_help);
    QToolBar *toolBar = addToolBar(tr("Tool Bar 3"));
    toolBar->addAction(openAction);

    QToolBar *toolBar2 = addToolBar(tr("Tool Bar 2"));
    toolBar2->addAction(openACtion);

    QToolBar *toolBar3 = addToolBar(tr("Tool Bar 3"));
    toolBar3->addAction(saveAction);

    setWindowTitle(tr("简易贪吃蛇"));
    setCentralWidget(view);
    initScene();

    initSceneBackground();
    //view->centerOn(10,0);
    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
    //函数原型：static void QTimer::singleShot(int msec, QObject * receiver, const char * member);
        //ui.setupUi(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene()
{
    scene->setSceneRect(-100, -100, 210, 210);
    //设置场景范围
}

void MainWindow::initSceneBackground()
{
        QPixmap bg(TILE_SIZE, TILE_SIZE);
        //生成一个TILE_SIZE长宽的图像
        QPainter p(&bg);
        //对bg执行绘制操作
        p.setBrush(QBrush(Qt::gray));
        //颜色填充
        p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);
        //坐标，长宽，绘制一个矩形

        view->setBackgroundBrush(QBrush(bg));
        //view作为背景画刷，将bg铺满view
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
void MainWindow::view_data(){
    S.Recording_Select();
}
void MainWindow::view_rank(){
    S.Ranking_Select();
}
void MainWindow::view_help(){
    QMessageBox::information(this,
                             tr("提示"),
                             tr("<h1> <font color=red size=500>上下左右方向键控制蛇前进方向!</font></h1>"));
}
