#include <string>
using namespace std;

constexpr float millimeters_per_inch = 25.4f;
constexpr int inches_per_foot = 12;
constexpr int feet_per_yard = 3;
constexpr int yards_per_mile = 1760;
constexpr float miles_per_nautical_mile = 1.150779f;

constexpr int millimeters_per_centimeter = 10;
constexpr int centimeters_per_decimeter = 10;
constexpr int decimeters_per_meter = 10;
constexpr int meters_per_kilometer = 1000;


constexpr float sq_mm_per_sq_in = millimeters_per_inch * millimeters_per_inch;
constexpr int sq_in_per_sq_ft = inches_per_foot * inches_per_foot;
constexpr int sq_ft_per_sq_yd = feet_per_yard * feet_per_yard;
constexpr int sq_yd_per_sq_mi = yards_per_mile * yards_per_mile;

constexpr int sq_mm_per_sq_cm = 100;
constexpr int sq_cm_per_sq_m = 10000;
constexpr int sq_m_per_ha = 10000;
constexpr int sq_ha_per_sq_km = 100;


constexpr float cu_mm_per_cu_in = (millimeters_per_inch * millimeters_per_inch) * millimeters_per_inch;
constexpr int cu_in_per_cu_ft = (inches_per_foot * inches_per_foot) * inches_per_foot;

constexpr int cu_mm_per_cu_cm = 1000;
constexpr int cu_cm_per_cu_dec = 1000;
constexpr int cu_dec_per_cu_m = 1000;


constexpr float milL_per_floz = 29.5735f;
constexpr int floz_per_gill = 4;
constexpr float gill_per_cup = 2.02884f;
constexpr float cup_per_pint = 1.97157f;
constexpr int pint_per_quart = 2;
constexpr int quart_per_gallon = 4;

constexpr int milL_per_cl = 10;
constexpr int cl_per_decl = 10;
constexpr int decl_per_l = 10;
constexpr int l_per_kl = 1000;


constexpr float mg_per_oz = 28349.5f;
constexpr int oz_per_lbs = 16;

constexpr int mg_per_cng = 10;
constexpr int cng_per_decg = 10;
constexpr int decg_per_g = 10;
constexpr int g_per_kg = 1000;
constexpr int kg_per_t = 1000;
constexpr int t_per_gg = 1000;

#include "converter.h"
namespace std {
	double converter::convert_length(double input, converter::conversion_types_length input_type, conversion_types_length output_type) {
		if (input != 0) {
			//convert input to millimeters;
			switch (input_type) {
			case converter::conversion_types_length::millimeters:
				input = input;
				break;

			case converter::conversion_types_length::inches:
				input = input * millimeters_per_inch;
				break;

			case converter::conversion_types_length::feet:
				input = (input * inches_per_foot) * millimeters_per_inch;
				break;

			case converter::conversion_types_length::yards:
				input = ((input * feet_per_yard) * inches_per_foot) * millimeters_per_inch;
				break;

			case converter::conversion_types_length::miles:
				input = (((input * yards_per_mile) * feet_per_yard) * inches_per_foot) * millimeters_per_inch;
				break;

			case converter::conversion_types_length::nautical_miles:
				input = ((((input * miles_per_nautical_mile) * yards_per_mile) * feet_per_yard) * inches_per_foot) * millimeters_per_inch;
				break;

			case converter::conversion_types_length::centimeters:
				input = input * millimeters_per_centimeter;
				break;

			case converter::conversion_types_length::decimeters:
				input = (input * centimeters_per_decimeter) * millimeters_per_centimeter;
				break;

			case converter::conversion_types_length::meters:
				input = ((input * decimeters_per_meter) * centimeters_per_decimeter) * millimeters_per_centimeter;
				break;

			case converter::conversion_types_length::kilometers:
				input = (((input * meters_per_kilometer) * decimeters_per_meter) * centimeters_per_decimeter) * millimeters_per_centimeter;
				break;

			default:
				break;
			}

			switch (output_type) {
			case converter::conversion_types_length::millimeters:
				input = input;
				break;

			case converter::conversion_types_length::centimeters:
				input = input / millimeters_per_centimeter;
				break;

			case converter::conversion_types_length::decimeters:
				input = (input / millimeters_per_centimeter) / centimeters_per_decimeter;
				break;

			case converter::conversion_types_length::meters:
				input = ((input / millimeters_per_centimeter) / centimeters_per_decimeter) / decimeters_per_meter;
				break;

			case converter::conversion_types_length::kilometers:
				input = (((input / millimeters_per_centimeter) / centimeters_per_decimeter) / decimeters_per_meter) / meters_per_kilometer;
				break;

			case converter::conversion_types_length::inches:
				input = input / millimeters_per_inch;
				break;

			case converter::conversion_types_length::feet:
				input = (input / millimeters_per_inch) / inches_per_foot;
				break;

			case converter::conversion_types_length::yards:
				input = ((input / millimeters_per_inch) / inches_per_foot) / feet_per_yard;
				break;

			case converter::conversion_types_length::miles:
				input = (((input / millimeters_per_inch) / inches_per_foot) / feet_per_yard) / yards_per_mile;
				break;

			case converter::conversion_types_length::nautical_miles:
				input = ((((input / millimeters_per_inch) / inches_per_foot) / feet_per_yard) / yards_per_mile) / miles_per_nautical_mile;
				break;

			default:
				break;
			}
		}
		return input;
	}

