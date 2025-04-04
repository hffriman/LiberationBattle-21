#ifndef SOUNDEFFECTPLAYER_H
#define SOUNDEFFECTPLAYER_H
#include <QString>
#include <QMediaPlayer>
#include <QAudioOutput>

class SoundEffectPlayer
{
public:
    SoundEffectPlayer();
    QString soundEffects[12] = { "ButtonSound.wav", "ButtonSoundCancel.wav", "WritingSound.wav", "SwordPrepare.wav", "SwordSlash.wav", "GunPrepare.wav", "GunShot.wav", "BottlePrepare.wav", "DrinkSound.wav", "PrepareWeaponRepair.wav", "RepairWeapons.wav", "DestructionRay.wav"};
    QMediaPlayer* soundPlayer;
    QAudioOutput* soundOutput;

    void PlaySound(int soundIndex);
};

#endif // SOUNDEFFECTPLAYER_H
