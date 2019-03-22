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
	// Set specs to class variables
	mSampleRate = spec.sampleRate;
	mSamplesPerBlock = spec.maximumBlockSize;
	mNumChannels = spec.numChannels;
	mDelayBufferLen = 2 * (mSampleRate + mSamplesPerBlock);

	// Prepare delay lines
	for (auto& dline : delayLines)
	{
		dline.resize(mDelayBufferLen);
		dline.clear();
	}
	// Prepare smoothed values
	float feedback = *mState.getRawParameterValue(IDs::feedback);
	float wet	   = *mState.getRawParameterValue(IDs::wetness);
	float time	   = *mState.getRawParameterValue(IDs::time);

	float FB = feedback / 100.f;
	float W = wet / 100.f;
	float G = 1 - W;
	mLastTime = time;

	for (int channel = 0; channel < 2; ++channel)
	{
		mSmoothFB[channel].reset(mSamplesPerBlock);
		mSmoothW[channel].reset(mSamplesPerBlock);
		mSmoothG[channel].reset(mSamplesPerBlock);

		mSmoothFB[channel].setCurrentAndTargetValue(FB);
		mSmoothW[channel].setCurrentAndTargetValue(W);
		mSmoothG[channel].setCurrentAndTargetValue(G);
	}
}

//==============================================================================
void DelayEffect::reset()
{
	// Empty reset function
}

//==============================================================================
void DelayEffect::process(AudioBuffer<float>& buffer)
{
	// Get user parameters
	float feedback = *mState.getRawParameterValue(IDs::feedback);
	float wet	   = *mState.getRawParameterValue(IDs::wetness);
	float time	   = *mState.getRawParameterValue(IDs::time);

	float FB = feedback / 100.f;
	float W  = wet / 100.f;
	float G  = 1 - W;

	for (int channel = 0; channel < 2; ++channel)
	{
		mSmoothFB[channel].setValue(FB);
		mSmoothW[channel].setValue(W);
		mSmoothG[channel].setValue(G);
	}

	// Clear felay buffers is time is changed and play only input
	// as otherwise will hear crackle
	if (time != mLastTime)
	{
		W = 0;
		G = 1;
		for (auto& dline : delayLines)
		{
			dline.clear();
		}
	}
	mLastTime = time;

	// Time to samples
	float delayInSamplesFrac = mSampleRate * (time / 1000.f);
	int delayInSamplesInt = static_cast<int> (delayInSamplesFrac);
	float delayFrac = delayInSamplesFrac - delayInSamplesInt;

	// Add delay into buffer
	for (auto channel = 0; channel < buffer.getNumChannels(); ++channel)
	{
		// Get smoothed parameter values
		FB = mSmoothFB[channel].getNextValue();
		W = mSmoothW[channel].getNextValue();
		G = mSmoothG[channel].getNextValue();

		const float* input = buffer.getReadPointer(channel);
		float* output = buffer.getWritePointer(channel);

		for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			float delayedSample = 0.f;

			// Fractal delay with liner interpolation if neede
			if (delayFrac != 0)
			{
				float y0  = delayLines[channel].get(delayInSamplesInt);
				float ym1 = delayLines[channel].get(delayInSamplesInt + 1);
				delayedSample = linearInterp(y0, ym1, delayFrac);
			}
			else
			{
				delayedSample = delayLines[channel].get(delayInSamplesInt);
			}

			auto inputSample = input[sample];
			delayLines[channel].push(inputSample + delayedSample * FB);
			output[sample] = inputSample * G + delayedSample * W;
		}
	}
}

//==============================================================================
// Linear interpolation used with fractal delays
float DelayEffect::linearInterp(const float& y0, const float& yp1, const float& frac)
{
	return yp1 * frac + y0 * (1 - frac);
}
