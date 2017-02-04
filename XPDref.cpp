/*

Mozzie - An MQTT plugin for the X-Plane flight simulator.
Copyright (C) 2017  Ben Russell - br@x-plugins.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


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
