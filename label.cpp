#include "label.h"

#include <QPainter>
#include <iostream>

Label::Label(QWidget *parent) :
    QLabel(parent)
{
    b_x[0] = 0;
    b_y[0] = 0;
    h = 1;
    n = 0;
    pix = QPixmap(1000, 1000);
    pix.fill(Qt::white);
    setPixmap(pix);
}

void
Label::yset_b()
{
    double a_i, b_i, c_i;
    double alph[n+1];
    double f[n+1];
    double bett[n+1];
    alph[0] = 0;
    bett[0] = 0;
    f[0] = 0;
    f[n-1] = 0;
    for (int i = 0; i <= n-1; i++) {
        if (i == 0 || i == n-1) {
            a_i = 0;
            b_i = 1;
            c_i = 0;
            f[i] = 0;
        } else {
            a_i = 1;
            b_i = 4;
            c_i = 1;
            f[i] = 3 * (y[i-1] - 2 * y[i] + y[i+1]);
        }
        alph[i+1] = - (c_i / (a_i * alph[i] + b_i) );
        bett[i+1] = (f[i] - a_i * alph[i]) / (a_i * alph[i] + b_i);
    }
    for (int i = n-1; i >= 0; i--) {
        b_y[i] = alph[i+1] * b_y[i+1] + bett[i+1];
    }
}

void
Label::yset_a()
{
    for(int i = 0; i < n-1; i++) {
        a_y[i] = (b_y[i+1] - b_y[i]) / 3 / h;
    }
}

void
Label::yset_c()
{
    for(int i = 0; i < n-1; i++) {
        c_y[i] = (y[i+1] - y[i]) / h - (b_y[i+1] + 2 * b_y[i]) * h / 3;
    }
}

void
Label::xset_b()
{
    double a_i, b_i, c_i;
    double alph[n+1];
    double f[n+1];
    double bett[n+1];
    alph[0] = 0;
    bett[0] = 0;
    f[0] = 0;
    f[n-1] = 0;
    for (int i = 0; i <= n-1; i++) {
        if (i == 0 || i == n-1) {
            a_i = 0;
            b_i = 1;
            c_i = 0;
            f[i] = 0;
        } else {
            a_i = 1;
            b_i = 4;
            c_i = 1;
            f[i] = 3 * (x[i-1] - 2 * x[i] + x[i+1]);
        }
        alph[i+1] = - (c_i / (a_i * alph[i] + b_i) );
        bett[i+1] = (f[i] - a_i * alph[i]) / (a_i * alph[i] + b_i);
    }
    for (int i = n-1; i >= 0; i--) {
        b_x[i] = alph[i+1] * b_x[i+1] + bett[i+1];
    }
}

void
Label::xset_a()
{
    for(int i = 0; i < n-1; i++) {
        a_x[i] = (b_x[i+1] - b_x[i]) / 3;
    }
}

void
Label::xset_c()
{
    for(int i = 0; i < n-1; i++) {
        c_x[i] = (x[i+1] - x[i]) - a_x[i] - b_x[i];
    }
}

void Label::draw()
{
    //test();
    QPainter painter(&pix);
    int radius = 10;
    pix.fill(Qt::white);
    setPixmap(pix);
    painter.setBrush(QBrush(Qt::black));
    painter.setRenderHint(QPainter::Antialiasing, true);
    for (int i = 0; i < n; i++) {
        painter.drawEllipse(x[i] - radius/2,
                            y[i] - radius/2,
                            radius, radius);
    }
    if (n > 1) {
        painter.setPen(QPen(Qt::black,3));
        xset_b();
        xset_a();
        xset_c();
        yset_b();
        yset_a();
        yset_c();
        for (int t = 0; t < n-1; t++) {
            double h = 0.01;
            double pred_x = x[t];
            double pred_y = y[t];
            double cur_x, cur_y;
            for (int i = 1; i <= 100; i++) {
                double tau = t + i*h;
                cur_x = a_x[t] * (tau - t) * (tau - t) * (tau - t) +
                        b_x[t] * (tau - t) * (tau - t) +
                        c_x[t] * (tau - t) + x[t];
                cur_y = a_y[t] * (tau - t) * (tau - t) * (tau - t) +
                        b_y[t] * (tau - t) * (tau - t) +
                        c_y[t] * (tau - t) + y[t];
                painter.drawLine(QPoint(pred_x,pred_y),QPoint(cur_x,cur_y));
                pred_x = cur_x;
                pred_y = cur_y;
            }
        }
    }
}


void Label::mousePressEvent(QMouseEvent *ev)
{
    n++;
    x[n - 1] = ev -> x();
    y[n - 1] = ev -> y();
    b_x[n - 1] = 0;
    b_y[n - 1] = 0;
    draw();
    setPixmap(pix);
}
