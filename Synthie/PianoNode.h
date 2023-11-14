#pragma once
#include "AudioNode.h"
#include <vector>
#include "audio/DirSoundSource.h"
#include "audio/WaveformBuffer.h"
#include <memory>

class CPianoNode :
    public CAudioNode
{
public:
    CPianoNode(void);
    virtual ~CPianoNode(void);

    //! Start audio generation
    virtual void Start();

    //! Generate one frame of audio
    virtual bool Generate();

    //! Set the sine wave amplitude
    void SetAmplitude(double a) { m_amp = a; }

    // Set notes
    void SetNotes(std::vector<std::wstring> notes);
    void SetDuration(double d) { m_duration = d; }
private:
    double m_amp;
    double m_attack;
    double m_release;
    double m_duration;
    CWaveformBuffer m_waveformBuffer;
    std::vector<std::shared_ptr<CDirSoundSource>> m_waves;
    bool m_pedal = false;

};

