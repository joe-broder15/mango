#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageloader.h"
#include <QPixmap>
#include <QMessageBox>
#include <qDebug>
#include <QFileDialog>
// /Users/admin/Desktop/testManga

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

}

//Destructor for main window
MainWindow::~MainWindow()
{
    bookLoader.saveBooks();
    delete ui;
}

//Method to set page image to that for the current page
void MainWindow::setImageForPage()
{
    //Clear the current image from the scene
    scene->clear();

    //Set the current scene image to the image for the current page
    scene->addPixmap(imageloader.getPage(imageloader.getCurrentPage()));

    //Set the scene to the size of the current image (for scrolling purposes)
    scene->setSceneRect(0, 0, imageloader.getPage(imageloader.getCurrentPage()).width(),
                       imageloader.getPage(imageloader.getCurrentPage()).height());

    //Set the graphicsView scene to the one we just modified
    ui->pageDisplay->setScene(scene);
}

//Get manga button
void MainWindow::on_getMangaButton_clicked()
{
    //Open dialogue to browse for a path, then load it as a book
    imageloader.loadBook(QFileDialog::getExistingDirectory());

    //Reset current page
    imageloader.setCurrentPage(0);

    //Reset page label
    ui->pageLabel->setText("1/" + QString::number(imageloader.getLength()));

    //Set page image
    this->setImageForPage();
}

//Next page
void MainWindow::on_nextPageButton_clicked()
{
    //If there is currently no manga loaded, give a dialogue saying so
    if(imageloader.getLength() == 0){
        QMessageBox::critical(this, "No manga", "Please select a manga!");
        return;

    // if currently on last page, give dialogue saying so
    } else if(imageloader.getCurrentPage() == imageloader.getLength() - 1){
        QMessageBox::information(this, "Finished", "You have finished this manga!");

    //Otherwise, show next page
    } else {

        //Increase current page by 1
        int currentPage = imageloader.getCurrentPage() + 1;
        imageloader.setCurrentPage(currentPage);

        //Reset page label
        ui->pageLabel->setText(QString::number(currentPage + 1) + "/" + QString::number(imageloader.getLength()));

        //Set image
        this->setImageForPage();
    }
}

//Previous Page
void MainWindow::on_previousPageButton_clicked()
{
    //Warning for no manga currently loaded
    if(imageloader.getLength() == 0){
        QMessageBox::critical(this, "No manga", "Please select a manga!");
        return;

    //Warning for current page is already first page
    }else if(imageloader.getCurrentPage() == 0){
        QMessageBox::critical(this, "First Page", "You are already on the first page!");
        return;

    //Otherwise, show previous page
    } else {

        //Decrease Page by 1
        int currentPage = imageloader.getCurrentPage() - 1;
        imageloader.setCurrentPage(currentPage);

        //Reset label
        ui->pageLabel->setText(QString::number(currentPage+1) + "/" + QString::number(imageloader.getLength()));

        //Set Image
        this->setImageForPage();
    }
}

//Page Jump
void MainWindow::on_pageJumpButton_clicked()
{
    //Dialogue for no page or negative page number
    if(ui->pageJumpLineEdit->text().toInt() < 1){
        QMessageBox::critical(this, "Page out of range", "Page number must be greater than zero!");
        return;

    //Dialogue for page too long
    } else if(ui->pageJumpLineEdit->text().toInt() > imageloader.getLength() - 1){
        QMessageBox::information(this, "Page out of range", "Page number must be less than or equal to " +
                             QString::number(imageloader.getLength()));

    //Otherwise jump to page
    } else {

        //Set Number
        int currentPage = ui->pageJumpLineEdit->text().toInt() - 1;
        imageloader.setCurrentPage(currentPage);

        //Set Label
        ui->pageLabel->setText(QString::number(currentPage+1) + "/" + QString::number(imageloader.getLength()));

        //Reset Image
        this->setImageForPage();
    }
}

//Zoom in
void MainWindow::on_zoomInButton_clicked()
{
    //Reload image and increase zoom
    imageloader.increaseScaleFactor();
    this->setImageForPage();
}

//Zoom out
void MainWindow::on_zoomOutButton_clicked()
{
    //Reload image and decrease zoom
    imageloader.decreaseScaleFactor();
    this->setImageForPage();
}

//Reset Zoom
void MainWindow::on_zoomResetButton_clicked()
{
    //Reload image and set zoom to 1
    imageloader.setScaleFactor(1);
    this->setImageForPage();
}

//First Page
void MainWindow::on_firstPageButton_clicked()
{
    //Set Page
    imageloader.setCurrentPage(0);

    //Set Label
    ui->pageLabel->setText("0/" + QString::number(imageloader.getLength()));

    //Set Image
    this->setImageForPage();
}

//Last Page
void MainWindow::on_lastPageButton_clicked()
{
    //Set Page
    imageloader.setCurrentPage(imageloader.getLength() - 1);

    //Set Label
    ui->pageLabel->setText(QString::number(imageloader.getLength()) + "/" + QString::number(imageloader.getLength()));

    //Set Image
    this->setImageForPage();
}
