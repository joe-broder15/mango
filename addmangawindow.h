#ifndef ADDMANGAWINDOW_H
#define ADDMANGAWINDOW_H

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

private:
    Ui::addMangaWindow *ui;
};

#endif // ADDMANGAWINDOW_H
