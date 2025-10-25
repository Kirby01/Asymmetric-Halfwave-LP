#include "PluginProcessor.h"
#include "PluginEditor.h"

AsymHalfLowpassAudioProcessor::AsymHalfLowpassAudioProcessor()
: parameters (*this, nullptr, "PARAMETERS", {
      std::make_unique<juce::AudioParameterFloat>("posCutoff", "Positive Cutoff", 10.0f, 20000.0f, 1000.0f),
      std::make_unique<juce::AudioParameterFloat>("negCutoff", "Negative Cutoff", 10.0f, 20000.0f, 200.0f),
      std::make_unique<juce::AudioParameterFloat>("mix", "Mix", 0.0f, 1.0f, 0.5f)
  })
{
}

void AsymHalfLowpassAudioProcessor::prepareToPlay (double sampleRate, int)
{
    srate = sampleRate;
    pStateL = nStateL = pStateR = nStateR = 0.0f;
}

bool AsymHalfLowpassAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet()
        && (layouts.getMainInputChannelSet() == juce::AudioChannelSet::mono()
         || layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo());
}

void AsymHalfLowpassAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    auto totalCh = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();

    float posCut = *parameters.getRawParameterValue("posCutoff");
    float negCut = *parameters.getRawParameterValue("negCutoff");
    float mixVal = *parameters.getRawParameterValue("mix");

    float pCoef = 1.0f - std::exp (-2.0f * juce::MathConstants<float>::pi * posCut / (float)srate);
    float nCoef = 1.0f - std::exp (-2.0f * juce::MathConstants<float>::pi * negCut / (float)srate);

    for (int ch = 0; ch < totalCh; ++ch)
    {
        auto* data = buffer.getWritePointer (ch);
        float &pState = (ch == 0 ? pStateL : pStateR);
        float &nState = (ch == 0 ? nStateL : nStateR);

        for (int i = 0; i < numSamples; ++i)
        {
            float x = data[i];
            float p = std::max (x, 0.0f);
            float n = std::min (x, 0.0f);

            pState = (1.0f - pCoef) * pState + pCoef * p;
            nState = (1.0f - nCoef) * nState + nCoef * n;

            float wet = pState + nState;
            data[i] = (1.0f - mixVal) * x + mixVal * wet;
        }
    }
}
juce::AudioProcessorEditor* AsymHalfLowpassAudioProcessor::createEditor()
{
    return new AsymHalfLowpassAudioProcessorEditor (*this);
}


juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AsymHalfLowpassAudioProcessor();
}
