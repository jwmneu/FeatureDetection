/*
 * VideoImageSource.cpp
 *
 *  Created on: 20.08.2012
 *      Author: poschmann
 */

#include "imageio/VideoImageSource.hpp"
#include "boost/lexical_cast.hpp"
#include <iostream>
#include <string>

using boost::lexical_cast;
using std::string;

namespace imageio {

VideoImageSource::VideoImageSource(int device) : capture(device), frame(), frameCounter(0) {
	if (!capture.isOpened())
		std::cerr << "Could not open stream from device " << device << std::endl;
}

VideoImageSource::VideoImageSource(string video) : capture(video), frame(), frameCounter(0) {
	if (!capture.isOpened())
		std::cerr << "Could not open video file '" << video << "'" << std::endl;
}

VideoImageSource::~VideoImageSource() {
	capture.release();
}

const Mat VideoImageSource::get() {
	if (next()) {
		return frame;
	} else {
		return Mat();
	}
}

const bool VideoImageSource::next()
{
	capture >> frame;
	++frameCounter;	// We'll overflow after 2 years at 60fps... guess that's not a problem?
	return true; // TODO: How can we find out here if we've reached the end of a video file?
}

const Mat VideoImageSource::getImage() const
{
	return frame;
}

const path VideoImageSource::getName() const
{
	return path(lexical_cast<string>(frameCounter));
}

const vector<path> VideoImageSource::getNames() const
{
	vector<path> tmp;
	tmp.push_back(path(lexical_cast<string>(frameCounter)));
	return tmp;
}


} /* namespace imageio */