	double converter::convert_area(double input, converter::conversion_types_area input_type, conversion_types_area output_type) {
		if (input != 0) {
			//convert input to millimeters;
			switch (input_type) {
			case converter::conversion_types_area::millimeters:
				input = input;
				break;

			case converter::conversion_types_area::inches:
				input = input * sq_mm_per_sq_in;
				break;

			case converter::conversion_types_area::feet:
				input = (input * sq_in_per_sq_ft) * sq_mm_per_sq_in;
				break;

			case converter::conversion_types_area::yards:
				input = ((input * sq_ft_per_sq_yd) * sq_in_per_sq_ft) * sq_mm_per_sq_in;
				break;

			case converter::conversion_types_area::miles:
				input = (((input * sq_yd_per_sq_mi) * sq_ft_per_sq_yd) * sq_in_per_sq_ft) * sq_mm_per_sq_in;
				break;


			case converter::conversion_types_area::centimeters:
				input = input * sq_mm_per_sq_cm;
				break;
			
			case converter::conversion_types_area::meters:
				input = (input * sq_cm_per_sq_m) * sq_mm_per_sq_cm;
				break;

			case converter::conversion_types_area::hectares:
				input = ((input * sq_m_per_ha) * sq_cm_per_sq_m) * sq_mm_per_sq_cm;
				break;


			case converter::conversion_types_area::kilometers:
				input = (((input * sq_ha_per_sq_km) * sq_m_per_ha) * sq_cm_per_sq_m) * sq_mm_per_sq_cm;
				break;

			default:
				break;
			}
			//input = input * input;
			//input = to_power<float>(input);
			switch (output_type) {
			case converter::conversion_types_area::millimeters:
				input = input;
				break;

			case converter::conversion_types_area::centimeters:
				input = input / sq_mm_per_sq_cm;
				break;			

			case converter::conversion_types_area::meters:
				input = ((input / sq_mm_per_sq_cm) / sq_cm_per_sq_m);
				break;

			case converter::conversion_types_area::hectares:
				input = ((input / sq_mm_per_sq_cm) / sq_cm_per_sq_m) / sq_m_per_ha;
				break;

			case converter::conversion_types_area::kilometers:
				input = (((input / sq_mm_per_sq_cm) / sq_cm_per_sq_m) / sq_m_per_ha) / sq_ha_per_sq_km;
				break;

			case converter::conversion_types_area::inches:
				input = input / sq_mm_per_sq_in;
				break;

			case converter::conversion_types_area::feet:
				input = (input / sq_mm_per_sq_in) / sq_in_per_sq_ft;
				break;

			case converter::conversion_types_area::yards:
				input = ((input / sq_mm_per_sq_in) / sq_in_per_sq_ft) / sq_ft_per_sq_yd;
				break;

			case converter::conversion_types_area::miles:
				input = (((input / sq_mm_per_sq_in) / sq_in_per_sq_ft) / sq_ft_per_sq_yd) / sq_yd_per_sq_mi;
				break;

			default:
				break;
			}
			
		}
		return input;
	}

