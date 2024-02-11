#include "filedraggerwidget.h"
#include <QDebug>

FileDraggerWidget::FileDraggerWidget(QWidget *parent)
    : QWidget{parent}
{
    setAcceptDrops(true);
    m_Player = new QMediaPlayer();

    connect(m_Player, &QMediaPlayer::errorOccurred, this, [](QMediaPlayer::Error error){
        qDebug() << "Error al reproducir el archivo:" << error;
    });

    connect(m_Player, &QMediaPlayer::mediaStatusChanged, this, [](QMediaPlayer::MediaStatus state){
        qDebug() << "Estado del reproductor cambiado a:" << state;
    });

    connect(m_Player, &QMediaPlayer::playbackStateChanged, this, [](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::PlayingState) {
            qDebug() << "El reproductor está reproduciendo." << state;
        }
    });
}

void FileDraggerWidget::dragEnterEvent(QDragEnterEvent *e)
{
    qDebug() << "File Drag";
    if(e->mimeData()->hasUrls())
    {
        qDebug() << "Has URL";
        e->acceptProposedAction();
    }
}

void FileDraggerWidget::dropEvent(QDropEvent *e)
{
    const QMimeData* mime = e->mimeData();

    if(mime->hasUrls())
    {
        QList<QUrl> urls = mime->urls();
        for(const QUrl& url : urls)
        {
            if(setCurrentSong(url.toLocalFile()))
                break;
        }
    }
}

bool FileDraggerWidget::setCurrentSong(QString path)
{
    if(path.endsWith(".mp3", Qt::CaseInsensitive))
    {
        currentSong = path;
        qDebug() << "Added song" << currentSong;
        m_Player->setSource(QUrl::fromLocalFile(currentSong));
        emit changingSong();
        return true;
    }
    return false;
}
