/*
 * bitmap_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <vector>

#include "libutils/bitmap/bitmap.h"
#include "libutils/bitmap/bitmap_utils.h"
#include "libutils/misc/step_iterator.h"
#include "libutils/type/misc.h"

using namespace std;

namespace utils
{
namespace bitmap
{

bool BitmapUtils::IsOpaque(const Bitmap &bmp)
{
	const vector<Byte> &data = bmp.GetData();
	// +3 to move to the first alpha byte.
	misc::StepIterator<decltype(data.cbegin())> it(data.cbegin() + 3, 4);

	const Uint count = bmp.GetSize().GetArea();
	for (Uint i = 0; i < count; ++i)
	{
		if (*it++ != 0xFF)
		{
			return false;
		}
	}
	return true;
}

vector<Byte> BitmapUtils::GetBgrData(const Bitmap &bmp)
{
	const vector<Byte> &data = bmp.GetData();
	vector<Byte> product(bmp.GetSize().GetArea() * 3);

	vector<Byte>::iterator dst_it = product.begin();
	vector<Byte>::const_iterator src_it = data.cbegin();
	while (src_it != data.cend())
	{
		*dst_it++ = *src_it++;
		*dst_it++ = *src_it++;
		*dst_it++ = *src_it++;
		++src_it;
	}
	return product;
}

}
}
