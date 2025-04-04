#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <QString>
#include <QMediaPlayer>
#include <QAudioOutput>

class MusicPlayer
{
public:
    MusicPlayer();
    QString musicTracks[5] = {"lb21-intro.wav", "lb21-over21.wav", "lb21-perfectscore.wav", "lb21-gameover.wav", "lb21-congratulations.wav"};
    QMediaPlayer* musicTrackPlayer;
    QAudioOutput* musicOutput;

    void PlayMusic(int musicIndex);
};

#endif // MUSICPLAYER_H
