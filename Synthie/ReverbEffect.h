#pragma once
#include "Effect.h"
class CReverbEffect :
    public CEffect
{
public:
    CReverbEffect(void);
    virtual ~CReverbEffect(void);

    //! Cause one sample to be generated
    virtual void Process(double* frameIn, double* frameOut);

    virtual void SetNote(CNote* note);

private:
    double m_delay;
    double m_g;
};

