/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Identifiers.h"
#include "KnobLookAndFeel.h"

//==============================================================================
/**
*/
class DelayAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DelayAudioProcessorEditor (DelayAudioProcessor&);
    ~DelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void initialiseGUI();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DelayAudioProcessor& processor;
	AudioProcessorValueTreeState& mState;

	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

	// Slider parameters
	const int mSliderSize    = 80;
	const int mLabelHeight   = 20;
	const int mTextBoxHeight = 12;
	const int mReductionSize = 20;
	
	// Look and feel
	KnobLookAndFeel mKnobLookAndFeel;

	// Delay time
	Slider mDelaySlider;
	Label  mDelayLabel;
	std::unique_ptr<SliderAttachment> mTimeSliderAttachment;

	// Mix (wetness)
	Slider mMixSlider;
	Label  mMixLabel;
	std::unique_ptr<SliderAttachment> mMixSliderAttachment;

	// Feedback (gain)
	Slider mFBSlider;
	Label  mFBLabel;
	std::unique_ptr<SliderAttachment> mFBSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessorEditor)
};
