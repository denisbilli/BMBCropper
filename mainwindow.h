#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileInfoList>
#include <QFileSystemModel>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QRect crop(QImage p);
    QRect crop1(QImage p);
    QRect getBoundsWithoutColor(QImage p, const QColor &exclusionColor = Qt::white, const int tolerance=30);
    QPixmap generateFrame(QImage image);

    void refreshPreview(const QModelIndex &index);
private slots:
    void on_actionApri_triggered();
    void on_actionGenera_Cornici_triggered();

    void on_listView_clicked(const QModelIndex &index);

    void on_listView_pressed(const QModelIndex &index);

    void on_listView_activated(const QModelIndex &index);

    void on_frameSize_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QFileInfoList filesList;
    QDir* container;
    QFileSystemModel *model;
};

#endif // MAINWINDOW_H
