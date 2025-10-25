#include "PluginEditor.h"

AsymHalfLowpassAudioProcessorEditor::AsymHalfLowpassAudioProcessorEditor (AsymHalfLowpassAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    auto& params = processor.parameters;

    posSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    posSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 18);
    posLabel.setText ("Positive Cutoff", juce::dontSendNotification);
    posLabel.attachToComponent (&posSlider, false);

    negSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    negSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 18);
    negLabel.setText ("Negative Cutoff", juce::dontSendNotification);
    negLabel.attachToComponent (&negSlider, false);

    mixSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 18);
    mixLabel.setText ("Mix", juce::dontSendNotification);
    mixLabel.attachToComponent (&mixSlider, false);

    addAndMakeVisible (posSlider);
    addAndMakeVisible (negSlider);
    addAndMakeVisible (mixSlider);

    posAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "posCutoff", posSlider);
    negAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "negCutoff", negSlider);
    mixAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "mix", mixSlider);

    setSize (380, 160);
}

void AsymHalfLowpassAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (18.0f);
    g.drawFittedText ("Asymmetric Halfwave LP - Harmonious Records", getLocalBounds().removeFromTop(24), juce::Justification::centred, 1);
}

void AsymHalfLowpassAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (20);
    auto sliderArea = area.removeFromBottom (100);
    posSlider.setBounds (sliderArea.removeFromLeft (120));
    negSlider.setBounds (sliderArea.removeFromLeft (120));
    mixSlider.setBounds (sliderArea);
}
