#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageloader.h"
#include <QPixmap>
#include <QMessageBox>
#include <qDebug>
#include <QFileDialog>
#include "addmangadialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Allow use of mouse panning/kinetic-scroll on images
    ui->pageDisplay->setDragMode(QGraphicsView::ScrollHandDrag);

    //Set alignment of images
    ui->pageDisplay->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    //Remove default padding for images
    ui->pageDisplay->setContentsMargins(0,0,0,0);

    //Remove default window padding
    centralWidget()->layout()->setContentsMargins(0,0,0,0);

    //Hide statusbar and toolbar
    statusBar()->hide();
    ui->mainToolBar->hide();

    //Maximize window on startup
    QWidget::showMaximized();

    //Load Books
    bookLoader.loadBooks();
    reloadMangaList();


}

//Destructor for main window
MainWindow::~MainWindow()
{
    bookLoader.saveBooks();
    delete ui;
}

//Load manga list
void MainWindow::reloadMangaList()
{
    //clear list
    ui->mangaListWidget->clear();

    //Get books
    vector<Book> b = bookLoader.getAllBooks();

    //Check if empty
    if(!b.empty()){
        //Load books to list
        for(int i=0; i < (int)(b.size()); i++){
            ui->mangaListWidget->addItem(b[i].getTitle());
        }
    }
}

void MainWindow::on_addMangaButton_clicked()
{
    //Create dialogue
    addMangaDialog dlg;

    //Get data for manga via dialogue
    if (dlg.exec() == QDialog::Accepted) {

        //Check if fields are empty
        if(!dlg.getPath().trimmed().isEmpty() && !dlg.getSeries().trimmed().isEmpty() && !dlg.getBookNumber().trimmed().isEmpty()){

            //Add new manga
            bookLoader.addBook(dlg.getPath(), dlg.getSeries(), dlg.getBookNumber().toInt());
        } else {

            //Send warning
            QMessageBox::warning(this, "Warning", "All fields must be filled");
            return;
        }

        reloadMangaList();
    }
}


void MainWindow::on_deleteMangaButton_clicked()
{
    //Get selected title
    QModelIndex listIndex = ui->mangaListWidget->currentIndex();
    QString deleteBookTitle = listIndex.data(Qt::DisplayRole).toString();

    //Delete book
    bookLoader.deleteBook(deleteBookTitle);

    //Reload
    reloadMangaList();

}
