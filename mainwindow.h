#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "head.h"
class QGraphicsScene;
class QGraphicsView;
class  sql;

class GameController;

#include<QMessageBox>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void adjustViewSize();
private:
    void initScene();
    void initSceneBackground();
    void view_rank();
    void view_data();
    void view_help();
    sql *mysql;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QAction *saveAction;
    QAction *openAction;
    QAction *openACtion;
    GameController *game;
};

#endif // MAINWINDOW_H
