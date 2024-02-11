#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <filedraggerwidget.h>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_play_button_clicked();

    void on_stop_button_clicked();

    void on_song_slider_valueChanged(int value);

    void changeSongName();

    void on_actionOpen_File_triggered();

private:
    Ui::MainWindow *ui;
    FileDraggerWidget* m_FileWidget;
    QAudioOutput* m_AudioOutput;
};
#endif // MAINWINDOW_H
