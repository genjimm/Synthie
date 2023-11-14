#pragma once
#include "Effect.h"
class CChorusEffect :
    public CEffect
{
public:
    CChorusEffect(void);
    virtual ~CChorusEffect(void);

    //! Cause one sample to be generated
    virtual void Process(double* frameIn, double* frameOut);

    virtual void SetNote(CNote* note);

private:
    double m_delay;
    double m_freq;
    double m_depth;
};

