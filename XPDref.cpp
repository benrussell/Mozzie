//
// Created by br on 4/02/17.
//

#include "XPDref.h"
#include "Mozzie.h"


XPDref::XPDref(const std::string &name) {

    _dref = XPLMFindDataRef( name.c_str() );

    if( NULL == _dref ){
        _valid = false;

        std::string sMsg = "XPDref: 404: " + name + "\n";
        Mozzie::debug( sMsg );

    }else{
        _name = name;
        _valid = true;

    }

}


float XPDref::getFloat(){

    float val = XPLMGetDataf( _dref );

    if( _last_val != val ){
        // Data has changed, issue an update.
        Mozzie::debug("value changed; sending packet: <dref name>\n");

        _last_val = val;
    }

    return val;
}


//eof
