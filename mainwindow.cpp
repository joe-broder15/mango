#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <qDebug>
#include <QFileDialog>
#include "addmangadialog.h"
#include <QMessageBox>
#include <QShortcut>
#include <QtConcurrent/QtConcurrentRun>

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

    //set only numbers for manga jump text field
    ui->pageJumpLineEdit->setValidator( new QIntValidator(0, 99999, this) );

    //Graphics view background color
    ui->pageDisplay->setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));

    //set up thumbnail widget
    ui->thumbnailListWidget->setViewMode(QListWidget::IconMode);
    ui->thumbnailListWidget->setIconSize(QSize(200,200));
    ui->thumbnailListWidget->setResizeMode(QListWidget::Adjust);
    ui->thumbnailListWidget->setFlow(QListWidget::LeftToRight);

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

//Load current page
void MainWindow::loadCurrentPage()
{
    //Clear the scene
    scene->clear();

    //Scale image
    double s = bookLoader.getScaleFactor();
    QPixmap pic = bookLoader.getCurrentBook()->getPage(bookLoader.getCurrentBook()->getCurrentPage());
    pic = pic.scaled(pic.size() * s);

    //Set image and scene rect
    scene->addPixmap(pic);
    scene->setSceneRect(0, 0, pic.width(), pic.height());
    ui->pageDisplay->setScene(scene);

    //Set label
    ui->pageLabel->setText(QString::number(bookLoader.getCurrentBook()->getCurrentPage() + 1)+
                           "/"+QString::number(bookLoader.getCurrentBook()->getSize()));
    //Set thumbnail
    ui->thumbnailListWidget->setCurrentItem(ui->thumbnailListWidget->item(bookLoader.getCurrentBook()->getCurrentPage()));
}

