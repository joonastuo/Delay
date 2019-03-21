/*
  ==============================================================================

    Delay.h
    Created: 14 Mar 2019 7:31:38am
    Author:  Joonas

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Identifiers.h"

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
	void fillDelayBuffer(AudioBuffer<float>& buffer, const int& channel);
	void copyFromDelayBuffer(AudioBuffer<float>& buffer, const int& channel, const int& readPos, const float& readFrac);
	void feedbackDelayBuffer(AudioBuffer<float>& buffer, const int& channel, const float& startGain, const float& endGain);

	// Variables
	AudioProcessorValueTreeState& mState;

	AudioBuffer<float> mDelayBuffer;
	AudioBuffer<float> mDryBuffer;
	// Write position of delay buffer
	int mWriteIndex = 0;
	float mLastG = 0.f;
	float mLastW = 0.f;
	float mLastFB = 0.f;
	double mSampleRate = 44100.f;
	int mSamplesPerBlock = 512;
	int mDelayBufferLen = 0;
	int mNumChannels = 2;
};