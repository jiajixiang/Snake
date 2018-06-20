#include "sql.h"

#include "information.h"
information get;

sql::sql()
{
}
QString sql::User_Write(int score){
    QSqlDatabase db;
    QSqlDatabase::drivers();
    QString e="";
    e.clear();
    /* if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else*/
    db =QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("118.89.51.72");
    db.setDatabaseName("snake");
    db.setUserName("pig");
    db.setPassword("123456");
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString time=current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    QString name=get.getName();
    name.trimmed();
    QString ip=get.getIP();
    QString mac=get.getMac();
    bool flag=false;
    if(db.open()){
        QSqlQuery query(db);
        QString in="insert into user values('";
        in.insert(in.size(),mac);
        in.insert(in.size(),"','");
        in.insert(in.size(),name);
        in.insert(in.size(),"');");
        if(query.exec(in)){
            flag=true;
            e="insert into user    ";
        }

        QString two="insert into game_record values(";
        two.insert(two.size(),"'");
        two.insert(two.size(),mac);
        two.insert(two.size(),"','");
        two.insert(two.size(),name);
        two.insert(two.size(),"','");
        two.insert(two.size(),ip);
        two.insert(two.size(),"','");
        two.insert(two.size(),time);
        two.insert(two.size(),"',");
        two.insert(two.size(),QString::number(score, 10));
        two.insert(two.size(),");");
        if(query.exec(two)){
            flag=true;
            e.insert(e.size(),"insert into game_record     ");
        }

        bool fl=false;
        QString se="select * from ranking where r_mac='";
        se.insert(se.size(),mac);
        se.insert(se.size(),"';");
        // qDebug()<<se;
        if(query.exec(se)){
            while(query.next()){
                QString qs = query.value(3).toString();
                bool ok;
                int co=qs.toInt(&ok,10);
                if(co<score){
                    fl=true;
                    break;
                }
            }
            if(fl){
                QString fo="update ranking";
                QString to=" set r_score=";
                fo.insert(fo.size(),to);
                fo.insert(fo.size(),QString::number(score, 10));
                fo.insert(fo.size(),",r_time='");
                fo.insert(fo.size(),time);
                fo.insert(fo.size(),"' where r_mac='");
                fo.insert(fo.size(),mac);
                fo.insert(fo.size(),"';");
                QSqlQuery tb(db);
                if(tb.exec(fo)){
                    flag=true;
                    e.insert(e.size(),"update ranking     ");
                }
                else{
                    //  qDebug()<<fo;
                }
            }
            else{
                QString three="insert into ranking values('";
                three.insert(three.size(),mac);
                three.insert(three.size(),"','");
                three.insert(three.size(),name);
                three.insert(three.size(),"','");
                three.insert(three.size(),time);
                three.insert(three.size(),"',");
                three.insert(three.size(),QString::number(score, 10));
                three.insert(three.size(),");");
                QSqlQuery tb(db);
                if(tb.exec(three)){
                    flag=true;
                    e.insert(e.size(),"insert into ranking     ");
                }
            }
        }
        db.close();
    }
    else{
        e="Open failed";\
        qDebug() << db.lastError().text();
        qDebug() << QSqlDatabase::drivers();

        qDebug() << QCoreApplication::libraryPaths();
        qDebug( ("sb"));
    }
    return e;
}
bool sql::Ranking_Select(){
    int i=0;
    QTableWidget *table;
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("118.89.51.72");
    db.setDatabaseName("snake");
    db.setUserName("pig");
    db.setPassword("123456");
    if(!db.open())
        return false;
    QSqlQuery query(db);
    query.exec("select r_name,r_time,r_score from ranking order by r_score desc;");
    while (query.next()) {
        i++;
    }

    table = new QTableWidget(i,3);
    QStringList colLabs;
    colLabs<<"name"<<"time"<<"score";
    table->setHorizontalHeaderLabels(colLabs);
    table->resize(400, 200);
    table->setWindowTitle("Select Ranking");
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    //设置每一行的高度
    table->setRowHeight(0,20);
    //自动调整最后一列的宽度使它和表格的右边界对齐
    table->horizontalHeader()->setStretchLastSection(true);
    //设置表格的选择方式
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::DoubleClicked);

    if( query.exec("select r_name,r_time,r_score from ranking order by r_score desc;")){
        i=0;
        while(query.next()){
            QString q0 = query.value(0).toString();
            // pri.insert(pri.size(),q0);
            // pri.insert(pri.size()," \t");
            QString q1 = query.value(1).toString();
            // pri.insert(pri.size(),q1);
            // pri.insert(pri.size()," \t");
            QString q2 = query.value(2).toString();
            // pri.insert(pri.size(),q2);
            //  pri.insert(pri.size()," \n");
            QTableWidgetItem *item0, *item1,*item2;
            item0 = new QTableWidgetItem;
            item1 = new QTableWidgetItem;
            item2 = new QTableWidgetItem;
            table->setRowHeight(i,20);
            item0->setText(q0);
            table->setItem(i,0,item0);
            item1->setText(q1);
            table->setItem(i,1,item1);
            item2->setText(q2);
            table->setItem(i,2,item2);
            i++;
        }
    }
    db.close();
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->show();
    return true;
}

bool sql::Recording_Select(){
    int i=0;
    QTableWidget *table;
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("118.89.51.72");
    db.setDatabaseName("snake");
    db.setUserName("pig");
    db.setPassword("123456");
    if(!db.open())
        return false;
    QSqlQuery query(db);
    query.exec("select r_name,r_time,r_score from ranking order by r_score desc;");
    while (query.next()) {
        i++;
    }

    table = new QTableWidget(i,3);
    QStringList colLabs;
    colLabs<<"ip"<<"time"<<"score";
    table->setHorizontalHeaderLabels(colLabs);
    table->resize(400, 200);
    table->setWindowTitle("Select Recording");
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    //设置每一行的高度
    table->setRowHeight(0,20);
    //自动调整最后一列的宽度使它和表格的右边界对齐
    table->horizontalHeader()->setStretchLastSection(true);
    //设置表格的选择方式
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::DoubleClicked);
    QString se="select g_ip,g_time,g_score from game_record where g_mac='";
    se.insert(se.size(),get.getMac());
    se.insert(se.size(),"';");
    if( query.exec(se)){
        i=0;
        while(query.next()){
            QString q0 = query.value(0).toString();
            // pri.insert(pri.size(),q0);
            // pri.insert(pri.size()," \t");
            QString q1 = query.value(1).toString();
            // pri.insert(pri.size(),q1);
            // pri.insert(pri.size()," \t");
            QString q2 = query.value(2).toString();
            // pri.insert(pri.size(),q2);
            //  pri.insert(pri.size()," \n");
            QTableWidgetItem *item0, *item1,*item2;
            item0 = new QTableWidgetItem;
            item1 = new QTableWidgetItem;
            item2 = new QTableWidgetItem;
            table->setRowHeight(i,20);
            item0->setText(q0);
            table->setItem(i,0,item0);
            item1->setText(q1);
            table->setItem(i,1,item1);
            item2->setText(q2);
            table->setItem(i,2,item2);
            i++;
        }
    }
    db.close();
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->show();
    return true;
}
