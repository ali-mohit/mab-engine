#pragma once

#include "MABEngine/Core/Base.h"

#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>

namespace MABEngine {
	namespace Core {

        class MABENGINE_API EngineUUID {
        public:
            EngineUUID();
            EngineUUID(const std::string& uuid_str);

            std::string ToString() const;
            static std::string GenerateUUIDString();

            bool operator==(const EngineUUID& other) const {
                return data == other.data;
            }

            const std::array<uint8_t, 16>& GetData() const {
                return data;
            }
        private:
            void generate();
            void fromString(const std::string& uuid_str);
            uint8_t hexCharToInt(char ch);
        private:
            std::array<uint8_t, 16> data;

        };

        inline std::ostream& operator<<(std::ostream& os, const EngineUUID& e)
        {
            return os << e.ToString();
        }
	}
}

namespace std {
    template <>
    struct hash<MABEngine::Core::EngineUUID> {
        std::size_t operator()(const MABEngine::Core::EngineUUID& uuid) const noexcept {
            // A simple hash function that combines all bytes of the UUID data
            const auto& data = uuid.GetData();
            std::size_t hashValue = 0;
            for (const auto& byte : data) {
                hashValue ^= std::hash<uint8_t>()(byte) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            }
            return hashValue;
        }
    };
}