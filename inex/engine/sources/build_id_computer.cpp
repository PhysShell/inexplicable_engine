#include "stdafx.h"
#include "build_id_computer.h"
namespace inex {
namespace engine {
namespace build {

//constexpr pcstr get_build_date()
//{
//    return __DATE__;
//}
//
//
//constexpr u16 get_build_id  ()
//{
//    int					days{};
//	int					months = 0;
//	int					years{};
//    string16            month{};
//	sscanf				(get_build_date(),"%s%d%d",month,&days,&years);
//
//}

//void compute_build_id	()
//{
//    pcstr month_id[12]  = {
//        "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec"
//    };
//
//    u16 days_in_month[12] = {
//        31,28,31,30,31,30,31,31,30,31,30,31
//    };
//
//    u16 start_day	    = 7;	// 7
//    u16 start_month	    = 9;	// September
//    u16 start_year	    = 2017;	// 2017
//
//	build_date			= __DATE__;
//	u16					days;
//	u16					months = 0;
//	u16					years;
//	string16            month;
//	string256           buffer;
//	strcpy				(buffer,__DATE__);
//	sscanf				(buffer,"%s%hu%hu",month,&days,&years);
//
//	for (u8 i=0; i<12; i++) {
//		if (_stricmp(month_id[i],month))
//			continue;
//
//		months			= i;
//		break;
//	}
//
//	build_id			= (years - start_year)*365 + days - start_day;
//
//	for (int i=0; i<months; ++i)
//		build_id		+= days_in_month[i];
//
//	for (int i=0; i<start_month-1; ++i)
//		build_id		-= days_in_month[i];
//}
} // namespace build
} // namespace engine
} // namespace inex
