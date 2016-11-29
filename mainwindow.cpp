#include "framegenerator.h"
#include "mainwindow.h"
#include "reportageframegenerator.h"
#include "ui_mainwindow.h"
#include "weddingframegenerator.h"

#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QFileSystemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    container = NULL;
    model = NULL;
    borderStyle = WEDDING;
    ui->radioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionApri_triggered()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);

    if(!dialog.exec()) {
        return;
    }

    QStringList fileNames = dialog.selectedFiles();
    container = new QDir(fileNames[0]);
    filesList = container->entryInfoList(QStringList() << "*.jpg", QDir::NoFilter, QDir::Name);
    ui->txtOriginalDir->setText(fileNames[0]);

    model = new QFileSystemModel(this);
    model->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    model->setNameFilters(QStringList() << "*.jpg");
    model->setRootPath(container->absolutePath());

    ui->listView->setModel(model);
    ui->listView->setRootIndex(model->setRootPath(container->absolutePath()));

    qDebug() << model->rootPath();
}

QPixmap MainWindow::generateFrame(QImage image) {
    FrameGenerator* frameGenerator;
    if(borderStyle == WEDDING) {
        frameGenerator = new WeddingFrameGenerator(this);
    } else if (borderStyle == REPORTAGE) {
        frameGenerator = new ReportageFrameGenerator(this);
    }
    frameGenerator->setBorderSize(ui->frameSize->value());

    return frameGenerator->generateFrame(image);
}

void MainWindow::on_actionGenera_Cornici_triggered()
{
    if(container == NULL) {
        QMessageBox::warning(this, "Attenzione!", "Nessuna cartella selezionata. Impossibile generare le cornici!");
        return;
    }

    // crop
    container->mkdir("Export");

    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(filesList.count());
    int count = 0;
    foreach (QFileInfo file, filesList) {
        ui->statusBar->showMessage("Generazione cornice per \"" + file.fileName() + "\"");
        QImage image(file.absoluteFilePath());
        QPixmap out = generateFrame(image);
        //QString("export_%1").arg(count++, 3, 10, QChar('0'))
        out.save(container->absolutePath() + "/Export/" + file.baseName().replace(" ","_" ).toLower().simplified() + ".jpg");
        ui->progressBar->setValue(ui->progressBar->value()+1);
        qApp->processEvents(QEventLoop::AllEvents, 1000);
    }
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);

    ui->statusBar->showMessage("Generazione completata");
}

void MainWindow::refreshPreview(const QModelIndex &index)
{
    if(container == NULL) {
        QMessageBox::warning(this, "Attenzione!", "Nessuna cartella selezionata. Impossibile generare le cornici!");
        return;
    }

    QImage image(container->absolutePath() + "/" + index.data().toString());
    QPixmap out = generateFrame(image);
    bool isLandscape = (out.width() > out.height());
    if(isLandscape) {
        ui->lblPreview->setPixmap(out.scaledToWidth(ui->lblPreview->width(), Qt::SmoothTransformation));
    } else {
        ui->lblPreview->setPixmap(out.scaledToHeight(ui->lblPreview->height(), Qt::SmoothTransformation));
    }
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    refreshPreview(index);
}

void MainWindow::on_listView_pressed(const QModelIndex &index)
{
    refreshPreview(index);
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{
    refreshPreview(index);
}

void MainWindow::on_frameSize_valueChanged(int value)
{
    refreshPreview(ui->listView->currentIndex());
}

void MainWindow::on_radioButton_clicked()
{
    borderStyle = WEDDING;
    refreshPreview(ui->listView->currentIndex());
}

void MainWindow::on_radioButton_2_clicked()
{
    borderStyle = REPORTAGE;
    refreshPreview(ui->listView->currentIndex());
}
