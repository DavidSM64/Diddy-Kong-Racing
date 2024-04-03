#pragma once

#include "misc/settings.hpp"

class TestDKRAT {
    public:
        TestDKRAT(DkrAssetsSettings &settings);
        ~TestDKRAT();
    private:
        DkrAssetsSettings &_settings;
};