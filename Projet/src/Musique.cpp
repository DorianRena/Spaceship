#include "Musique.h"

Musique::Musique(QObject *parent) {
    this->setParent(parent);
    format.setSampleRate(44000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);
    audio = new QAudioSink(format, this);
    effectFile = new QFile(this);
    effectFile->setFileName(":Projet/other/music_spaceship_compressée.wav");
    effectFile->open(QIODevice::ReadOnly);
    audio->start(effectFile);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(replayMusic()));
}
void Musique::replayMusic() {
    if (audio->state() == QAudio::IdleState && !isPause) {
        effectFile->seek(0);
        audio->start(effectFile);
        audio->setVolume(volume / 100.0f);
    }
}

void Musique::pauseMusic(){
    isPause = true;
    audio->suspend();
}
void Musique::restartMusic(){
    audio->resume();
    isPause = false;
}
void Musique::setVolumeMusic(float volume){
    this->volume = volume;
    audio->setVolume(volume/100);
}