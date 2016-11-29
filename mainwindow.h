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

    typedef enum BorderStyle {
        WEDDING = 0,
        REPORTAGE
    } BorderStyle;

    void refreshPreview(const QModelIndex &index);
    QPixmap generateFrame(QImage image);
private slots:
    void on_actionApri_triggered();
    void on_actionGenera_Cornici_triggered();

    void on_listView_clicked(const QModelIndex &index);

    void on_listView_pressed(const QModelIndex &index);

    void on_listView_activated(const QModelIndex &index);

    void on_frameSize_valueChanged(int value);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QFileInfoList filesList;
    QDir* container;
    QFileSystemModel *model;
    BorderStyle borderStyle;
};

#endif // MAINWINDOW_H
