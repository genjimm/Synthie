# Synthie
1.  score files are in Synthie/scores/

2.  piano music and effects are in Synthie/music/

3.  Format of score

<?xml version="1.0" encoding="utf-8"?>
<score bpm="60" beatspermeasure="4">
	<instrument instrument="PianoInstrument">
		<note measure="1"   beat="1" 	   duration="2"   speed="1.0"    notes="C3 G3 C4 E5"/>	
    <note measure="5"   beat="1" 	   duration="1"   speed="2.0"    notes="C3 E5 pedald"/>
		<note measure="5"   beat="1.5"     duration="1"   speed="2.1"    notes="G3"/>
		<note measure="5"   beat="2"       duration="1"   speed="2.2"    notes="C4"/>
		<note measure="5"   beat="2.5"     duration="1"   speed="2.3"    notes="E5"/>	
	<instrument instrument="FlangingEffect">									   
		<note measure="3"   beat="1"   send="1.0"	delay="0.02"   freq="0.02"/>			     
	</instrument>
</score>


4.  Synthesizer: Piano
                  Polyphony
                  Envelopes
                  Pedal Simulation
                  Dynamics (basic)
5.  Effect: Flanging 
            Chorus
            Reverb


==Piano synthesizer====
                Two classes, CPianoInstrument and CPianoNode, were used to deploy and complete the following functions:
Polyphony
                Read the following XML node in the SetNote function of CPianoInstrument
                <note measure="1" beat="1" duration="2" speed="1.0" notes="C3 G3 C4 E5"/>
                Notes are multiple notes, and the corresponding piano keys are sampled and stored as vectors in CPianoNode through note reading. Multiple notes are mixed in the function Generate() of CPianoNode to achieve Polyphony.
Envelopes
                And implement Envelopes through ramp in the function Generate() of CPianoNode.
Pedal Simulation
                Store the press and release of pedal as syllables in an XML file, as shown in the following example:
                <note measure="5" beat="1" duration="1" speed="2.0" notes="C3 E5 pedal"/>
                <note measure="5" beat="4.5" duration="1" speed="2.1" notes="B3 pedal"/>
                When CPianoInstrument reads a pedald syllable, it allows subsequent notes to continue throughout the entire duration until the pedalu syllable is read
Dynamics (basic)
                The speed in XML node can achieve dynamic effects, and the m in CPianoNode can be set based on the speed value in XML The value of m_amp and multiply the output frame by m_ amp
Pedal Noise
                When a pedal syllable is read, play the corresponding sampling
Dynamics (advanced)
                The sampling for each piano key is divided into two types: soft and loud. When the speed is greater than 2.0, play the sampling for loud, otherwise play the sampling for soft.
		
=====Effects====
Flanging
                Implemented through class CFlanging, the third measure of generating audio shows the effect.
Chorus
                Implemented through class CChorus, the second measure of generating audio shows the effect.
Reverb
                Implemented through class CReverb, the fourth measure of generating audio shows the effect.

Component passes audio
                Pass audio to effects in the Generate function of class CSynthesizer.
Controllable effects send
                Lines 251-383 of Synthesizer. cpp allows audio to be distributed to different effects. The proportion of wet and dry signals is controlled by the "send" attribute in the XML file, and the value of send represents the proportion of wet signals





Fangjun Huang
