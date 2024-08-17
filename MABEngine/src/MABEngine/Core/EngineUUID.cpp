#include "mabengine_pch.h"
#include "MABEngine/Core/EngineUUID.h"

namespace MABEngine {
	namespace Core {
		
        static std::random_device s_RandomDevice;
        static thread_local std::mt19937_64 s_Engine(s_RandomDevice());

        EngineUUID::EngineUUID()
		{
            generate();
		}
		
        EngineUUID::EngineUUID(const std::string& uuidStr)
		{
            fromString(uuidStr);
		}
		
        std::string EngineUUID::ToString() const
		{
            std::ostringstream oss;
            for (size_t i = 0; i < data.size(); ++i) {
                if (i == 4 || i == 6 || i == 8 || i == 10) {
                    oss << '-';
                }
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
            }
            return oss.str();
		}

		std::string EngineUUID::GenerateUUIDString()
		{
            std::uniform_int_distribution<int> dis(0, 15);
            std::uniform_int_distribution<int> dis2(8, 11);

            std::stringstream ss;
            ss << std::hex << std::setfill('0');

            for (int i = 0; i < 8; ++i) {
                ss << dis(s_Engine);
            }
            ss << "-";
            for (int i = 0; i < 4; ++i) {
                ss << dis(s_Engine);
            }
            ss << "-4"; // The 13th digit is '4'
            for (int i = 0; i < 3; ++i) {
                ss << dis(s_Engine);
            }
            ss << "-";
            ss << dis2(s_Engine); // The 17th digit is one of 8, 9, A, or B
            for (int i = 0; i < 3; ++i) {
                ss << dis(s_Engine);
            }
            ss << "-";
            for (int i = 0; i < 12; ++i) {
                ss << dis(s_Engine);
            }

            return ss.str();
		}

		void EngineUUID::generate()
		{
            std::uniform_int_distribution<uint32_t> dist(0, 255);

            for (auto& byte : data) {
                byte = static_cast<uint8_t>(dist(s_Engine));
            }

            // Set version (4) and variant (RFC4122) bits.
            data[6] = (data[6] & 0x0F) | 0x40; // Version 4 (randomly generated UUID)
            data[8] = (data[8] & 0x3F) | 0x80; // Variant (RFC4122)
		}

		void EngineUUID::fromString(const std::string& uuid_str)
        {
            MAB_CORE_ASSERT(uuid_str.length() != 36, "Invalid UUID string length");
            
            if (uuid_str.length() != 36) {
                throw std::invalid_argument("Invalid UUID string length");
            }

            // Validate hyphen positions
            if (uuid_str[8] != '-' || uuid_str[13] != '-' || uuid_str[18] != '-' || uuid_str[23] != '-') {
                MAB_CORE_ERROR("'{0}' is not correct format.", uuid_str);
                MAB_CORE_ASSERT(true, "Invalid UUID format. Hyphens are in incorrect positions.");
                throw std::invalid_argument("Invalid UUID format. Hyphens are in incorrect positions.");
            }

            size_t pos = 0;
            size_t data_index = 0;

            for (char ch : uuid_str) {
                if (ch == '-') {
                    continue; // Skip dashes
                }

                if (!std::isxdigit(ch)) {
                    MAB_CORE_ASSERT(true, "Invalid character in UUID string");
                    throw std::invalid_argument("Invalid character in UUID string");
                }

                if (pos % 2 == 0) {
                    data[data_index] = hexCharToInt(ch) << 4; // High nibble
                }
                else {
                    data[data_index] |= hexCharToInt(ch); // Low nibble
                    ++data_index;
                }

                ++pos;
            }
		}

		uint8_t EngineUUID::hexCharToInt(char ch)
		{
            if (ch >= '0' && ch <= '9') {
                return ch - '0';
            }
            if (ch >= 'a' && ch <= 'f') {
                return ch - 'a' + 10;
            }
            if (ch >= 'A' && ch <= 'F') {
                return ch - 'A' + 10;
            }

            MAB_CORE_ASSERT(true, "Invalid hex character");
            return '0';
		}
	}
}