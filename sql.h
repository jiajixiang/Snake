#ifndef SQL_H
#define SQL_H


#include "head.h"

class information;

class sql
{
public:
    sql();
    QString User_Write(int score);
    bool Ranking_Select();
    bool Recording_Select();
};

#endif // SQL_H
