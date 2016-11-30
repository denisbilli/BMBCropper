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
    frameGenerator = NULL;
    firstStart = true;

    borderStyle = WEDDING;
    ui->radioButton->setChecked(true);

    timer = new QTimer(this);
    timer->setInterval(300);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), SLOT(slot_onTimer()));

    on_radioButton_clicked();
    firstStart = false;
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

void MainWindow::refreshOptionsFrame(FrameGenerator* frameGenerator)
{
    QWidgetList list = ui->groupBox_2->findChildren<QWidget*>();
    foreach (QWidget * w, list) w->deleteLater();

    for (int i = 0; i < ui->groupBox_2->layout()->count(); ++i) {
        QLayoutItem *layoutItem = ui->groupBox_2->layout()->itemAt(i);
        if (layoutItem->spacerItem()) {
            ui->groupBox_2->layout()->removeItem(layoutItem);
            // You could also use: layout->takeAt(i);
            delete layoutItem;
            --i;
        }
    }

    foreach (QString optionName, frameGenerator->options().keys()) {
        FrameOption* option = frameGenerator->options().value(optionName).value<FrameOption*>();

        QWidget* container = new QWidget(ui->groupBox_2);
        QHBoxLayout* layout = new QHBoxLayout(container);

        QLabel* label = new QLabel(container);
        label->setText(QString("<b>%1</b>").arg(option->name()));

        layout->addWidget(label);
        if(option->widget() != NULL) {
            option->widget()->setParent(container);
            layout->addWidget(option->widget());
        }

        ui->groupBox_2->layout()->addWidget(container);
    }

    QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->groupBox_2->layout()->addItem(spacer);
}

QPixmap MainWindow::generateFrame(QImage image) {
    qDebug() << "MainWindow::generateFrame";
    if(frameGenerator == NULL) {
        return QPixmap();
    }
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
    foreach (QFileInfo file, filesList) {
        ui->statusBar->showMessage("Generazione cornice per \"" + file.fileName() + "\"");
        QImage image(file.absoluteFilePath());
        qDebug() << "genera";
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

void MainWindow::refreshPreview(const QModelIndex &index, bool fullRes)
{
    if(container == NULL) {
        QMessageBox::warning(this, "Attenzione!", "Nessuna cartella selezionata. Impossibile generare le cornici!");
        return;
    }

    QImage image(container->absolutePath() + "/" + index.data().toString());
    bool isLandscape = (image.width() > image.height());

    if(isLandscape) {
        qDebug() << "landscape";
        QPixmap out = generateFrame(fullRes ? image : image.scaledToWidth(ui->lblPreview->width(), Qt::FastTransformation));
        ui->lblPreview->setPixmap(out.scaledToWidth(ui->lblPreview->width(), fullRes ? Qt::SmoothTransformation : Qt::FastTransformation));
    } else {
        qDebug() << "portrait";
        QPixmap out = generateFrame(fullRes ? image : image.scaledToHeight(ui->lblPreview->height(), Qt::FastTransformation));
        ui->lblPreview->setPixmap(out.scaledToHeight(ui->lblPreview->height(), fullRes ? Qt::SmoothTransformation : Qt::FastTransformation));
    }
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    if(timer->isActive()) {
        return;
    }
    qDebug() << "MainWindow::on_listView_clicked";
    refreshPreview(index);
    timer->start();
}

void MainWindow::on_listView_pressed(const QModelIndex &index)
{
    if(timer->isActive()) {
        return;
    }
    qDebug() << "MainWindow::on_listView_pressed";
    refreshPreview(index);
    timer->start();
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{
    if(timer->isActive()) {
        return;
    }
    qDebug() << "MainWindow::on_listView_activated";
    refreshPreview(index);
    timer->start();
}

void MainWindow::on_radioButton_clicked()
{
    if(timer->isActive()) {
        return;
    }
    qDebug() << "MainWindow::on_radioButton_clicked";
    borderStyle = WEDDING;

    if(frameGenerator != NULL) {
        disconnect(frameGenerator, 0, 0, 0);
        frameGenerator->deleteLater();
    }

    frameGenerator = new WeddingFrameGenerator(this);
    connect(frameGenerator, SIGNAL(optionChanged(QString,QVariant)), SLOT(slot_onOptionChanged(QString,QVariant)));
    refreshOptionsFrame(frameGenerator);

    if(!firstStart) {
        refreshPreview(ui->listView->currentIndex());
        timer->start();
    }
}

void MainWindow::on_radioButton_2_clicked()
{
    if(timer->isActive()) {
        return;
    }
    qDebug() << "MainWindow::on_radioButton_2_clicked";
    borderStyle = REPORTAGE;

    if(frameGenerator != NULL) {
        disconnect(frameGenerator, 0, 0, 0);
        frameGenerator->deleteLater();
    }

    frameGenerator = new ReportageFrameGenerator(this);
    connect(frameGenerator, SIGNAL(optionChanged(QString,QVariant)), SLOT(slot_onOptionChanged(QString,QVariant)));
    refreshOptionsFrame(frameGenerator);

    refreshPreview(ui->listView->currentIndex());
    timer->start();
}

void MainWindow::slot_onTimer()
{
    qDebug() << "MainWindow::slot_onTimer";
    refreshPreview(ui->listView->currentIndex(), true);
}

void MainWindow::slot_onOptionChanged(QString optionName, QVariant optionValue)
{
    qDebug() << "MainWindow::slot_onOptionChanged" << optionName << optionValue;
    refreshPreview(ui->listView->currentIndex());
    timer->start();
}

