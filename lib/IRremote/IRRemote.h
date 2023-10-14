#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include "LedDisplay.h"

namespace IRControls
{
    static const uint32_t PLUS_A = 0x409F7A85;
    static const uint32_t SUB_A = 0x409FFA05;
    static const uint32_t PLUS_B = 0x409F728D;
    static const uint32_t SUB_B = 0x409FF20D;
}

class IRRemote
{
private:
    bool _debug = false;
    IRrecv* irrecv;
    decode_results results;
public:
    void set_debug(bool debug) { _debug = debug; }
    bool begin();
    void process();
};

extern IRRemote irRemote;