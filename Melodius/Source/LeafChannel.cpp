#include "LeafChannel.h"
#include "Exceptions/InvalidChannelTreeException.h"

LeafChannel::LeafChannel(Channel* parent)
{
	audioSource = nullptr;
	try
	{
		setParent(parent);
	}
	catch (InvalidChannelTreeException e)
	{
		throw e;
	}
}

LeafChannel::~LeafChannel()
{
	removeParent();
	delete audioSource;
}

AudioBuffer LeafChannel::processFrames(int numFrames, const Timeline &relativeTime)
{
	if (audioSource)
		return audioSource->processFrames(numFrames, relativeTime);
	else
		return AudioBuffer(numFrames, 2);
}

void LeafChannel::setAudioSource(AudioNode *audioSource)
{
	delete this->audioSource;
	this->audioSource = audioSource;
}

bool LeafChannel::hasChild(const Channel* childToFind)
{
	return false;
}

void LeafChannel::addChild(Channel* newChild)
{
	throw InvalidChannelTreeException();
}

void LeafChannel::removeChild(Channel* childToRemove)
{
	throw InvalidChannelTreeException();
}
