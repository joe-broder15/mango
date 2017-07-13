#include "addmangadialog.h"
#include "ui_addmangadialog.h"
#include <QFileDialog>

addMangaDialog::addMangaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addMangaDialog)
{
    ui->setupUi(this);
}

addMangaDialog::~addMangaDialog()
{
    delete ui;
}

QString addMangaDialog::getSeries(){
    return ui->seriesLineEdit->text();
}

QString addMangaDialog::getBookNumber(){
    return ui->bookNumberLineEdit->text();
}

QString addMangaDialog::getPath(){
    return ui->pathLineEdit->text();
}

void addMangaDialog::on_browseButton_clicked(){
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    ui->pathLineEdit->setText(dir);
}
