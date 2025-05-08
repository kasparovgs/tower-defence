#include <gtest/gtest.h>
#include "landscape.h"

TEST(LandscapeTests, changeStructuresFromCSV){
    Landscape landscape{};
    landscape.setMapSize(10);
    landscape.changeFieldFromCSV("/home/gkasp/oop2024/3/tests/configs/");
    EXPECT_NO_THROW(landscape.changeStructuresFromCSV("/home/gkasp/oop2024/3/tests/configs/"));
    landscape.changeStructuresFromCSV("/home/gkasp/oop2024/3/tests/configs/");
}