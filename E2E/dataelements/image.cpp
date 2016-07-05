#include "image.h"

// #include <ostream>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"


namespace
{
	struct ImageHeader
	{
		uint8_t  undef[0x40 - E2E::MDbData::headerSize];
		uint32_t u1;
		uint32_t u2;
		uint32_t breite;
		uint32_t hoehe;
	} __attribute__((packed));
}

namespace E2E
{

	Image::Image(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	, header(new ImageHeader)
	, image (new cv::Mat)
	{
		if(data.getImageSubId() == 0) // SLO
			readCVImage(stream, *image, CV_8UC1);
		else // BScan
			readCVImage(stream, *image, CV_16UC1);
	}

	Image::Image(cv::Mat* image, std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	, header(nullptr)
	, image(image)
	{

	}


	Image::~Image()
	{
		delete reinterpret_cast<ImageHeader*>(header);
		delete image;
	}


	void Image::readCVImage(std::istream& stream, cv::Mat& image, int cvFormat)
	{
		ImageHeader* head = reinterpret_cast<ImageHeader*>(header);
		StreamHelper::readFStream(stream, head);

		/*
#ifndef NDEBUG
		std::cout << "header: " << head->breite << " - " << head->hoehe << " | " << head->u1 << " - " << head->u2;

		std::cout << '\t';
		for(int i=0; i<sizeof(ImageHeader::undef); ++i)
			std::cout << std::hex << std::setw(2) << (static_cast<unsigned>(head->undef[i]) & 0xFF) << ' ';

		std::cout << std::dec << std::endl;
#endif
		*/

		image = cv::Mat(head->breite, head->hoehe, cvFormat);

		std::size_t num = head->breite*head->hoehe;
		stream.read(reinterpret_cast<char*>(image.data), num*image.elemSize());
	}

	Image* Image::fromJFIF(std::istream& stream, MDbData& data)
	{
		std::size_t readLengt  = data.getDataLength(); // TODO
		std::size_t readAdress = data.getDataAdress() + 60 + 0x10;

		cv::Mat inputArray(readLengt, 1, CV_8UC1);

		stream.seekg(readAdress);
		stream.read(reinterpret_cast<char*>(inputArray.data), readLengt);

		cv::Mat* image = new cv::Mat;
		*image = cv::imdecode(inputArray, CV_LOAD_IMAGE_ANYDEPTH);
		return new Image(image, stream, data);
	}


}