	double converter::convert_volume(double input, converter::conversion_types_volume input_type, conversion_types_volume output_type) {
		if (input != 0) {
			//convert input to millimeters;
			switch (input_type) {
			case converter::conversion_types_volume::millimeters:
				input = input;
				break;

			case converter::conversion_types_volume::inches:
				input = input * cu_mm_per_cu_in;
				break;

			case converter::conversion_types_volume::feet:
				input = (input * cu_in_per_cu_ft) * cu_mm_per_cu_in;
				break;

			case converter::conversion_types_volume::centimeters:
				input = input * cu_mm_per_cu_cm;
				break;

			case converter::conversion_types_volume::decameters:
				input = (input * cu_cm_per_cu_dec) * cu_mm_per_cu_cm;
				break;

			case converter::conversion_types_volume::meters:
				input = ((input * cu_dec_per_cu_m) * cu_cm_per_cu_dec) * cu_mm_per_cu_cm;
				break;

			default:
				break;
			}
			//input = input * input;
			//input = to_power<float>(input);
			switch (output_type) {
			case converter::conversion_types_volume::millimeters:
				input = input;
				break;

			case converter::conversion_types_volume::centimeters:
				input = input / cu_mm_per_cu_cm;
				break;

			case converter::conversion_types_volume::decameters:
				input = (input / cu_mm_per_cu_cm) / cu_cm_per_cu_dec;
				break;

			case converter::conversion_types_volume::meters:
				input = ((input / cu_mm_per_cu_cm) / cu_cm_per_cu_dec) / cu_dec_per_cu_m;
				break;

			case converter::conversion_types_volume::inches:
				input = input / cu_mm_per_cu_in;
				break;

			case converter::conversion_types_volume::feet:
				input = (input / cu_mm_per_cu_in) / cu_in_per_cu_ft;
				break;

			default:
				break;
			}

		}
		return input;
	}

	double converter::convert_liquidvolume(double input, converter::conversion_types_liquidvolume input_type, conversion_types_liquidvolume output_type) {
		if (input != 0) {
			//convert input to millimeters;
			switch (input_type) {
			case converter::conversion_types_liquidvolume::milliliter:
				input = input;
				break;

			case converter::conversion_types_liquidvolume::fl_oz:
				input = input * milL_per_floz;
				break;

			case converter::conversion_types_liquidvolume::gill:
				input = (input * floz_per_gill) * milL_per_floz;
				break;

			case converter::conversion_types_liquidvolume::cup:
				input = ((input * gill_per_cup) * floz_per_gill) * milL_per_floz;
				break;

			case converter::conversion_types_liquidvolume::pint:
				input = (((input * cup_per_pint) * gill_per_cup) * floz_per_gill) * milL_per_floz;
				break;

			case converter::conversion_types_liquidvolume::quart:
				input = ((((input * pint_per_quart) * cup_per_pint) * gill_per_cup) * floz_per_gill) * milL_per_floz;
				break;

			case converter::conversion_types_liquidvolume::gallon:
				input = (((((input * quart_per_gallon) * pint_per_quart) * cup_per_pint) * gill_per_cup) * floz_per_gill) * milL_per_floz;
				break;

			case converter::conversion_types_liquidvolume::centiliter:
				input = input * milL_per_cl;
				break;

			case converter::conversion_types_liquidvolume::deciliter:
				input = (input * cl_per_decl) * milL_per_cl;
				break;

			case converter::conversion_types_liquidvolume::liter:
				input = ((input * decl_per_l) * cl_per_decl) * milL_per_cl;
				break;

			case converter::conversion_types_liquidvolume::kiloliter:
				input = (((input * l_per_kl) * decl_per_l) * cl_per_decl) * milL_per_cl;
				break;

			default:
				break;
			}
			
			switch (output_type) {
			case converter::conversion_types_liquidvolume::milliliter:
				input = input;
				break;

			case converter::conversion_types_liquidvolume::fl_oz:
				input = input / milL_per_floz;
				break;

			case converter::conversion_types_liquidvolume::gill:
				input = (input / milL_per_floz) / floz_per_gill;
				break;

			case converter::conversion_types_liquidvolume::cup:
				input = ((input / milL_per_floz) * floz_per_gill) / gill_per_cup;
				break;

			case converter::conversion_types_liquidvolume::pint:
				input = (((input / milL_per_floz) * floz_per_gill) / gill_per_cup) / cup_per_pint;
				break;

			case converter::conversion_types_liquidvolume::quart:
				input = ((((input / milL_per_floz) * floz_per_gill) / gill_per_cup) / cup_per_pint) / pint_per_quart;
				break;

			case converter::conversion_types_liquidvolume::gallon:
				input = (((((input / milL_per_floz) * floz_per_gill) / gill_per_cup) / cup_per_pint) / pint_per_quart) / quart_per_gallon;
				break;

			case converter::conversion_types_liquidvolume::centiliter:
				input = input / milL_per_cl;
				break;

			case converter::conversion_types_liquidvolume::deciliter:
				input = (input / milL_per_cl) / cl_per_decl;
				break;

			case converter::conversion_types_liquidvolume::liter:
				input = ((input / milL_per_cl) / cl_per_decl) / decl_per_l;
				break;

			case converter::conversion_types_liquidvolume::kiloliter:
				input = (((input / milL_per_cl) / cl_per_decl) / decl_per_l) / l_per_kl;
				break;
			default:
				break;
			}

		}
		return input;
	}
	
