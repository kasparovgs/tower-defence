#include <gtest/gtest.h>
#include "landscape.h"

TEST(LandscapeTests, changeStructuresFromCSV){
    Landscape landscape{};
    landscape.setMapSize(10);
    landscape.changeFieldFromCSV("tests/configs/");
    EXPECT_NO_THROW(landscape.changeStructuresFromCSV("tests/configs/"));
    landscape.changeStructuresFromCSV("tests/configs/");
}