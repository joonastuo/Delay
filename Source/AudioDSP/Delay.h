/*
  ==============================================================================

    Delay.h
    Created: 14 Mar 2019 7:31:38am
    Author:  Joonas

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Helper/Identifiers.h"
#include "LFO.h"
#include "DelayLine.h"


class DelayEffect
{
public:
	DelayEffect(AudioProcessorValueTreeState& state);
	~DelayEffect();
	void prepare(dsp::ProcessSpec spec);
	void process(AudioBuffer<float>& buffer);
private:
	void update();
	float getFeedback();
	float getWetness();
	float getTime();
	// Methods
	float linearInterp(const float& y0, const float& yp1, const float& frac);

	// Variables
	AudioProcessorValueTreeState& mState;
	// Delay lines for right and left channel (stereo)
	std::array<DelayLine	<float>, 2> mDelayLines;
	std::array<SmoothedValue<float>, 2> mSmoothG;
	std::array<SmoothedValue<float>, 2> mSmoothW;
	std::array<SmoothedValue<float>, 2> mSmoothFB;

	float mLastTime = 0.f;
	double mSampleRate = 44100.f;
	int mSamplesPerBlock = 512;
	int mDelayBufferLen = 0;
	int mNumChannels = 2;
};
