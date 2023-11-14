#include "pch.h"
#include "PianoNode.h"

using namespace std;
CPianoNode::CPianoNode(void)
{
	m_amp = 1.0;
}

CPianoNode::~CPianoNode(void)
{
}

void CPianoNode::Start()
{
	m_time = 0;
	m_attack = 0.1;
	m_release = 0.5;
}

bool CPianoNode::Generate()
{
	bool flag = false;
	m_frame[0] = 0;
	m_frame[1] = 0;
	/*
	* Polyphony
	* Pedel noisy
	*/
	for (auto it = m_waves.begin(); it != m_waves.end(); ++it) {
		short frame[2] = { 0, 0 };
		flag |= (*it)->ReadFrame(frame);
		//double amp = m_amp;
		m_frame[0] += double(frame[0]);
		m_frame[1] += double(frame[1]);
	}
	m_frame[0] *= m_amp / 16384.0;
	m_frame[0] /= m_waves.size();
	m_frame[1] = m_frame[0];
	/// Is pedel pressed
	if (!m_pedal) {
		double releaseTime = (m_duration / (m_bpm / 60.0));
		// Envelops
		double ramp = 1.0;
		if (m_time > releaseTime) {
			ramp = 1.0 - (m_time - releaseTime) / m_release;
		}
		if (ramp < 0) {
			flag = false;
			m_frame[0] = m_frame[1] = 0;
		}
		else {
			m_frame[0] *= ramp;
			m_frame[1] *= ramp;
		}
	}
	m_time += GetSamplePeriod();
	return flag;
}

void CPianoNode::SetNotes(std::vector<std::wstring> notes)
{
	for (auto note : notes) {
		wstring filename;
		wstring filePath = L"pianoSample/";
		shared_ptr<CDirSoundSource> wave = make_shared<CDirSoundSource>();
		if (note == L"pedald") {
			m_pedal = true;
			filename = L"piano/" + note + L".wav";
		}
		else if (note == L"pedalu") {
			m_pedal = false;
			filename = L"piano/" + note + L".wav";
		}
		else {
			// Dynamics (advanced)
			if (m_amp > 2.0) {
				filename = L"piano/" + note + L"l.wav";
				m_amp -= 1.0;
			}
			else {
				filename = L"piano/" + note + L"s.wav";
			}
		}
		wave->Open(filename.c_str());
		m_waves.push_back(wave);
	}
}
