#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>
#include <QFileInfo>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAcceptDrops(true);
    ui->setupUi(this);

    m_FileWidget = this->findChild<FileDraggerWidget*>("centralwidget");
    connect(m_FileWidget, &FileDraggerWidget::changingSong, this, &MainWindow::changeSongName);
    ui->play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->stop_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));

    m_AudioOutput = new QAudioOutput();
    m_AudioOutput->setVolume(0.2);
}

MainWindow::~MainWindow()
{
    delete m_AudioOutput;
    delete ui;
}

void MainWindow::changeSongName()
{
    qDebug() << "Changing Song";
    QFileInfo songFile(m_FileWidget->getCurrentSongFilePath());
    ui->var_name->setText(songFile.fileName());
}


void MainWindow::on_play_button_clicked()
{
    if(m_FileWidget->getPlayer()->hasAudio())
    {
        m_FileWidget->getPlayer()->play();
        qDebug() << "Play" << m_FileWidget->getPlayer()->errorString();
    }
}


void MainWindow::on_stop_button_clicked()
{
    m_FileWidget->getPlayer()->pause();
}


void MainWindow::on_song_slider_valueChanged(int value)
{
    qDebug() << "Current Volume:" << value;
    float normalized = value / 100;
    m_AudioOutput->setVolume(normalized);
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Audio File"), "",tr("MP3 Files (*.MP3)"));
    m_FileWidget->setCurrentSong(fileName);
}

