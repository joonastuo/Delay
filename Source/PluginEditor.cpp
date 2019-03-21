/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayAudioProcessorEditor::DelayAudioProcessorEditor (DelayAudioProcessor& p)
    : AudioProcessorEditor (&p), 
	  processor (p),
	  mState(p.getState())
{
	int windowWidth = 2 * mReductionSize + 2 * mSliderSize;
	int windowHeight = 2 * mReductionSize + 2 * mSliderSize + 2 * mLabelHeight;
    setSize (windowWidth, windowHeight);
	initialiseGUI();
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor()
{
	// Empty destructor
	mDelaySlider.setLookAndFeel(nullptr);
	mFBSlider.setLookAndFeel(nullptr);
	mMixSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void DelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

//==============================================================================
void DelayAudioProcessorEditor::resized()
{
	// WETNESS ===========================
	FlexBox wetBox;
	wetBox.alignContent = FlexBox::AlignContent::center;
	wetBox.justifyContent = FlexBox::JustifyContent::center;
	wetBox.flexDirection = FlexBox::Direction::column;
	wetBox.items.addArray(
		{
		FlexItem(mMixLabel).withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mMixSlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});

	// DELAY TIME ========================
	FlexBox delayBox;
	delayBox.alignContent = FlexBox::AlignContent::center;
	delayBox.justifyContent = FlexBox::JustifyContent::center;
	delayBox.flexDirection = FlexBox::Direction::column;
	delayBox.items.addArray(
		{
		FlexItem(mDelayLabel).withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mDelaySlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});

	// FEEDBACK ===========================
	FlexBox feedbackBox;
	feedbackBox.alignContent = FlexBox::AlignContent::center;
	feedbackBox.justifyContent = FlexBox::JustifyContent::center;
	feedbackBox.flexDirection = FlexBox::Direction::column;
	feedbackBox.items.addArray(
		{
		FlexItem(mFBLabel).withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mFBSlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});

	// DELAY + FEEDBACK ===================
	FlexBox firstBox;
	firstBox.alignContent = FlexBox::AlignContent::center;
	firstBox.justifyContent = FlexBox::JustifyContent::center;
	firstBox.flexDirection = FlexBox::Direction::row;
	firstBox.items.addArray(
		{
		FlexItem(delayBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight),
		FlexItem(feedbackBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight)
		});

	// MASTER =============================
	FlexBox masterBox;
	masterBox.alignContent = FlexBox::AlignContent::center;
	masterBox.justifyContent = FlexBox::JustifyContent::flexStart;
	masterBox.flexDirection = FlexBox::Direction::column;
	masterBox.items.addArray({
			FlexItem(firstBox).withWidth(2.f * mSliderSize).withHeight(mSliderSize + mLabelHeight),
			FlexItem(wetBox).withWidth(2.f * mSliderSize).withHeight(mSliderSize + mLabelHeight)
		});

	masterBox.performLayout(getLocalBounds().reduced(mReductionSize, mReductionSize).toFloat());
}

//==============================================================================
void DelayAudioProcessorEditor::initialiseGUI()
{
	// DELAY TIME ==============================
	// Slider
	mDelaySlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mDelaySlider.setSize(mSliderSize, mSliderSize);
	mDelaySlider.setTextBoxStyle(Slider::NoTextBox, true, mSliderSize, mTextBoxHeight);
	mTimeSliderAttachment.reset(new SliderAttachment(mState, IDs::time, mDelaySlider));
	addAndMakeVisible(mDelaySlider);
	mDelaySlider.setLookAndFeel(&mKnobLookAndFeel);
	mDelaySlider.setTextValueSuffix(" ms");

	// Label
	mDelayLabel.setText("Delay", dontSendNotification);
	mDelayLabel.setSize(mSliderSize, mLabelHeight);
	mDelayLabel.setFont(mLabelHeight);
	mDelayLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mDelayLabel);
	
	// MIX =====================================
	//Slider
	mMixSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mMixSlider.setSize(mSliderSize, mSliderSize);
	mMixSlider.setTextBoxStyle(Slider::NoTextBox, true, mSliderSize, mTextBoxHeight);
	mMixSliderAttachment.reset(new SliderAttachment(mState, IDs::wetness, mMixSlider));
	addAndMakeVisible(mMixSlider);
	mMixSlider.setLookAndFeel(&mKnobLookAndFeel);
	mMixSlider.setTextValueSuffix(" %");

	// Label
	mMixLabel.setText("Mix", dontSendNotification);
	mMixLabel.setSize(mSliderSize, mLabelHeight);
	mMixLabel.setFont(mLabelHeight);
	mMixLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mMixLabel);

	// FEEDBACK===================================
	// Slider
	mFBSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mFBSlider.setSize(mSliderSize, mSliderSize);
	mFBSlider.setTextBoxStyle(Slider::NoTextBox, true, mSliderSize, mTextBoxHeight);
	mFBSliderAttachment.reset(new SliderAttachment(mState, IDs::feedback, mFBSlider));
	addAndMakeVisible(mFBSlider);
	mFBSlider.setLookAndFeel(&mKnobLookAndFeel);
	mFBSlider.setTextValueSuffix(" %");

	// Label
	mFBLabel.setText("Feedback", dontSendNotification);
	mFBLabel.setSize(mSliderSize, mLabelHeight);
	mFBLabel.setFont(mLabelHeight);
	mFBLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mFBLabel);
}
