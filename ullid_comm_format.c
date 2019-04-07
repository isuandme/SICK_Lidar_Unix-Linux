/*
 */

/*  */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/*  */
#include "ullid_comm_format.h"
#include "LMS1XX.h"

const char * type_arr[12] = {
    "<STX>",
    "<ETX>",
    "sRA",
    "sRN",
    "sWN",
    "sWA",
    "sAN",
    "sMN",
    "sEN",
    "sEA",
    "sSN",
    "{SPC}"
};

const char * comm_arr[41] = {
    "SetAccessMode",
    "mLMPsetscancfg",
    "LMPscancfg",
    "LMDscandatacfg",
    "LMPoutputRange",
    "LMDscandata",
    "LSPsetdatetime",
    "STlms",
    "mEEwriteall",
    "Run",
    "LFPparticle",
    "LFPmeanfilter",
    "LFPnto1filter",
    "FREchoFilter",
    "MSsuppmode",
    "LICsrc",
    "LICencset",
    "LICencres",
    "LICFixVel",
    "LICSpTh",
    "LICencsp",
    "LIDoutputstate",
    "mDOSetOutput",
    "DO6Fnc",
    "DO3And4Fnc",
    "LIDrstoutpcnt",
    "DeviceIdent",
    "SCdevicestate",
    "LocationName",
    "ODoprh",
    "ODpwrc",
    "EIIpAddr",
    "mSCloadfacdef",
    "mSCreboot",
    "LCMcfg",
    "SYPhase",
    "LMLfpFcn",
    "LMCstandby",
    "LMCstartmeas",
    "LMCstopmeas"
};

char * teleCommBuilder(enum TelegramComm tele_comm, ... ) {
    
    char * out_str = NULL;
    va_list args;
    
    switch (tele_comm) {
        case SetAccessMode:
            
            va_start(args, tele_comm);
            char * tmp = va_arg(args, char *);
            asprintf(&out_str,"%s",tmp);
            
            /*
            va_start(args, tele_comm);
            int8_t user_level = va_arg (args, int);
            uint32_t pass_word = va_arg (args, long);
            asprintf(&out_str,"%s %c%c %u",comm_arr[SetAccessMode],'0',user_level,pass_word);
             */
            
            break;
    case mLMPsetscancfg:
        break;
    case LMPscancfg:
        break;
    case LCMstate:
        break;
    case LMDscandatacfg:
        break;
    case LMPoutputRange:
        break;
    case LMDscandata:
        break;
    case LSPsetdatetime:
        break;
    case STlms:
        break;
    case mEEwriteall:
        break;
    case Run:
        break;
    case LFPparticle:
        break;
    case LFPmeanfilter:
        break;
    case LFPnto1filter:
        break;
    case FREchoFilter:
        break;
    case MSsuppmode:
        break;
    case LICsrc:
        break;
    case LICencset:
        break;
    case LICencres:
        break;
    case LICFixVel:
        break;
    case LICSpTh:
        break;
    case LICencsp:
        break;
    case LIDoutputstate:
        break;
    case mDOSetOutput:
        break;
    case DO6Fnc:
        break;
    case DO3And4Fnc:
        break;
    case LIDrstoutpcnt:
        break;
    case DeviceIdent:
        break;
    case SCdevicestate:
        break;
    case LocationName:
        break;
    case ODoprh:
        break;
    case ODpwrc:
        break;
    case EIIpAddr:
        break;
    case mSCloadfacdef:
        break;
    case mSCreboot:
        break;
    case LCMcfg:
        break;
    case SYPhase:
        break;
    case LMLfpFcn:
        break;
    case LMCstandby:
        break;
    case LMCstartmeas:
        break;
    case LMCstopmeas:
        break;
    default:
            logError("Uknown Comm type",__FILE__, __LINE__);
        break;
    }
    
    va_end(args);
    return out_str;
}


//1. Log in:                             sMN SetAccessMode


//2. Set Frequency and Resolution:       sMN mLMPsetscancfg


//3. Configure scan data content:        sWN LMDscandatacfg


//4. Configure scan data output:         sWN LMPoutputRange


//5. Store Parameters:                   sMN mEEwriteall


//6. Log out:                            sMN Run


//7. Request Scan:                       sRN LMDscandata / sEN LMDscandata



// This function takes a general telegram and gets the
// hex code for it.
char * telegramBuilder(enum TelegramType tele_type, enum TelegramComm comm_type, ... ) {
    
    char * out_str = NULL;
    va_list args;
    
    switch (tele_type) {
        case sRA:
            break;
        case sRN:
            break;
        case sWN:
            break;
        case sWA:
            break;
        case sAN:
            break;
        case sMN:
            va_start(args,comm_type);
            out_str = teleCommBuilder(comm_type, args);
            // TODO -->
            break;
        case sEN:
            break;
        case sEA:
            break;
        case sSN:
            break;
        default:
            break;
    }
    
    va_end(args);
    return out_str;
}

