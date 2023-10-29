#include "IRRemote.h"

IRRemote irRemote;

using namespace IRControls;

bool IRRemote::begin()
{
    IRRemote::irrecv = new IRrecv(D4);
    IRRemote::irrecv->enableIRIn();
    return true;
}

void IRRemote::process()
{
    if (irrecv->decode(&results))
    {
        if (_debug) {
            Serial.println(results.value, HEX);
        }
        
        byte score;
        switch (results.value)
        {
        case PLUS_A:            
            if (_debug) { Serial.println("Chamou o PLUS_A"); }
            score = ledDisplay.get_ScoreTeamA() + 1;
            ledDisplay.set_ScoreTeamA(score);
            break;
        case SUB_A:
            if (_debug) { Serial.println("Chamou o SUB_A"); }
            score = ledDisplay.get_ScoreTeamA() - 1;
            ledDisplay.set_ScoreTeamA(score);
            break;
        case PLUS_B:
        if (_debug) { Serial.println("Chamou o PLUS_B"); }
            score = ledDisplay.get_ScoreTeamB() + 1;
            ledDisplay.set_ScoreTeamB(score);
            break;
        case SUB_B:
        if (_debug) { Serial.println("Chamou o SUB_A"); }
            score = ledDisplay.get_ScoreTeamB() - 1;
            ledDisplay.set_ScoreTeamB(score);
            break;
        default:
            break;
        }

        irrecv->resume();
    }
}