#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>

namespace Ui {
class search;
}

class search : public QDialog
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = 0);
    ~search();

private:
    Ui::search *ui;
};

#endif
