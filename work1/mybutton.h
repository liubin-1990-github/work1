#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

public:
    int m_fd=0;



signals:

public slots:
protected:

};

#endif // MYBUTTON_H
