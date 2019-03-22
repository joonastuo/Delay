/*
  ==============================================================================

    LFO.cpp
    Created: 21 Mar 2019 12:02:50pm
    Author:  Joonas

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LFO.h"
#define _USE_MATH_DEFINES
#include <math.h>

//==============================================================================
LFO::LFO()
{
	// Triangle wave
	// Functions calculated from coefficients m and b
	// y = mx + b
	// Rising edge 1
	float mt1 = 1.f / 256.f;
	float bt1 = 0.f;

	// Rising edge 2
	float mt2 =  1.f / 256.f;
	float bt2 = -1.f;

	// Falling edge
	float mtf2 = -2.f / 512.f;
	float btf2  = 1.f;

	// Sawtooth
	// Rising edge 1
	float ms1 = 1.f / 512.f;
	float bs1 = 0.f;

	// Risign edge 2
	float ms2 =  1.f / 512.f;
	float bs2 = -1.f;

	for (auto i = 0; i < 1024; ++i)
	{
		// Sin
		mSinArray[i] = sin((static_cast<float> (i) / 1024.f) * (2 * M_PI));
		mRectSinArray[i] = 2 * abs(mSinArray[i]) - 1;

		// Triangle
		if (i < 256)
			mTriangleArray[i] = mt1 * i + bt1;
		else if (i >= 256 && i < 768)
			mTriangleArray[i] = mtf2 * (i - 256) + btf2;
		else
			mTriangleArray[i] = mt2 * (i - 768) + bt2;

		// Sawtooth
		mSawtoothArray[i] = i < 512 ? ms1 * i + bs1 : ms2 * (i - 511) + bs2;

		// Square
		mSquareArray[i] = i < 512 ? 1.f : -1.f;
	}
}

LFO::~LFO()
{
	// Empty destructor
}

void LFO::prepare(dsp::ProcessSpec spec)
{
	mSampleRate = spec.sampleRate;
	mSamplesPerBlock = spec.maximumBlockSize;
}

float LFO::getValue()
{
	float LFOVal = 0.f;
	int readIndex = floor(mReadIndex);
	float frac = mReadIndex - readIndex;
	int readIndexNext = readIndex + 1 > 1023 ? 0 : readIndex + 1;

	switch (mWaveform)
	{
	case Waveforms::sine:
		LFOVal = linearInterp(mSinArray[readIndex], mSinArray[readIndexNext], frac);
		break;
	case Waveforms::rectSine:
		LFOVal = linearInterp(mRectSinArray[readIndex], mRectSinArray[readIndexNext], frac);
		break;
	case Waveforms::saw:
		LFOVal = linearInterp(mSawtoothArray[readIndex], mSawtoothArray[readIndexNext], frac);
		break;
	case Waveforms::tri:
		LFOVal = linearInterp(mTriangleArray[readIndex], mTriangleArray[readIndexNext], frac);
		break;
	case Waveforms::square:
		LFOVal = linearInterp(mSquareArray[readIndex], mSquareArray[readIndexNext], frac);
		break;
	default:
		LFOVal = linearInterp(mSinArray[readIndex], mSinArray[readIndexNext], frac);
		break;
	}

	if (mUnipolar)
	{
		LFOVal /= 2;
		LFOVal += 0.5;

		if (LFOVal < 0 || LFOVal > 1)
			return 0.f;
	}

	return LFOVal;
}

void LFO::setFreq(const float & freq)
{
	mInc = 1024.f * (freq / mSampleRate);
}

void LFO::setUnipolar(const bool & isUnipolar)
{
	mUnipolar = isUnipolar;
}

void LFO::setWaveform(const int & waveform)
{
	mWaveform = waveform;
}

void LFO::advanceSamples(const int & numSamples)
{
	mReadIndex += (mInc * numSamples);
	if (mReadIndex > 1024)
		mReadIndex = mReadIndex - 1024;
}

void LFO::advanceBlock()
{
	mReadIndex += (mInc * mSamplesPerBlock);
	if (mReadIndex > 1024)
		mReadIndex = mReadIndex - 1024;
}

float LFO::linearInterp(const float & y0, const float & yp1, const float & frac)
{
	return y0 * (1 - frac) + yp1  * frac;
}