//Add manga
void MainWindow::on_addMangaButton_clicked()
{
    //Create dialogue
    addMangaDialog dlg;

    //Get data for manga via dialogue
    if (dlg.exec() == QDialog::Accepted) {

        //Check for less than zero number
        if(dlg.getBookNumber().toInt() <= 0){
            QMessageBox::warning(this, "Warning", "Number must be greater than zero");
            return;
        }

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

//Delete manga
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

//Next Page
void MainWindow::on_nextPageButton_clicked()
{
    //check for book existing
    if(bookLoader.getCurrentBook()->getBookNumber() == 0){
        QMessageBox::warning(this, "Warning", "Please select a manga!");

    //Check for range
    } else if(bookLoader.getCurrentBook()->getCurrentPage() ==
              bookLoader.getCurrentBook()->getSize()-1){

        return;

    } else {
        //Set page
        bookLoader.getCurrentBook()->setCurrentPage(bookLoader.getCurrentBook()->getCurrentPage()+1);
        loadCurrentPage();
    }
}

//Previous Page
void MainWindow::on_previousPageButton_clicked()
{
    //check for book existing
    if(bookLoader.getCurrentBook()->getBookNumber() == 0){
        QMessageBox::warning(this, "Warning", "Please select a manga!");

    //Check for range
    } else if(bookLoader.getCurrentBook()->getCurrentPage() ==0){

        return;

    } else {
        //Set page
        bookLoader.getCurrentBook()->setCurrentPage(bookLoader.getCurrentBook()->getCurrentPage()-1);
        loadCurrentPage();
    }
}

//First Page
void MainWindow::on_firstPageButton_clicked()
{
    //check for book existing
    if(bookLoader.getCurrentBook()->getBookNumber() == 0){
        QMessageBox::warning(this, "Warning", "Please select a manga!");

    //Check for range
    } else {
        //Set page
        bookLoader.getCurrentBook()->setCurrentPage(0);
        loadCurrentPage();
    }
}

//Last Page
void MainWindow::on_lastPageButton_clicked()
{
    //check for book existing
    if(bookLoader.getCurrentBook()->getBookNumber() == 0){
        QMessageBox::warning(this, "Warning", "Please select a manga!");

    //Check for range
    } else {
        //Set page
        bookLoader.getCurrentBook()->setCurrentPage(bookLoader.getCurrentBook()->getSize()-1);
        loadCurrentPage();
    }
}

//Page Jump
void MainWindow::on_pageJumpButton_clicked()
{
    //check for book existing
    if(bookLoader.getCurrentBook()->getBookNumber() == 0){
        QMessageBox::warning(this, "Warning", "Please select a manga!");

    //Check for range
    } else if(ui->pageJumpLineEdit->text().toInt() <= 0){

        QMessageBox::warning(this, "Warning", "Page can't be less than one!");
        return;

    //Again, check for range
    } else if(ui->pageJumpLineEdit->text().toInt() > bookLoader.getCurrentBook()->getSize()){

        QMessageBox::warning(this, "Warning", "Page number too large!");
        return;

    } else{
        //Set page
        bookLoader.getCurrentBook()->setCurrentPage(ui->pageJumpLineEdit->text().toInt()-1);
        loadCurrentPage();
    }
}

//Reset Scale/Zoom
void MainWindow::on_zoomResetButton_clicked()
{
    if(bookLoader.getCurrentBook()->getBookNumber() == 0){
        return;
    }

    bookLoader.setScaleFactor(1);
    loadCurrentPage();
}

//Increase Scale
void MainWindow::on_zoomInButton_clicked()
{
    if(bookLoader.getCurrentBook()->getBookNumber() == 0){
        return;
    }

    bookLoader.setScaleFactor(bookLoader.getScaleFactor() * 1.1);
    loadCurrentPage();
}

//Decrease Scale
void MainWindow::on_zoomOutButton_clicked()
{
    if(bookLoader.getCurrentBook()->getBookNumber() == 0){
        return;
    }
    bookLoader.setScaleFactor(bookLoader.getScaleFactor() * .9);
    loadCurrentPage();
}

//Thumbnail Gallery Clicked
void MainWindow::on_thumbnailListWidget_itemClicked(QListWidgetItem *item)
{
    bookLoader.getCurrentBook()->setCurrentPage(item->text().toInt() - 1);
    loadCurrentPage();
}

//Select manga
void MainWindow::on_mangaListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //Get selected book
    QString selectBookTitle = item->text();

    if(!selectBookTitle.trimmed().isEmpty()){

        //Set current book to selected book
        bookLoader.setCurrentBook(bookLoader.getBook(selectBookTitle));

        //Clear scene and set image to graphics  view
        bookLoader.getCurrentBook()->setCurrentPage(0);
        loadThumbNails();
        loadCurrentPage();


    }
}

//Load thumbnails to gallery USED FOR ASYNCHRONOUS LOADING
void MainWindow::loadThumbNails()
{
    ui->thumbnailListWidget->clear();
    for(int i=0; i < bookLoader.getCurrentBook()->getSize(); i++){
        ui->thumbnailListWidget->addItem(new QListWidgetItem(QIcon(bookLoader.getCurrentBook()->getPathForIndex(i)),
                                                         QString::number(i+1)));
    }
}

//Entering galleryview and scroll view based on window resizing
void MainWindow::on_thumbnailSplitter_splitterMoved(int pos, int index)
{
    //Check to keep scroll view
    if(ui->thumbnailListWidget->minimumHeight() == ui->thumbnailListWidget->height() && isGalleryView == false){

        return;

    //Check to keep galleryview
    } else if(ui->thumbnailListWidget->minimumHeight() < ui->thumbnailListWidget->height() && isGalleryView == true){

        return;
    //Check to set galleryview
    } else if(ui->thumbnailListWidget->minimumHeight() < ui->thumbnailListWidget->height() && isGalleryView == false){

        //Set values(specifically wrapping)
        ui->thumbnailListWidget->setWrapping(true);

        //set gallery mode to true
        isGalleryView = true;



    } else if(ui->thumbnailListWidget->minimumHeight() == ui->thumbnailListWidget->height() && isGalleryView == true){
        //Set values(specifically wrapping)
        ui->thumbnailListWidget->setWrapping(false);

        //set gallery mode to true
        isGalleryView = false;

    }
}
