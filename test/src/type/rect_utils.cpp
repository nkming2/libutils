/*
 * rect_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <string>

#include <gtest/gtest.h>

#include <libutils/type/coord.h>
#include <libutils/type/rect.h>
#include <libutils/type/rect_utils.h>

using namespace utils::type;

GTEST_TEST(TypeRectUtils, IsInside)
{
	Rect r(0, 10, 20, 6);
	EXPECT_TRUE(RectUtils::IsInside(r, {15, 13}));
	EXPECT_FALSE(RectUtils::IsInside(r, {0, 13}));
	EXPECT_FALSE(RectUtils::IsInside(r, {15, 10}));
	EXPECT_FALSE(RectUtils::IsInside(r, {20, 13}));
	EXPECT_FALSE(RectUtils::IsInside(r, {15, 16}));
}

GTEST_TEST(TypeRectUtils, IsInsidePx)
{
	Rect r(0, 10, 20, 6);
	EXPECT_TRUE(RectUtils::IsInsidePx(r, {15, 13}));
	EXPECT_TRUE(RectUtils::IsInsidePx(r, {0, 13}));
	EXPECT_TRUE(RectUtils::IsInsidePx(r, {15, 10}));
	EXPECT_FALSE(RectUtils::IsInsidePx(r, {20, 13}));
	EXPECT_FALSE(RectUtils::IsInsidePx(r, {15, 16}));
}
