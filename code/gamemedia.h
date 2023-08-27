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
    //������Ƶ
    void playMedia();
    //������Ƶ
    void stopMedia(bool isSlow);
    //����ѭ������
    void setForeverPlay(QString address);

    //ȡ��ѭ��
    void stopForeverPlay();
    //�������ٲ���
    void setSlow();

private:
    QMediaPlayer * media;
    QTimer * foreverTimer;

signals:

};

#endif // GAMEMEDIA_H
