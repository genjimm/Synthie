#include "pch.h"
#include "Effect.h"

using namespace std;



CEffect::CEffect(void)
{
	m_inQueueL.resize(QUEUESIZE);
	m_inQueueR.resize(QUEUESIZE);
	m_outQueueL.resize(QUEUESIZE);
	m_outQueueR.resize(QUEUESIZE);
}

CEffect::~CEffect(void)
{
}
