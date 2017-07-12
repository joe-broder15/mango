#include "addmangawindow.h"
#include "ui_addmangawindow.h"

addMangaWindow::addMangaWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addMangaWindow)
{
    ui->setupUi(this);
}

addMangaWindow::~addMangaWindow()
{
    delete ui;
}
