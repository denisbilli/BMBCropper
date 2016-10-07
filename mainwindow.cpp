#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QFileSystemModel>

#define SMALL 10
#define isSimilar(A, B) ( ((A-B) < SMALL) && ((A-B) > - SMALL) )
#define isSimilarRgb(A, B) (isSimilar(qRed(A),qRed(B)) && isSimilar(qGreen(A),qGreen(B)) && isSimilar(qBlue(A),qBlue(B)))

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    container = NULL;
    model = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

QRect MainWindow::crop(QImage p) {
    int l = p.width(), r = 0, t = p.height(), b = 0;
    for (int y = 0; y < p.height(); ++y) {
        QRgb *row = (QRgb*)p.scanLine(y);
        bool rowFilled = false;
        for (int x = 0; x < p.width(); ++x) {
            if(isSimilarRgb(row[x], 255)) {
                //if (qRed(row[x]) == 255 && qGreen(row[x]) == 255 && qBlue(row[x]) == 255) {
                rowFilled = true;
                r = std::max(r, x);
                if (l > x) {
                    l = x;
                    x = r; // shortcut to only search for new right bound from here
                }
            }
        }
        if (rowFilled) {
            t = std::min(t, y);
            b = y;
        }
        qDebug() << l << r << t << b;
    }
    return QRect(l, t, l+r, t+b);
}

QRect MainWindow::getBoundsWithoutColor(QImage p, const QColor &exclusionColor, const int tolerance)
{
    QRect rect;

    int maxX = 0; int minX = p.width();
    int maxY = 0; int minY = p.height();

    for(int y=0; y < p.height(); y++) {
        QRgb *row = (QRgb*)p.scanLine(y);
        for(int x=0; x < p.width(); x++) {
            int diff = abs(exclusionColor.red()-qRed(row[x])) +
                    abs(exclusionColor.green()-qGreen(row[x])) +
                    abs(exclusionColor.blue()-qBlue(row[x]));
            //QColor pixelColor = QColor::fromRgb(qRed(row[x]),qGreen(row[x]),qBlue(row[x]));
            if(diff > tolerance) {
                //                if (pixelColor != exclusionColor) {
                if(x < minX) minX = x;
                if(x > maxX) maxX = x;
                if(y < minY) minY = y;
                if(y > maxY) maxY = y;

                //                qDebug() << QString("%1,%2,%3 == %4,%5,%6? %7")
                //                            .arg(qRed(row[x]))
                //                            .arg(qGreen(row[x]))
                //                            .arg(qBlue(row[x]))
                //                            .arg(exclusionColor.red())
                //                            .arg(exclusionColor.green())
                //                            .arg(exclusionColor.blue())
                //                            .arg(diff);
            }
        }

        if (minX > maxX || minY > maxY) {
            // The whole picture is white. How you wanna handle this case is up to you.
        } else {
            rect.setCoords(minX, minY, maxX, maxY);
        }
    }

    return rect;
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
    int fixedBorders = ui->frameSize->value();
    int logoSize = 165;
    int maxEdgeLength = 1950;

    // Cerco e rimuovo i bordi bianchi dell'immagine e la scalo a 1950
    QRect whiteBox = getBoundsWithoutColor(image);
    QImage firstPass = image.copy(whiteBox);
    if(firstPass.width() > firstPass.height()) {
        // sono in formato landscape
        firstPass = firstPass.scaledToWidth(maxEdgeLength);
    } else {
        firstPass = firstPass.scaledToHeight(maxEdgeLength);
    }

    QRect outRect = QRect(0, 0, firstPass.width() + fixedBorders*2, firstPass.height() + fixedBorders+logoSize);
    QPixmap out = QPixmap(outRect.size());
    QPainter painter(&out);
    painter.fillRect(outRect, Qt::white);
    painter.drawImage(fixedBorders, fixedBorders, firstPass);
    QImage logo(":/bmb-logo");
    painter.drawImage((out.width()-logo.width())/2, out.height()-(logoSize+logo.height())/2, logo);
    painter.end();

    return out;
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
    QImage image(container->absolutePath() + "/" + index.data().toString());
    QPixmap out = generateFrame(image);
    ui->lblPreview->setPixmap(out.scaledToWidth(400));
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
