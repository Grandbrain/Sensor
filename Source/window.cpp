#include "window.h"
#include "search.h"
#include "ui_window.h"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
    connect(ui->buttonConnect, SIGNAL(released()), SLOT(SearchAddress()));
}

Window::~Window()
{
    delete ui;
}

void Window::SearchAddress()
{
    Search s;
    s.exec();
}
