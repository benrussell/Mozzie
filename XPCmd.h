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

#ifndef MOZZIE_XPCMD_H
#define MOZZIE_XPCMD_H


#include <XPLMUtilities.h>
#include <string>


class XPCmd {
protected:
    int _cmd_active; //held high while the hardware button is down, returns to low when we get a release event from USB HID

    XPLMCommandRef _xpcmd;


public:
    XPCmd( const std::string cmd_name, const std::string cmd_description, void* _button_router );
    virtual ~XPCmd(){};

    std::string _name;

    int _is_multi_phase;

    //std::string _description;

    virtual void Begin();
    virtual void Stop();

    int _action_handler(    XPLMCommandRef        inCommand,
                            XPLMCommandPhase     inPhase);

    static int StaticXpCmdRouter(    XPLMCommandRef        inCommand,
                                           XPLMCommandPhase     inPhase,
                                           void *               inRefcon);

};


#endif //MOZZIE_XPCMD_H
