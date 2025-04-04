#include "soundeffectplayer.h"

/* SoundEffectPlayer:
 * - Used to play a sound effect when necessary
 * - Note: the soundEffects array's content is declared completely
 *   in the header file for the sake of convenience
*/
SoundEffectPlayer::SoundEffectPlayer()
{
    soundPlayer = new QMediaPlayer();
    soundOutput = new QAudioOutput();
}

void SoundEffectPlayer::PlaySound(int i)
{
    QString* urlText = new QString("qrc:/SoundEffects/" + soundEffects[i]);
    soundPlayer->setAudioOutput(soundOutput);
    soundPlayer->setSource(QUrl(*urlText));
    soundOutput->setVolume(10);
    soundPlayer->play();

}
