#pragma once
#include "Instrument.h"
#include "PianoNode.h"

class CPianoInstrument :
    public CInstrument
{
public:
    CPianoInstrument(void);
    ~CPianoInstrument(void);

    virtual void Start();
    virtual bool Generate();

    void SetNote(CNote* note);

    void SetDuration(double d) { m_duration = d; m_pianoNode.SetDuration(d); }

    void SetNotes(std::vector<std::wstring> notes) { m_pianoNode.SetNotes(notes); }

    void SetSpeed(double speed) { m_pianoNode.SetAmplitude(speed); }

private:
    double m_duration;
    double m_time;
    // If speed > 2.0, play loud
    double m_pressSpeed = 1.0;
    CPianoNode m_pianoNode;
};

