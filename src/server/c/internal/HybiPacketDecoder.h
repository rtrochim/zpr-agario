#pragma once

#include "seasocks/Logger.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace seasocks {

class HybiPacketDecoder {
    Logger& _logger;
    const std::vector<uint8_t>& _buffer;
    size_t _messageStart;

public:
    HybiPacketDecoder(Logger& logger, const std::vector<uint8_t>& buffer);

    enum class Opcode : uint8_t {
        Cont = 0x0, // Deprecated in latest hybi spec, here anyway.
        Text = 0x1,
        Binary = 0x2,
        Close = 0x8,
        Ping = 0x9,
        Pong = 0xA,
    };

    enum class MessageState {
        NoMessage,
        TextMessage,
        BinaryMessage,
        Error,
        Ping,
        Pong,
        Close
    };
    MessageState decodeNextMessage(std::vector<uint8_t>& messageOut, bool& deflateNeeded);
    MessageState decodeNextMessage(std::vector<uint8_t>& messageOut) {
        bool ignore;
        return decodeNextMessage(messageOut, ignore);
    }

    size_t numBytesDecoded() const;
};

}
