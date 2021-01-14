#pragma once



namespace std {
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
