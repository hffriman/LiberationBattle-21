#include "soundeffectplayer.h"

/* SoundEffectPlayer:
 * - Used to play a sound effect when necessary
 * - Note: the soundEffects are defined in the header file
 *   (for the sake of convenience)
*/
SoundEffectPlayer::SoundEffectPlayer()
{
    soundPlayer = new QMediaPlayer();
    soundOutput = new QAudioOutput();
}

void SoundEffectPlayer::PlaySound(int soundIndex)
{
    QString* soundEffectUrl = new QString("qrc:/SoundEffects/" + soundEffects[soundIndex]);
    soundPlayer->setAudioOutput(soundOutput);
    soundPlayer->setSource(QUrl(*soundEffectUrl));
    soundOutput->setVolume(10);
    soundPlayer->play();

}
