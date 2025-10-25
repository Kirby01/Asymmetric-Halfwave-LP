#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class AsymHalfLowpassAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    AsymHalfLowpassAudioProcessorEditor (AsymHalfLowpassAudioProcessor&);
    ~AsymHalfLowpassAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    AsymHalfLowpassAudioProcessor& processor;

    juce::Slider posSlider, negSlider, mixSlider;
    juce::Label posLabel, negLabel, mixLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> posAttach, negAttach, mixAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AsymHalfLowpassAudioProcessorEditor)
};
