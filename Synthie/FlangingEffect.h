#pragma once
#include "Effect.h"
class CFlangingEffect :
    public CEffect
{
public:
    CFlangingEffect(void);
    virtual ~CFlangingEffect(void);

    //! Cause one sample to be generated
    virtual void Process(double* frameIn, double* frameOut);

    virtual void SetNote(CNote* note);

private:
    double m_delay;
    double m_freq;
};

