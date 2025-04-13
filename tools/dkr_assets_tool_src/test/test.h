#pragma once

#include "misc/settings.hpp"

namespace DkrAssetsTool {
class TestDKRAT {
    public:
        TestDKRAT(DkrAssetsSettings &settings);
        ~TestDKRAT();
    private:
        DkrAssetsSettings &_settings;
};
}
