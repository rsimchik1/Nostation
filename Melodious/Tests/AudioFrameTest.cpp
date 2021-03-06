#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../Source/Model/AudioFrame.h"
#include "../Source/Exceptions/InvalidFrameException.h"
#include "../Source/Exceptions/InvalidSampleException.h"
#include "../Source/Exceptions/IndexOutOfBoundsException.h"

BOOST_AUTO_TEST_SUITE(AudioFrameTest);

	BOOST_AUTO_TEST_CASE(AudioFrameConstructor)
	{
		auto frame = AudioFrame(2);
		BOOST_CHECK_EQUAL(frame.getNumChannels(), 2);
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 0.0f);
		BOOST_CHECK_EQUAL(frame.readSampleAt(1), 0.0f);
		BOOST_CHECK_THROW(AudioFrame(0), InvalidFrameException);
		BOOST_CHECK_THROW(AudioFrame(-1), InvalidFrameException);
		BOOST_CHECK_THROW(AudioFrame(-100), InvalidFrameException);
		auto copy = AudioFrame(frame);
		BOOST_CHECK_EQUAL(copy.getNumChannels(), frame.getNumChannels());
		BOOST_CHECK_EQUAL(copy.readSampleAt(0), frame.readSampleAt(0));
		BOOST_CHECK_EQUAL(copy.readSampleAt(1), frame.readSampleAt(1));
	}

	BOOST_AUTO_TEST_CASE(AudioFrameWriteSampleAt)
	{
		auto frame = AudioFrame(2);
		BOOST_CHECK_NO_THROW(frame.writeSampleAt(0, 0.5f));
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 0.5f);
		BOOST_CHECK_NO_THROW(frame.writeSampleAt(1, -0.5f));
		BOOST_CHECK_EQUAL(frame.readSampleAt(1), -0.5f);
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 0.5f);
		BOOST_CHECK_NO_THROW(frame.writeSampleAt(0, 1.0f));
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 1.0f);

		BOOST_CHECK_THROW(frame.writeSampleAt(2, 0.0f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(100, 0.0f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(-1, 0.0f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(-100, 0.0f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(0, 1.001f),
			InvalidSampleException);
		BOOST_CHECK_THROW(frame.writeSampleAt(0, -1.001f),
			InvalidSampleException);
		BOOST_CHECK_THROW(frame.writeSampleAt(0, 100.0f),
			InvalidSampleException);
		BOOST_CHECK_THROW(frame.writeSampleAt(0, -100.0f),
			InvalidSampleException);
	}

	BOOST_AUTO_TEST_CASE(AudioFrameReadSampleAt)
	{
		auto frame = AudioFrame(2);
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 0.0f);
		frame.writeSampleAt(0, 0.5f);
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 0.5f);
		BOOST_CHECK_THROW(frame.readSampleAt(-1), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.readSampleAt(2), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.readSampleAt(-100), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.readSampleAt(100), IndexOutOfBoundsException);
	}

	BOOST_AUTO_TEST_CASE(AudioFrameGetNumChannels)
	{
		auto frame1 = AudioFrame(1);
		auto frame2 = AudioFrame(2);
		auto frame3 = AudioFrame(3);
		BOOST_CHECK_EQUAL(frame1.getNumChannels(), 1);
		BOOST_CHECK_EQUAL(frame2.getNumChannels(), 2);
		BOOST_CHECK_EQUAL(frame3.getNumChannels(), 3);
		BOOST_CHECK_EQUAL(frame1.getNumChannels() + frame2.getNumChannels(),
			frame3.getNumChannels());
	}

BOOST_AUTO_TEST_SUITE_END();