#include "Guid.h"
#include <assert.h>

namespace kit
{
	const Guid Guid::Null;

    std::string Base16::encode(const std::string & data, bool up_cast)
    {
        char const * hex_chr = up_cast ? "0123456789ABCDEF" : "0123456789abcdef";
        std::string hex;
        for (unsigned int i = 0; i < data.length(); i++)
        {
            unsigned char d = (unsigned char)data[i];
            hex.append(1, hex_chr[d >> 4]);
            hex.append(1, hex_chr[d & 0x0F]);
        }
        return hex;
    }

    std::string Base16::decode(const std::string & hex)
    {
        std::string data;
        if (hex.length() % 2)
        {
            assert(false);
            return "";
        }
        for (unsigned int i = 0; i < hex.length() / 2; i++)
        {
            char h = hex[i * 2];
            char l = hex[i * 2 + 1];
            if (h >= '0' && h <= '9')
                h -= '0';
            else if (h >= 'A' && h <= 'F')
                h -= ('A' - 10);
            else if (h >= 'a' && h <= 'f')
                h -= ('a' - 10);
            else 
            {
                assert(false);
                return "";
            }
            if (l >= '0' && l <= '9')
                l -= '0';
            else if (l >= 'A' && l <= 'F')
                l -= ('A' - 10);
            else if (l >= 'a' && l <= 'f')
                l -= ('a' - 10);
            else
            {
                assert(false);
                return "";
            }
            data.append(1, char((h << 4) + l));
        }
        return data;
    }

    std::string Guid::to_string() const
    {
		unsigned char bytes[16];
        memcpy(bytes, &guid_, sizeof(guid_));
        std::string guid = std::string((char const *)bytes, sizeof(GuidStruct));
        guid = Base16::encode(guid, true);
        return guid;
    }

    void Guid::from_string(std::string const & guid_str)
    {
        assert(guid_str.length() == 32);
        std::string guid = Base16::decode(guid_str);
        memcpy(&guid_, &guid[0], sizeof(GuidStruct));
    }

    void Guid::to_bytes(unsigned char * bytes) const
    {
		assert(sizeof(guid_) == 16);
        memcpy(bytes, &guid_, sizeof(guid_));
    }

    void Guid::from_bytes(unsigned char * bytes)
    {
		assert(sizeof(guid_) == 16);
        memcpy(&guid_, bytes, sizeof(guid_));
    }
}
