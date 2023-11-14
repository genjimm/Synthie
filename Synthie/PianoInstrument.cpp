#include "pch.h"
#include "PianoInstrument.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;
std::vector<std::wstring> splitString(const std::wstring& input, wchar_t delimiter) {
    std::vector<std::wstring> result;
    std::wstringstream ss(input);
    std::wstring token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

CPianoInstrument::CPianoInstrument(void)
{
    m_duration = 0.1; 
}

CPianoInstrument::~CPianoInstrument(void)
{
}

void CPianoInstrument::Start()
{
    m_pianoNode.SetSampleRate(GetSampleRate());
    m_pianoNode.SetBpm(m_bpm);
    m_pianoNode.Start();
    m_time = 0;
}

bool CPianoInstrument::Generate()
{
    bool flag = m_pianoNode.Generate();
    m_frame[0] = m_pianoNode.Frame(0);
    m_frame[1] = m_pianoNode.Frame(1);
    // Update time
    m_time += GetSamplePeriod();
    // We return true until the time reaches the duration.
    return (m_time < m_duration) && flag;
}

void CPianoInstrument::SetNote(CNote* note)
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

        // Get the value of the attribute.  A CComVariant is a variable
        // that can have any type. It loads the attribute value as a
        // string (UNICODE), but we can then change it to an integer 
        // (VT_I4) or double (VT_R8) using the ChangeType function 
        // and then read its integer or double value from a member variable.
        CComVariant value;
        attrib->get_nodeValue(&value);

        if (name == "duration")
        {
            value.ChangeType(VT_R8);
            SetDuration(value.dblVal);
        }
        else if (name == "speed") {
            // Dynamics amplitude with press speed
            value.ChangeType(VT_R8);
            SetSpeed(value.dblVal);
        }
        else if (name == "notes")
        {
            // Set note
            wstring notesStr = value.bstrVal;
            vector<wstring> notes = splitString(notesStr, ' ');
            SetNotes(notes);
        }
    }
}

