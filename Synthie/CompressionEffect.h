#pragma once
#include "Effect.h"
class CCompressionEffect :
    public CEffect
{
public:
    CCompressionEffect(void);
    virtual ~CCompressionEffect(void);

    //! Cause one sample to be generated
    virtual void Process(double* frameIn, double* frameOut);

    virtual void SetNote(CNote* note);

private:
    double m_threshold;
    double m_ratio;
};

