#include "musicplayer.h"

/* MusicPlayer:
 * - Used to play music tracks when necessary
 * - Note: MusicTracks are defined in the header file
 *  (for the sake of convenience)
 */
MusicPlayer::MusicPlayer()
{
    musicTrackPlayer = new QMediaPlayer();
    musicOutput = new QAudioOutput();
}

void MusicPlayer::PlayMusic(int musicIndex)
{
    QString* musicTrackUrl = new QString("qrc:/Music/" + musicTracks[musicIndex]);
    musicTrackPlayer->setAudioOutput(musicOutput);
    musicTrackPlayer->setSource(*musicTrackUrl);
    musicOutput->setVolume(5);
    musicTrackPlayer->play();
}
