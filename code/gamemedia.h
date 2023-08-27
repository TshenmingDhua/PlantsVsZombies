#ifndef GAMEMEDIA_H
#define GAMEMEDIA_H

#include <QObject>
#include <QtMultimedia/QtMultimedia>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QTimer>

class gameMedia : public QObject
{
    Q_OBJECT
public:
    gameMedia(QString address,QObject * parent = nullptr,bool dontPlay = false);
    //播放音频
    void playMedia();
    //结束音频
    void stopMedia(bool isSlow);
    //设置循环播放
    void setForeverPlay(QString address);

    //取消循环
    void stopForeverPlay();
    //设置慢速播放
    void setSlow();

private:
    QMediaPlayer * media;
    QTimer * foreverTimer;

signals:

};

#endif // GAMEMEDIA_H
