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

#ifndef MOZZIE_XPDREF_H
#define MOZZIE_XPDREF_H

#include <string>

#include <XPLMDataAccess.h>

class XPDref {
private:
    XPLMDataRef _dref;

    // Used for delta-filtering to cut down on MQTT traffic.
    float _last_val;


public:
    XPDref( const std::string& name );

    std::string _name;

    float _val;

    bool _send_it;
    bool _valid;


    void update();

};


#endif //MOZZIE_XPDREF_H
