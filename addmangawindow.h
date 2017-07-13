#ifndef ADDMANGAWINDOW_H
#define ADDMANGAWINDOW_H
#include <QLineEdit>

#include <QWidget>

namespace Ui {
class addMangaWindow;
}

class addMangaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit addMangaWindow(QWidget *parent = 0);
    ~addMangaWindow();

    //Elements
    QString seriesText;
    QString bookNumberText;
    QString pathText;

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::addMangaWindow *ui;
};

#endif // ADDMANGAWINDOW_H
