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
    setSize (400, 200);
	initialiseGUI();
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor()
{
}

//==============================================================================
void DelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void DelayAudioProcessorEditor::resized()
{
	// WETNESS ===========================
	FlexBox wetBox;
	wetBox.alignContent = FlexBox::AlignContent::center;
	wetBox.justifyContent = FlexBox::JustifyContent::center;
	wetBox.flexDirection = FlexBox::Direction::column;
	wetBox.items.addArray(
		{
		FlexItem(mFFLabel).withWidth(100.f).withHeight(20.f),
		FlexItem(mFFSlider).withWidth(100.f).withHeight(100.f)
		});

	// DELAY TIME ========================
	FlexBox delayBox;
	delayBox.alignContent = FlexBox::AlignContent::center;
	delayBox.justifyContent = FlexBox::JustifyContent::center;
	delayBox.flexDirection = FlexBox::Direction::column;
	delayBox.items.addArray(
		{
		FlexItem(mTimeLabel).withWidth(100.f).withHeight(20.f),
		FlexItem(mTimeSlider).withWidth(100.f).withHeight(100.f)
		});

	// FEEDBACK ===========================
	FlexBox feedbackBox;
	feedbackBox.alignContent = FlexBox::AlignContent::center;
	feedbackBox.justifyContent = FlexBox::JustifyContent::center;
	feedbackBox.flexDirection = FlexBox::Direction::column;
	feedbackBox.items.addArray(
		{
		FlexItem(mFBLabel).withWidth(100.f).withHeight(20.f),
		FlexItem(mFBSlider).withWidth(100.f).withHeight(100.f)
		});

	// MASTER =============================
	FlexBox masterBox;
	masterBox.alignContent = FlexBox::AlignContent::center;
	masterBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
	masterBox.flexDirection = FlexBox::Direction::row;
	masterBox.items.addArray({
			FlexItem(wetBox).withWidth(100.f).withHeight(120.f),
			FlexItem(delayBox).withWidth(100.f).withHeight(120.f),
			FlexItem(feedbackBox).withWidth(100.f).withHeight(120.f)
		});

	masterBox.performLayout(getLocalBounds().reduced(20, 10).toFloat());
}

void DelayAudioProcessorEditor::initialiseGUI()
{
	// DELAY TIME ==============================
	// Slider
	mTimeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mTimeSlider.setSize(100, 100);
	mTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
	mTimeSliderAttachment.reset(new SliderAttachment(mState, "time", mTimeSlider));
	addAndMakeVisible(mTimeSlider);

	// Label
	mTimeLabel.setText("Delay", dontSendNotification);
	mTimeLabel.setSize(100, 20);
	mTimeLabel.setFont(20);
	addAndMakeVisible(mTimeLabel);
	
	//// BL = =====================================
	//// Slider
	//mBLSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	//mBLSlider.setSize(100, 100);
	//mBLSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
	//mBLSliderAttachment.reset(new SliderAttachment(mState, "BL", mBLSlider));
	//addAndMakeVisible(mBLSlider);

	//// Label
	//mBLLabel.setText("BL", dontSendNotification);
	//addAndMakeVisible(mBLLabel);

	// FF = =====================================
	mFFSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mFFSlider.setSize(100, 100);
	mFFSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
	mFFSliderAttachment.reset(new SliderAttachment(mState, "FF", mFFSlider));
	addAndMakeVisible(mFFSlider);

	// Label
	mFFLabel.setText("Dry/Wet", dontSendNotification);
	mFFLabel.setSize(100, 20);
	mFFLabel.setFont(20);
	addAndMakeVisible(mFFLabel);

	// FB = =====================================
	mFBSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mFBSlider.setSize(100, 100);
	mFBSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
	mFBSliderAttachment.reset(new SliderAttachment(mState, "FB", mFBSlider));
	addAndMakeVisible(mFBSlider);

	// Label
	mFBLabel.setText("Feedback", dontSendNotification);
	mFBLabel.setSize(100, 20);
	mFBLabel.setFont(20);
	addAndMakeVisible(mFBLabel);
}
