#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui
{
    class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget* = 0);
    virtual ~About();

private:
    Ui::About *ui;
};

#endif
