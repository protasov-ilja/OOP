#include "stdafx.h"
#include <vector>



TEST_CASE("vectors can be sized and resized", "[vector]") {
	REQUIRE(v.size() == 5);
	REQUIRE(v.capacity() >= 5);

	SECTION("resizing bigger changes size and capacity") {
		v.resize(10);

		REQUIRE(v.size() == 10);
		REQUIRE(v.capacity() >= 10);
	}
}