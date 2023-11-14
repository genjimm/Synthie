#include "pch.h"
#include "CChorusEffect.h"

CChorusEffect::CChorusEffect(void)
{
}

CChorusEffect::~CChorusEffect(void)
{
}

void CChorusEffect::Process(double* frameIn, double* frameOut)
{
	//Add the input frame to the input delay circular queue
	m_wrloc = (m_wrloc + 1) % QUEUESIZE;
	m_inQueueL[m_wrloc] = frameIn[0];
	m_inQueueR[m_wrloc] = frameIn[0];

	//Compute the transfer equation result
	// double delay = m_depth + m_delay/2 + m_delay/2 * sin(2 * PI * m_freq * m_time);
	double delay = m_delay/2 + m_delay/2 * sin(2 * PI * m_freq * m_time);
	int delaylength = int(delay * GetSampleRate() + 0.5);
	while (delaylength > QUEUESIZE) {
		delaylength -= QUEUESIZE;
	}
	int rdloc = (m_wrloc + QUEUESIZE - delaylength) % QUEUESIZE;

	// double virbo = 1 + m_depth*sin(2 * PI * m_freq * m_time);
	double virbo = 1.0 - m_depth;
	frameOut[0] = frameIn[0] / 2 + virbo * m_inQueueL[rdloc] / 2;
	frameOut[1] = frameIn[1] / 2 + virbo * m_inQueueR[rdloc] / 2;


	frameOut[0] = frameIn[0] * (1 - m_send) + frameOut[0] * m_send;
	frameOut[1] = frameIn[1] * (1 - m_send) + frameOut[1] * m_send;

	//Add the result frame to the output delay circular queue
	m_outQueueL[m_wrloc] = frameOut[0];
	m_outQueueR[m_wrloc] = frameOut[1];

	m_time += GetSamplePeriod();
}

void CChorusEffect::SetNote(CNote* note)
{
	// Get a list of all attribute nodes and the
// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "delay")
		{
			value.ChangeType(VT_R8);
			m_delay = value.dblVal;
		}
		if (name == "send")
		{
			value.ChangeType(VT_R8);
			m_send = value.dblVal;
		}
		if (name == "freq")
		{
			value.ChangeType(VT_R8);
			m_freq = value.dblVal;
		}
		if (name == "depth")
		{
			value.ChangeType(VT_R8);
			m_depth = value.dblVal;
		}

	}
}
