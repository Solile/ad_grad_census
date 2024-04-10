#include "adcensus_util.h"
#include <cassert>

void adcensus_util::census_transform_5x5(const uint8 *source, vector<uint32> &census, const sint32 &width, const sint32 &height)
{
	if (source == nullptr || census.empty() || width <= 5u || height <= 5u)
	{
		return;
	}

	// 逐像素计算census值
	for (sint32 i = 2; i < height - 2; i++)
	{
		for (sint32 j = 2; j < width - 2; j++)
		{

			// 中心像素值
			const uint8 gray_center = source[i * width + j];

			// 遍历大小为5x5的窗口内邻域像素，逐一比较像素值与中心像素值的的大小，计算census值
			uint32 census_val = 0u;
			for (sint32 r = -2; r <= 2; r++)
			{
				for (sint32 c = -2; c <= 2; c++)
				{
					census_val <<= 1; // 左移 value*2
					const uint8 gray = source[(i + r) * width + j + c];
					if (gray < gray_center)
					{
						census_val += 1;
					}
				}
			}

			// 中心像素的census值
			census[i * width + j] = census_val;
		}
	}
};

void adcensus_util::census_transform_9x7(const uint8 *source, vector<uint64> &census, const sint32 &width, const sint32 &height)
{
	if (source == nullptr || census.empty() || width <= 9 || height <= 7)
	{
		return;
	}

	// 逐像素计算census值
	for (sint32 i = 4; i < height - 4; i++)
	{
		for (sint32 j = 3; j < width - 3; j++)
		{

			// 中心像素值
			const uint8 gray_center = source[i * width + j];

			// 遍历大小为9x7的窗口内邻域像素，逐一比较像素值与中心像素值的的大小，计算census值
			uint64 census_val = 0u;
			for (sint32 r = -4; r <= 4; r++)
			{
				for (sint32 c = -3; c <= 3; c++)
				{
					census_val <<= 1;
					const uint8 gray = source[(i + r) * width + j + c];
					if (gray < gray_center)
					{
						census_val += 1;
					}
				}
			}

			// 中心像素的census值
			census[i * width + j] = census_val;
		}
	}
}

void adcensus_util::census_transform_dx2d(const uint8 *source, vector<uint64>& census, const sint32 &width, const sint32 &height)
{
	// d = max(x0-x3);
	sint32 d = 10;
	if (source == nullptr || census.empty() || width <= 4 * d + 1||height <= 2*d + 1)
	{
		return;
	}

	// 逐像素计算census值
	for (sint32 i = d; i < height - d; i++)
	{
		for (sint32 j = 2 * d; j < width - 2 * d; j++)
		{

			// 中心像素值
			const uint8 gray_center = source[i * width + j];

			// 遍历大小为5x5的窗口内邻域像素，逐一比较像素值与中心像素值的的大小，计算census值
			uint32 census_val = 0u;
			for (sint32 r = -d; r <= d; r++)
			{
				for (sint32 c = -2*d; c <= 2*d; c++)
				{
					census_val <<= 1; // 左移 value*2
					const uint8 gray = source[(i + r) * width + j + c];
					if (gray < gray_center)
					{
						census_val += 1;
					}
				}
			}

			// 中心像素的census值
			census[i * width + j] = census_val;
		}
	}
};

