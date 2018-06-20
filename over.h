#ifndef OVER_H
#define OVER_H
#include"head.h"
class over
{
public:
    over();
    bool Dialog_box(int score);
private:
    QDialog *dialog;
    QMessageBox *message;
};

#endif // OVER_H
