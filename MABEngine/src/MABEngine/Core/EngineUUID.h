#pragma once

#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>

namespace MABEngine {
	namespace Core {
        inline std::string generateUUID() {
            // Initialize a random number generator
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(0, 15);
            std::uniform_int_distribution<int> dis2(8, 11);

            std::stringstream ss;
            ss << std::hex << std::setfill('0');

            for (int i = 0; i < 8; ++i) {
                ss << dis(gen);
            }
            ss << "-";
            for (int i = 0; i < 4; ++i) {
                ss << dis(gen);
            }
            ss << "-4"; // The 13th digit is '4'
            for (int i = 0; i < 3; ++i) {
                ss << dis(gen);
            }
            ss << "-";
            ss << dis2(gen); // The 17th digit is one of 8, 9, A, or B
            for (int i = 0; i < 3; ++i) {
                ss << dis(gen);
            }
            ss << "-";
            for (int i = 0; i < 12; ++i) {
                ss << dis(gen);
            }

            return ss.str();
        }
	}
}