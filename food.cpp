#include"constants.h"
#include"food.h"

static const qreal FOOD_RADIUS = 3;

Food::Food(qreal x, qreal y) {
    setPos(x, y);//指定该元素的坐标
    setData(GD_Type, GO_Food);
    //传输数据
}

QRectF Food::boundingRect() const {
    return QRectF(-TILE_SIZE, -TILE_SIZE, TILE_SIZE * 2, TILE_SIZE * 2);
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    //设置反走样
    painter->fillPath(shape(), Qt::red);
    /*
     用于保存画笔状态
    save()和restore()。save()就是保存下当前状态；restore()则恢复上一次保存的结果。
    这两个函数必须成对出现：QPainter使用栈来保存数据，
    每一次save()，将当前状态压入栈顶，restore()则弹出栈顶进行恢复。*/
    painter->restore();
}

QPainterPath Food::shape() const {
    QPainterPath p;
    p.addEllipse(QPointF(TILE_SIZE / 2, TILE_SIZE / 2), FOOD_RADIUS, FOOD_RADIUS);
    //绘制圆
    return p;
}
