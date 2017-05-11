#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>

class Label : public QLabel
{
    Q_OBJECT

    QPixmap pix;
//    int x, y;
    int n;
    double h;
    double x[1000];
    double y[1000];
    double a_y[1000];
    double b_y[1000];
    double c_y[1000];
    double a_x[1000];
    double b_x[1000];
    double c_x[1000];
    void yset_b(int level, double alpha, double betta);
    void yset_b();
    void yset_a();
    void yset_c();
    void xset_b(int level, double alpha, double betta);
    void xset_b();
    void xset_a();
    void xset_c();

public:
    Label(QWidget *parent = 0);
    void draw();
    void mousePressEvent(QMouseEvent *ev);

signals:

public slots:
};

#endif // LABEL_H
