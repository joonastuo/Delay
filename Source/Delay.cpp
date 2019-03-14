/*
  ==============================================================================

    Delay.cpp
    Created: 14 Mar 2019 7:31:38am
    Author:  Joonas

  ==============================================================================
*/

#include "Delay.h"

DelayEffect::DelayEffect(AudioProcessorValueTreeState& state)
	: mState(state)
{
	// Empty constructor
}

DelayEffect::~DelayEffect()
{
	// Emtyp destructor
}

void DelayEffect::prepare(dsp::ProcessSpec spec)
{
	mSampleRate = spec.sampleRate;
	mSamplesPerBlock = spec.maximumBlockSize;
	const int numChannels = spec.numChannels;

	for (auto channel = 0; channel < numChannels; ++channel)
	{
		mDelayBuffer.push_back(
			std::unique_ptr<circular_buffer<float>>(new circular_buffer<float>(2 * (mSampleRate + mSamplesPerBlock))));
	}
}

void DelayEffect::reset()
{
	// Empty reset function
}

void DelayEffect::process(dsp::ProcessContextReplacing<float> context)
{
	dsp::AudioBlock<float> inputBlock = context.getInputBlock();

	// Read input buffer into delay buffer
	for (auto channel = 0; channel < inputBlock.getNumChannels(); ++channel)
	{
		const float* input = inputBlock.getChannelPointer(channel);
		for (auto sample = 0; sample < inputBlock.getNumSamples(); ++sample)
		{
			mDelayBuffer[channel]->put(input[sample]);
		}
	}

}
