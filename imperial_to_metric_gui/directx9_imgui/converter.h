#pragma once



namespace std {
	static constexpr float millimeters_per_inch = 25.4f;
	static constexpr int inches_per_foot = 12;
	static constexpr int feet_per_yard = 3;
	static constexpr int yards_per_mile = 1760;
	static constexpr float miles_per_nautical_mile = 1.150779f;


	static constexpr int millimeters_per_centimeter = 10;
	static constexpr int centimeters_per_decimeter = 10;
	static constexpr int decimeters_per_meter = 10;
	static constexpr int meters_per_kilometer = 1000;


	static constexpr float sq_mm_per_sq_in = millimeters_per_inch * millimeters_per_inch;
	static constexpr int sq_in_per_sq_ft = inches_per_foot * inches_per_foot;
	static constexpr int sq_ft_per_sq_yd = feet_per_yard * feet_per_yard;
	static constexpr int sq_yd_per_sq_mi = yards_per_mile * yards_per_mile;

	static constexpr int sq_mm_per_sq_cm = 100;
	static constexpr int sq_cm_per_sq_m = 10000;
	static constexpr int sq_m_per_ha = 10000;
	static constexpr int sq_ha_per_sq_km = 100;


	static constexpr float cu_mm_per_cu_in = (millimeters_per_inch * millimeters_per_inch) * millimeters_per_inch;
	static constexpr int cu_in_per_cu_ft = (inches_per_foot * inches_per_foot) * inches_per_foot;

	static constexpr int cu_mm_per_cu_cm = 1000;
	static constexpr int cu_cm_per_cu_dec = 1000;
	static constexpr int cu_dec_per_cu_m = 1000;


	static constexpr float milL_per_floz = 29.5735f;
	static constexpr int floz_per_gill = 4;
	static constexpr float gill_per_cup = 2.02884f;
	static constexpr float cup_per_pint = 1.97157f;
	static constexpr int pint_per_quart = 2;
	static constexpr int quart_per_gallon = 4;

	static constexpr int milL_per_cl = 10;
	static constexpr int cl_per_decl = 10;
	static constexpr int decl_per_l = 10;
	static constexpr int l_per_kl = 1000;


	static constexpr float mg_per_oz = 28349.5f;
	static constexpr int oz_per_lbs = 16;

	static constexpr int mg_per_cng = 10;
	static constexpr int cng_per_decg = 10;
	static constexpr int decg_per_g = 10;
	static constexpr int g_per_kg = 1000;
	static constexpr int kg_per_t = 1000;
	static constexpr int t_per_gg = 1000;


	class converter {
	public:				
		static enum class conversion_types_length
		{
			inches = 0,
			feet = 1,
			yards = 2,
			miles = 3,
			nautical_miles = 4,

			millimeters = 5,

			centimeters = 6,
			decimeters = 7,
			meters = 8,
			kilometers = 9
		};

		static enum class conversion_types_area
		{
			inches = 0,
			feet = 1,
			yards = 2,
			miles = 3,

			millimeters = 4,

			centimeters = 5,
			meters = 6,
			hectares = 7,
			kilometers = 8
		};

		static enum class conversion_types_volume
		{
			inches = 0,
			feet = 1,

			millimeters = 2,

			centimeters = 3,
			decameters = 4,
			meters = 5
			
		};

		static enum class conversion_types_liquidvolume
		{
			fl_oz = 0,
			gill = 1,
			cup = 2,
			pint = 3,
			quart = 4,
			gallon = 5,

			milliliter = 6,

			centiliter = 7,
			deciliter = 8,
			liter = 9,
			kiloliter = 10

		};

		static enum class conversion_types_weight
		{
			ounce = 0,
			pound = 1,

			milligram = 2,

			
			centigram = 3,
			decigram = 4,
			gram = 5,
			kilogram = 6,
			tonne = 7,
			gigagram = 8
		};
		static double convert_length(double input, conversion_types_length type, conversion_types_length output);

		static double convert_area(double input, conversion_types_area type, conversion_types_area output);

		static double convert_volume(double input, conversion_types_volume type, conversion_types_volume output);

		static double convert_liquidvolume(double input, conversion_types_liquidvolume type, conversion_types_liquidvolume output);

		static double convert_weight(double input, conversion_types_weight type, conversion_types_weight output);
	};
}
