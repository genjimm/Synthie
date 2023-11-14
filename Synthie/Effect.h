#pragma once
#include <vector>
#include "Note.h"

const int QUEUESIZE = 20000;

class CEffect
{
public:
    CEffect(void);
    virtual ~CEffect(void);

    //! Cause one sample to be generated
    virtual void Process(double* frameIn, double* frameOut) = 0;

    virtual void SetNote(CNote* note) = 0;

    //! Start the node generation
    virtual void Start() {
        m_wrloc = 0;
        m_rdloc = 0;
        m_time = 0;
    }

    //! Get the sample rate in samples per second
    double GetSampleRate() { return m_sampleRate; }
    //! Get the sample period in seconds
    double GetSamplePeriod() { return m_samplePeriod; }

    //! Set the sample rate
    void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1 / s; }

protected:
    std::vector<double> m_inQueueL;
    std::vector<double> m_inQueueR;

    std::vector<double> m_outQueueL;
    std::vector<double> m_outQueueR;

    int m_wrloc;
    int m_rdloc;

    double m_send;

    double m_time;

    double m_sampleRate;
    double m_samplePeriod;
};

