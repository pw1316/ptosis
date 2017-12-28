#pragma once
#include <string>
#include <vector>

namespace pw {
    void filterExp1Point5(const std::vector<double>& in, std::vector<double>& out);
    void filterExp2Point5(const std::vector<double>& in, std::vector<double>& out);
    void filter(std::string fname);
}