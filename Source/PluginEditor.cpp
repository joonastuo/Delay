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
    setSize (200, 200);
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
	FlexBox masterBox;
	masterBox.alignContent = FlexBox::AlignContent::center;
	masterBox.justifyContent = FlexBox::JustifyContent::center;
	masterBox.flexDirection = FlexBox::Direction::column;
	masterBox.items.addArray({
								FlexItem(mTimeSlider).withWidth(100.f).withHeight(100.f)
							 });
	masterBox.performLayout(getLocalBounds().toFloat());
}

void DelayAudioProcessorEditor::initialiseGUI()
{
	mTimeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mTimeSlider.setSize(100, 100);
	mTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100.f, 20.f);
	mTimeSliderAttachment.reset(new SliderAttachment(mState, "time", mTimeSlider));
	addAndMakeVisible(mTimeSlider);
}
