#include "seasocks/util/Json.h"

#include <iomanip>

namespace seasocks {

void jsonToStream(std::ostream& str, const char* t) {
    str << '"';
    for (; *t; ++t) {
        switch (*t) {
            default:
                if (static_cast<unsigned char>(*t) >= 32) {
                    str << *t;
                } else {
                    str << "\\u" << std::setw(4)
                        << std::setfill('0') << std::hex << static_cast<int>(*t);
                }
                break;
            case 8:
                str << "\\b";
                break;
            case 9:
                str << "\\t";
                break;
            case 10:
                str << "\\n";
                break;
            case 12:
                str << "\\f";
                break;
            case 13:
                str << "\\r";
                break;
            case '"':
            case '\\':
                str << '\\';
                str << *t;
                break;
        }
    }
    str << '"';
}

void jsonToStream(std::ostream& str, bool b) {
    str << (b ? "true" : "false");
}

void EpochTimeAsLocal::jsonToStream(std::ostream& o) const {
    o << "new Date(" << t * 1000 << ").toLocaleString()";
}

}
