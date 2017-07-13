#ifndef ADDMANGADIALOG_H
#define ADDMANGADIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>

namespace Ui {
class addMangaDialog;
}

class addMangaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addMangaDialog(QWidget *parent = 0);
    ~addMangaDialog();

    //variables for passing data to main window
    QString getSeries();
    QString getBookNumber();
    QString getPath();

private slots:
    void on_browseButton_clicked();

private:
    Ui::addMangaDialog *ui;

};

#endif // ADDMANGADIALOG_H
