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
	float feedback = 0.5f;
	float time = *mState.getRawParameterValue("time");

	// Write input buffer to delay buffer
	for (auto channel = 0; channel < mNumChannels; ++channel)
	{
		fillDelayBuffer(buffer, channel, mLastInputGain, gain);
	}
	mLastInputGain = gain;

	const int64 readPos = static_cast<int64> (mDelayBufferLen + mWritePos - (mSampleRate * time / 1000.0)) % mDelayBufferLen;

	// Copy mSamplesPerBlock samples from delay buffer (readPos) to output buffer
	for (auto channel = 0; channel < mNumChannels; ++channel)
	{
		copyFromDelayBuffer(buffer, channel, readPos);
	}

	// Add feedback to delay buffer
	for (auto channel = 0; channel < mNumChannels; ++channel)
	{
		feedbackDelayBuffer(buffer, channel, mLastFeedbackGain, feedback);
	}
	mLastFeedbackGain = feedback;

	mWritePos += mSamplesPerBlock;
	mWritePos %= mDelayBufferLen;
}

//==============================================================================
// Write input buffer to delay buffer
//
void DelayEffect::fillDelayBuffer(AudioBuffer<float>& buffer, const int& channel, float& startGain, float& endGain)
{
	if (mDelayBufferLen > mSamplesPerBlock + mWritePos)
	{
		mDelayBuffer.copyFromWithRamp(channel, mWritePos, buffer.getReadPointer(channel), mSamplesPerBlock, startGain, endGain);
	}
	else
	{
		const int midPos = mDelayBufferLen - mWritePos;
		const float midGain = mLastInputGain + ((endGain - startGain) / mSamplesPerBlock) * (midPos / mSamplesPerBlock);
		mDelayBuffer.copyFromWithRamp(channel, mWritePos, buffer.getReadPointer(channel), midPos, startGain, midGain);
		mDelayBuffer.copyFromWithRamp(channel, 0, buffer.getReadPointer(channel), mSamplesPerBlock - midPos, midGain, endGain);
	}
}

//==============================================================================
// Copy mSamplesPerBlock samples from position readPos to output buffer
//
void DelayEffect::copyFromDelayBuffer(AudioBuffer<float>& buffer, const int& channel, const int64& readPos)
{
		if (mDelayBufferLen > readPos + mSamplesPerBlock)
		{
			buffer.copyFrom(channel, 0, mDelayBuffer.getReadPointer(channel) + readPos, mSamplesPerBlock);
		}
		else
		{
			const int64 midPos = mDelayBufferLen - readPos;
			buffer.copyFrom(channel, 0, mDelayBuffer.getReadPointer(channel) + readPos, midPos);
			buffer.copyFrom(channel, midPos, mDelayBuffer.getReadPointer(channel), mSamplesPerBlock - midPos);
		}
}

//==============================================================================
// Add feedbakc to delay buffer
//
void DelayEffect::feedbackDelayBuffer(AudioBuffer<float>& buffer, const int & channel, const float & startGain, const float & endGain)
{
		if (mDelayBufferLen > mSamplesPerBlock + mWritePos)
		{
			mDelayBuffer.addFromWithRamp(channel, mWritePos, buffer.getWritePointer(channel), mSamplesPerBlock, startGain, endGain);
		}
		else
		{
			const int64 midPos = mDelayBufferLen - mWritePos;
			const float midGain = mLastFeedbackGain + ((endGain - startGain) / mSamplesPerBlock) * (midPos / mSamplesPerBlock);
			mDelayBuffer.addFromWithRamp(channel, mWritePos, buffer.getWritePointer(channel), midPos, startGain, midGain);
			mDelayBuffer.addFromWithRamp(channel, 0, buffer.getWritePointer(channel), mSamplesPerBlock - midPos, midGain, endGain);
		}
}