void adcensus_util::census_transform_9x7_improved(const uint8 *source, vector<uint64> &census, const sint32 &width, const sint32 &height)
{
	if (source == nullptr || census.empty() || width <= 9 || height <= 7)
	{
		return;
	}

	// 逐像素计算census值
	for (sint32 i = 4; i < height - 4; i++)
	{
		for (sint32 j = 3; j < width - 3; j++)
		{

			// 中心像素值
			const uint8 gray_center_original = source[i * width + j];
			// 区块均值

			uint8 u1_ = 0, u2_ = 0, u3_ = 0, u4_ = 0;
			for (sint32 r = -4; r <= 0; r++)
			{
				for (sint32 c = -3; c <= 0; c++)
				{
					u1_ += source[(i + r) * width + j + c];
				}
			}
			for (sint32 r = -4; r <= 0; r++)
			{
				for (sint32 c = 0; c <= 3; c++)
				{
					u2_ += source[(i + r) * width + j + c];
				}
			}
			for (sint32 r = 0; r <= 4; r++)
			{
				for (sint32 c = -3; c <= 0; c++)
				{
					u3_ += source[(i + r) * width + j + c];
				}
			}
			for (sint32 r = 0; r <= 4; r++)
			{
				for (sint32 c = 0; c <= 3; c++)
				{
					u4_ += source[(i + r) * width + j + c];
				}
			}

			// 区块图像均匀度
			uint8 u1 = 0, u2 = 0, u3 = 0, u4 = 0;
			for (sint32 r = -4; r <= 0; r++)
			{
				for (sint32 c = -3; c <= 0; c++)
				{
					u1 += source[(i + r) * width + j + c] - (u1_ / 20);
				}
			}
			for (sint32 r = -4; r <= 0; r++)
			{
				for (sint32 c = 0; c <= 3; c++)
				{
					u2 += source[(i + r) * width + j + c] - (u2_ / 20);
				}
			}
			for (sint32 r = 0; r <= 4; r++)
			{
				for (sint32 c = -3; c <= 0; c++)
				{
					u3 += source[(i + r) * width + j + c] - (u3_ / 20);
				}
			}
			for (sint32 r = 0; r <= 4; r++)
			{
				for (sint32 c = 0; c <= 3; c++)
				{
					u4 += source[(i + r) * width + j + c] - (u4_ / 20);
				}
			}

			const uint8 uMax = std::max(std::max(u1, u2), std::max(u3, u4));
			const uint8 uMin = std::min(std::min(u1, u2), std::min(u3, u4));
			uint8 uMax_, uMin_;
			if (uMax == u1)
			{
				uMax_ = u1_;
			}
			else if (uMax == u2)
			{
				uMax_ = u2_;
			}
			else if (uMax == u3)
			{
				uMax_ = u3_;
			}
			else
			{
				uMax_ = u4_;
			}

			if (uMin == u1)
			{
				uMin_ = u1_;
			}
			else if (uMin == u2)
			{
				uMin_ = u2_;
			}
			else if (uMin == u3)
			{
				uMin_ = u3_;
			}
			else
			{
				uMin_ = u4_;
			}

			const uint8 gray_center = (uMax_ + uMin_ - 2 * gray_center_original) / (2 * 20 - 2);
			// 中心像素值
			// const uint8 gray_center = source[i * width + j];

			// 遍历大小为9x7的窗口内邻域像素，逐一比较像素值与中心像素值的的大小，计算census值
			uint64 census_val = 0u;
			for (sint32 r = -4; r <= 4; r++)
			{
				for (sint32 c = -3; c <= 3; c++)
				{
					census_val <<= 1;
					const uint8 gray = source[(i + r) * width + j + c];
					if (gray < gray_center)
					{
						census_val += 1;
					}
				}
			}

			// 中心像素的census值
			census[i * width + j] = census_val;
		}
	}
}

uint8 adcensus_util::Hamming64(const uint64 &x, const uint64 &y)
{
	uint64 dist = 0, val = x ^ y;

	// Count the number of set bits
	while (val)
	{
		++dist;
		val &= val - 1;
	}

	return static_cast<uint8>(dist);
}

void adcensus_util::MedianFilter(const float32 *in, float32 *out, const sint32 &width, const sint32 &height, const sint32 wnd_size)
{
	const sint32 radius = wnd_size / 2;
	const sint32 size = wnd_size * wnd_size;

	std::vector<float32> wnd_data;
	wnd_data.reserve(size);

	for (sint32 y = 0; y < height; y++)
	{
		for (sint32 x = 0; x < width; x++)
		{
			wnd_data.clear();
			for (sint32 r = -radius; r <= radius; r++)
			{
				for (sint32 c = -radius; c <= radius; c++)
				{
					const sint32 row = y + r;
					const sint32 col = x + c;
					if (row >= 0 && row < height && col >= 0 && col < width)
					{
						wnd_data.push_back(in[row * width + col]);
					}
				}
			}
			std::sort(wnd_data.begin(), wnd_data.end());
			if (!wnd_data.empty())
			{
				out[y * width + x] = wnd_data[wnd_data.size() / 2];
			}
		}
	}
}