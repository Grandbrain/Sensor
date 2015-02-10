#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>

namespace Ui
{
    class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget* = 0);
    ~Search();

public:
    QString GetAddress() const;
    quint16 GetPort() const;

private:
    Ui::Search* ui;
};

#endif
