#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <dynarr/dynarr.hpp>

TEST_CASE("dynarr ctor") {
  DynArr arr_def;
  CHECK_EQ(arr_def.size(), 0);

  const int size = 5;
  DynArr arr_s(size);
  CHECK_EQ(arr_s.size(), size);

  CHECK_THROWS(void(DynArr(0)));
  CHECK_THROWS(void(DynArr(-size)));
}

TEST_CASE("dynarr op[]") {
  const int size = 5;
  DynArr arr(size);
  CHECK_EQ(arr[0], 0);
  CHECK_EQ(arr[arr.size() - 1], 0);
  CHECK_THROWS(arr[-1]);
  CHECK_THROWS(arr[arr.size()]);
}
