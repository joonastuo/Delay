/*
  ==============================================================================

    Delay.h
    Created: 14 Mar 2019 7:31:38am
    Author:  Joonas

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DelayEffect
{
public:
	DelayEffect(AudioProcessorValueTreeState& state);
	~DelayEffect();
	void prepare(dsp::ProcessSpec spec);
	void reset();
	void process(AudioBuffer<float>& buffer);
private:
	// Methods
	void fillDelayBuffer(const float* input, const int channel, float startGain, float endGain);


	// Variables
	AudioProcessorValueTreeState& mState;

	AudioBuffer<float> mDelayBuffer;
	int mWritePos = 0;
	float mLastInputGain = 0.f;
	double mSampleRate = 44100.f;
	int mSamplesPerBlock = 512;
	int mDelayBufferLen = 0;
	int mNumChannels = 2;

};