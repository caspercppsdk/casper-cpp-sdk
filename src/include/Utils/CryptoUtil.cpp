#include "CryptoUtil.h"

#include <cryptopp/blake2.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

#include "Utils/StringUtil.h"

namespace Casper {
    CBytes CryptoUtil::hexDecode(std::string encoded) {
        CStringSource ss(encoded, true, new CHexDecoder);
        CBytes decoded((size_t) ss.MaxRetrievable());
        ss.Get(decoded, decoded.size());
        return decoded;
    }

    std::string CryptoUtil::hexEncode(CBytes decoded) {
        std::string encoded;

        CStringSource ss(decoded, decoded.size(), true,
                         new CHexEncoder(new CStringSink(encoded))  // HexEncoder
        );
        return encoded;
    }


    std::string CryptoUtil::timeToRFC3339(time_t time) {
        std::tm tm;
        localtime_r(&time, &tm);
        char buffer[32];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S%z", &tm);
        return std::string(buffer);
    }
}  // namespace Casper
