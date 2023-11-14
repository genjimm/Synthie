#include "pch.h"
#include "CompressionEffect.h"

void CCompressionEffect::Process(double* frameIn, double* frameOut)
{

}

void CCompressionEffect::SetNote(CNote* note)
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

		if (name == "threshold")
		{
			value.ChangeType(VT_R8);
			m_threshold = value.dblVal;
		}
		if (name == "send")
		{
			value.ChangeType(VT_R8);
			m_send = value.dblVal;
		}
		if (name == "ratio")
		{
			value.ChangeType(VT_R8);
			m_ratio = value.dblVal;
		}
	}
}
