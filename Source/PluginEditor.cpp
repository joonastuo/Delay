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
	int windowWidth  = 2 * mReductionSize + 2 * mSliderSize + mControlPanelSpaceW;
	int windowHeight = 2 * mReductionSize + 2 * mSliderSize + 2 * mLabelHeight + mTitleHeight + mSpaceBetween + mControlPanelSpaceH;
    setSize (windowWidth, windowHeight);
	initialiseGUI();
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor()
{
	// Empty destructor
	mDelaySlider.setLookAndFeel(nullptr);
	mFBSlider   .setLookAndFeel(nullptr);
	mMixSlider  .setLookAndFeel(nullptr);
}

//==============================================================================
void DelayAudioProcessorEditor::paint (Graphics& g)
{
	Colour bgColour = getLookAndFeel().findColour(ResizableWindow::backgroundColourId);
    g.fillAll (bgColour);

	auto area = getLocalBounds().reduced(mReductionSize / 2.f, mReductionSize / 2.f);
	auto titleArea = area.removeFromBottom(mTitleHeight);
	drawTitle(g, titleArea.toFloat());
}

//==============================================================================
void DelayAudioProcessorEditor::drawTitle(Graphics & g, Rectangle<float> area)
{
	Colour bgColour = getLookAndFeel().findColour(ResizableWindow::backgroundColourId);

	Path textPath;
	GlyphArrangement glyphs;
	float x = area.getX(); ;
	float y = area.getY();
	float w = area.getWidth();
	float h = area.getHeight();

	glyphs.addFittedText(mTitleFont, mTitleText, x, y - 3.f, w, h, Justification::centred, 1);
	glyphs.createPath(textPath);

	g.setColour(bgColour);
	auto textBounds = textPath.getBounds().expanded(8.f, 8.f);
	g.setColour(bgColour.darker(.4));
	g.fillRoundedRectangle(textBounds.toFloat(), 18.f);

	g.setColour(juce::Colours::white);
	PathStrokeType strokeType(2.5f);
	g.fillPath(textPath);
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
		FlexItem(mMixLabel) .withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mMixSlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});

	// DELAY TIME ========================
	FlexBox delayBox;
	delayBox.alignContent = FlexBox::AlignContent::center;
	delayBox.justifyContent = FlexBox::JustifyContent::center;
	delayBox.flexDirection = FlexBox::Direction::column;
	delayBox.items.addArray(
		{
		FlexItem(mDelayLabel) .withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mDelaySlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});

	// FEEDBACK ===========================
	FlexBox feedbackBox;
	feedbackBox.alignContent = FlexBox::AlignContent::center;
	feedbackBox.justifyContent = FlexBox::JustifyContent::center;
	feedbackBox.flexDirection = FlexBox::Direction::column;
	feedbackBox.items.addArray(
		{
		FlexItem(mFBLabel) .withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mFBSlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});

	// DELAY + FEEDBACK ===================
	FlexBox firstBox;
	firstBox.alignContent = FlexBox::AlignContent::spaceBetween;
	firstBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
	firstBox.flexDirection = FlexBox::Direction::row;
	firstBox.items.addArray(
		{
		FlexItem(delayBox)   .withWidth(mSliderSize + (mControlPanelSpaceW / 2.f)).withHeight(mSliderSize + mLabelHeight),
		FlexItem(feedbackBox).withWidth(mSliderSize + (mControlPanelSpaceW / 2.f)).withHeight(mSliderSize + mLabelHeight)
		});

	// MASTER =============================
	float masterItemWidth = (2.f * mSliderSize) + mControlPanelSpaceW;
	float masterItemHeight = mSliderSize + mLabelHeight + mControlPanelSpaceH / 2.f;

	FlexBox masterBox;
	masterBox.alignContent = FlexBox::AlignContent::spaceBetween;
	masterBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
	masterBox.flexDirection = FlexBox::Direction::column;
	masterBox.items.addArray({
			FlexItem(firstBox).withWidth(masterItemWidth).withHeight(masterItemHeight),
			FlexItem(wetBox)  .withWidth(masterItemWidth).withHeight(masterItemHeight)
		});

	auto area = getLocalBounds().reduced(mReductionSize, mReductionSize);
	area.removeFromBottom(mTitleHeight + mSpaceBetween);
	masterBox.performLayout(area.toFloat());
}

//==============================================================================
void DelayAudioProcessorEditor::initialiseGUI()
{
	// DELAY TIME ==============================
	// Slider
	mDelaySlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mDelaySlider.setSize(mSliderSize, mSliderSize);
	mDelaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, mSliderSize, mTextBoxHeight);
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
	mMixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, mSliderSize, mTextBoxHeight);
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
	mFBSlider.setTextBoxStyle(Slider::TextBoxBelow, false, mSliderSize, mTextBoxHeight);
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
