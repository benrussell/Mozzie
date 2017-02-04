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


void XPDref::update(){

    _val = XPLMGetDataf( _dref );

    if( _last_val != _val ){
        // Data has changed, issue an update.
        std::string sMsg = "update:(" + _name + "):\n";
        Mozzie::debug( sMsg );

        _send_it = true;
        _last_val = _val;
    } //see if the value has changed

} //update(..)


//eof
