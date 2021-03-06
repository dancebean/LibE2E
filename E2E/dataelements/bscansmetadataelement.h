/*
 * Copyright (c) 2018 Kay Gawlik <kaydev@amarunet.de> <kay.gawlik@beuth-hochschule.de> <kay.gawlik@charite.de>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once

#include <istream>
#include <vector>

#include "baseelement.h"



namespace E2E
{
	class MDbData;

	class BScansMetaDataElement : public BaseElement
	{
	public:
		struct BScansData
		{
			double x1;
			double y1;
			double x2;
			double y2;
		};
		typedef std::vector<BScansData> MetaDataList;

		BScansMetaDataElement(std::istream& stream, MDbData& data);
		~BScansMetaDataElement();

		const MetaDataList& getMetaData() const                  { return dataVec; }
		MetaDataList::const_iterator begin() const               { return dataVec.begin(); }
		MetaDataList::const_iterator end() const                 { return dataVec.end();   }
	private:
		MetaDataList dataVec;
	};

}

