/*
  ==============================================================================

    Delay.cpp
    Created: 14 Mar 2019 7:31:38am
    Author:  Joonas

  ==============================================================================
*/

#include "Delay.h"

//==============================================================================
DelayEffect::DelayEffect(AudioProcessorValueTreeState& state)
	: mState(state)
{
	// Empty constructor
}

//==============================================================================
DelayEffect::~DelayEffect()
{
	// Emtyp destructor
}

//==============================================================================
void DelayEffect::prepare(dsp::ProcessSpec spec)
{
	mSampleRate = spec.sampleRate;
	mSamplesPerBlock = spec.maximumBlockSize;
	mNumChannels = spec.numChannels;
	mDelayBufferLen = 2 * (mSampleRate + mSamplesPerBlock);
	mDelayBuffer.setSize(mNumChannels, mDelayBufferLen, false, true);
	mDelayBuffer.clear();
}

//==============================================================================
void DelayEffect::reset()
{
	// Empty reset function
}

//==============================================================================
void DelayEffect::process(AudioBuffer<float>& buffer)
{
	float gain = 0.5f;
	float time = *mState.getRawParameterValue("time");

	for (auto channel = 0; channel < mNumChannels; ++channel)
	{
		const float* input = buffer.getReadPointer(channel);
		fillDelayBuffer(input, channel, mLastInputGain, gain);
	}
	mLastInputGain = gain;

	const int64 readPos = static_cast<int64> (mDelayBufferLen + mWritePos - (mSampleRate * time / 1000.0)) % mDelayBufferLen;

	for (auto channel = 0; channel < mNumChannels; ++channel)
	{
		if (mDelayBufferLen > readPos + mSamplesPerBlock)
		{
			buffer.addFrom(channel, 0, mDelayBuffer.getReadPointer(channel, readPos), mSamplesPerBlock);
		}
		else
		{
			const int64 midPos = mDelayBufferLen - readPos;
			buffer.addFrom(channel, 0, mDelayBuffer.getReadPointer(channel, readPos), midPos);
			buffer.addFrom(channel, midPos, mDelayBuffer.getReadPointer(channel), mSamplesPerBlock - midPos);
		}
	}

	mWritePos += mSamplesPerBlock;
	mWritePos %= mDelayBufferLen;
}

//==============================================================================
// Write input buffer to delay buffer
//
void DelayEffect::fillDelayBuffer(const float* input, const int channel, float startGain, float endGain)
{
	const float* delayInput = mDelayBuffer.getReadPointer(channel);

	if (mDelayBufferLen > mSamplesPerBlock + mWritePos)
	{
		mDelayBuffer.copyFromWithRamp(channel, mWritePos, input, mSamplesPerBlock, startGain, endGain);
	}
	else
	{
		const int midPos = mDelayBufferLen - mWritePos;
		const float midGain = mLastInputGain + ((startGain - endGain) / mSamplesPerBlock) * (midPos / mSamplesPerBlock);
		mDelayBuffer.copyFromWithRamp(channel, mWritePos, input, midPos, startGain, midGain);
		mDelayBuffer.copyFromWithRamp(channel, 0, input, mSamplesPerBlock - midPos, midGain, endGain);
	}
}
