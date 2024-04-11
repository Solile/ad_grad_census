/* -*-c++-*- AD-Census - Copyright (C) 2020.
* Author	: Yingsong Li(Ethan Li) <ethan.li.whu@gmail.com>
*			  https://github.com/ethan-li-coding/AD-Census
* Describe	: header of adcensus_types
*/

#ifndef ADCENSUS_STEREO_TYPES_H_
#define ADCENSUS_STEREO_TYPES_H_

#include <cstdint>
#include <limits>
#include <vector>
using std::vector;
using std::pair;

#ifndef SAFE_DELETE
#define SAFE_DELETE(P) {if(P) delete[](P);(P)=nullptr;}
#endif

/** \brief 基础类型别名 */
typedef int8_t      sint8;      // 有符号8位整数    unsigned char
typedef uint8_t     uint8;      // 无符号8位整数    uint8_tsigned char
typedef int16_t     sint16;     // 有符号16位整数   int16_tshort int
typedef uint16_t    uint16;     // 无符号16位整数   unsigned short int
typedef int32_t     sint32;     // 有符号32位整数   int
typedef uint32_t    uint32;     // 无符号32位整数   unsigned int
typedef int64_t     sint64;     // 有符号64位整数   long int
typedef uint64_t    uint64;     // 无符号64位整数   unsigned long int
typedef float       float32;    // 单精度浮点
typedef double      float64;    // 双精度浮点

/** \brief float32无效值 */
constexpr auto Invalid_Float = std::numeric_limits<float32>::infinity();

constexpr auto Large_Float = 99999.0f;
constexpr auto Small_Float = -99999.0f;

/** \brief Census窗口尺寸类型 */
enum CensusSize {
	Census5x5 = 0,
	Census9x7
};
/** \brief ADCensus参数结构体 */
struct ADCensusOption
{
	sint32 min_disparity;
	sint32 max_disparity;
	sint32 lambda_ad;
	sint32 lambda_census;
	sint32 cross_L1;
	sint32 cross_L2;
	sint32 cross_t1;
	sint32 cross_t2;
	float32 so_p1;
	float32 so_p2;
	float32 so_tso;
	sint32 irv_ts;
	float32 irv_th;

	float32 lrcheck_thres;
	bool do_lr_check;
	bool do_filling;
	bool do_discontinuity_adjustment;

	ADCensusOption() : min_disparity(0), max_disparity(64),
		lambda_ad(10), lambda_census(30),
		cross_L1(34), cross_L2(17),
		cross_t1(20), cross_t2(6),
		so_p1(1.0f), so_p2(3.0f),
		so_tso(15), irv_ts(20), irv_th(0.4f),
		lrcheck_thres(1.0f),
		do_lr_check(true), do_filling(true), do_discontinuity_adjustment(false) {};
};

/**
* \brief 颜色结构体
*/
struct ADColor {
	uint8 r, g, b;
	ADColor() : r(0), g(0), b(0) {}
	ADColor(uint8 _b, uint8 _g, uint8 _r) {
		r = _r; g = _g; b = _b;
	}
};

struct PGradient
{
	sint16 x, y;
	PGradient() : x(0), y(0) {}
	PGradient(sint16 _x, sint16 _y) {
		x = _x; y = _y;
	}
};


#endif
