#ifndef QT_MUSIQUE_H
#define QT_MUSIQUE_H

#include <QAudioFormat>
#include <QAudioSink>
#include <QFile>
#include <QDebug>

class Musique : public QAudioSink{
    Q_OBJECT
private:
    QAudioSink* audio;
    QFile* effectFile;
    QAudioFormat format;
    bool isPause = false;
    float volume = 50;

public:
    Musique(QObject* parent = nullptr);
    virtual ~Musique(){
        delete audio;
        delete effectFile;
    };
    float getVolume(){return volume;};

public slots:
    void replayMusic();
    void pauseMusic();
    void restartMusic();
    void setVolumeMusic(float volume);
};


#endif //QT_MUSIQUE_H
