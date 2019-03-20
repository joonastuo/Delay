/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

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

	// Delay time
	Slider mTimeSlider;
	Label  mTimeLabel;
	std::unique_ptr<SliderAttachment> mTimeSliderAttachment;

	// BL
	Slider mBLSlider;
	Label  mBLLabel;
	std::unique_ptr<SliderAttachment> mBLSliderAttachment;

	// Feed forward
	Slider mFFSlider;
	Label  mFFLabel;
	std::unique_ptr<SliderAttachment> mFFSliderAttachment;

	// Feedback
	Slider mFBSlider;
	Label  mFBLabel;
	std::unique_ptr<SliderAttachment> mFBSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessorEditor)
};
