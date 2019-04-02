/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Helper/Identifiers.h"
#include "LookAndFeel/KnobLookAndFeel.h"

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
	void drawTitle(Graphics& g, Rectangle<float> area);
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
	const int mTextBoxHeight = 14;
	const int mReductionSize = 10;
	const int mTitleHeight   = 50;
	const int mSpaceBetween  = 10;
	const float mControlPanelSpaceW = 40.f;
	const float mControlPanelSpaceH = 10.f;
	
	String mTitleText = "Delay";
	Font mTitleFont = Font(30, Font::bold);

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