	double converter::convert_weight(double input, converter::conversion_types_weight input_type, conversion_types_weight output_type) {
		if (input != 0) {
			//convert input to millimeters;
			switch (input_type) {
			case converter::conversion_types_weight::milligram:
				input = input;
				break;

			case converter::conversion_types_weight::ounce:
				input = input * mg_per_oz;
				break;

			case converter::conversion_types_weight::pound:
				input = (input * oz_per_lbs) * mg_per_oz;
				break;			

			case converter::conversion_types_weight::centigram:
				input = input * mg_per_cng;
				break;

			case converter::conversion_types_weight::decigram:
				input = (input * cng_per_decg) * mg_per_cng;
				break;

			case converter::conversion_types_weight::gram:
				input = ((input * decg_per_g) * cng_per_decg) * mg_per_cng;
				break;

			case converter::conversion_types_weight::kilogram:
				input = (((input * g_per_kg) * decg_per_g) * cng_per_decg) * mg_per_cng;
				break;

			case converter::conversion_types_weight::tonne:
				input = ((((input * kg_per_t) * g_per_kg) * decg_per_g) * cng_per_decg) * mg_per_cng;
				break;

			case converter::conversion_types_weight::gigagram:
				input = (((((input * t_per_gg) * kg_per_t) * g_per_kg) * decg_per_g) * cng_per_decg) * mg_per_cng;
				break;

			default:
				break;
			}

			switch (output_type) {
			case converter::conversion_types_weight::milligram:
				input = input;
				break;

			case converter::conversion_types_weight::ounce:
				input = input / mg_per_oz;
				break;

			case converter::conversion_types_weight::pound:
				input = (input / mg_per_oz) / oz_per_lbs;
				break;

			case converter::conversion_types_weight::centigram:
				input = input / mg_per_cng;
				break;

			case converter::conversion_types_weight::decigram:
				input = (input / mg_per_cng) / cng_per_decg;
				break;

			case converter::conversion_types_weight::gram:
				input = ((input / mg_per_cng) / cng_per_decg) / decg_per_g;
				break;

			case converter::conversion_types_weight::kilogram:
				input = (((input / mg_per_cng) / cng_per_decg) / decg_per_g) / g_per_kg;
				break;

			case converter::conversion_types_weight::tonne:
				input = ((((input / mg_per_cng) / cng_per_decg) / decg_per_g) / g_per_kg) / kg_per_t;
				break;

			case converter::conversion_types_weight::gigagram:
				input = (((((input / mg_per_cng) / cng_per_decg) / decg_per_g) / g_per_kg) / kg_per_t) / t_per_gg;
				break;
			default:
				break;
			}

		}
		return input;
	}
};