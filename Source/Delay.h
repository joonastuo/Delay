/*
  ==============================================================================

    Delay.h
    Created: 14 Mar 2019 7:31:38am
    Author:  Joonas

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CircularBuffer.h"
#include <vector>

class DelayEffect
{
public:
	DelayEffect(AudioProcessorValueTreeState& state);
	~DelayEffect();
	void prepare(dsp::ProcessSpec spec);
	void reset();
	void process(dsp::ProcessContextReplacing<float> context);
private:
	AudioProcessorValueTreeState& mState;

	std::vector<std::unique_ptr<circular_buffer<float>>> mDelayBuffer;
	double mSampleRate = 44100.f;
	int mSamplesPerBlock = 512;

};