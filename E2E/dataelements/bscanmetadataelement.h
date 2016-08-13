#pragma once

#include <istream>
#include <vector>

#include "baseelement.h"



namespace E2E
{
	class MDbData;

	class BScanMetaDataElement : public BaseElement
	{
	public:
		struct BScanData
		{
			double x1 = 0.0;
			double y1 = 0.0;
			double x2 = 0.0;
			double y2 = 0.0;
		};

		BScanMetaDataElement(std::istream& stream, MDbData& data);
		~BScanMetaDataElement();

		double getX1() const                                     { return bscanData.x1;}
		double getY1() const                                     { return bscanData.y1;}
		double getX2() const                                     { return bscanData.x2;}
		double getY2() const                                     { return bscanData.y2;}

	private:
		BScanData bscanData;
	};

}

