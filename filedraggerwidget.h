#ifndef FILEDRAGGERWIDGET_H
#define FILEDRAGGERWIDGET_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMediaPlayer>

class FileDraggerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileDraggerWidget(QWidget *parent = nullptr);

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* e) override;

    QMediaPlayer* getPlayer() {return m_Player;}
    QString getCurrentSongFilePath() {return currentSong;}

    bool setCurrentSong(QString path);

protected:

signals:
    void changingSong();

private:
    QMediaPlayer* m_Player = nullptr;
    QString currentSong;
};

#endif // FILEDRAGGERWIDGET_H
