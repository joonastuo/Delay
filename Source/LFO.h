/*
  ==============================================================================

    LFO.h
    Created: 21 Mar 2019 12:02:50pm
    Author:  Joonas

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class LFO
{
public:
    LFO();
    ~LFO();
	void prepare(dsp::ProcessSpec spec);
	float getValue();
	void setFreq(const float& freq);
	void setUnipolar(const bool& isUnipolar);
	void setWaveform(const int& waveform);
	void advanceSamples(const int& numSamples);
	void advanceBlock();
	float linearInterp(const float& y0, const float& yp1, const float& frac);

	enum Waveforms
	{
		sine,
		rectSine,
		saw,
		tri, 
		square
	};

private:
	float mReadIndex = 0.f;
	int mWaveform = 0;
	float mInc = 0.f;
	bool mUnipolar = true;

	float mSampleRate = 44100.f;
	float mSamplesPerBlock = 512.f;

	// Wavetables
	float mSinArray[1024] = { 0.f };
	float mRectSinArray[1024] = { 0.f };
	float mSawtoothArray[1024] = { 0.f };
	float mTriangleArray[1024] = { 0.f };
	float mSquareArray[1024] = { 0.f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO)
};
