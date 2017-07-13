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

void addMangaWindow::on_pushButton_3_clicked()
{
    bookNumberText = ui->bookNumberLineEdit->text();
    pathText = ui->pathLineEdit->text();
    seriesText = ui->seriesLineEdit->text();
}
