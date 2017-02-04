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

#include "XPCmd.h"

#include "Mozzie.h"


XPCmd::XPCmd( const std::string cmd_name, const std::string cmd_description, void* button_router ) {

    char caTmp[1024];
    snprintf(caTmp, 1024, " cmd:(%s)\n", cmd_name.c_str());
    Mozzie::debug(caTmp);

    _name = cmd_name;
    _xpcmd = XPLMCreateCommand(cmd_name.c_str(), cmd_description.c_str());

    XPLMRegisterCommandHandler(_xpcmd,              // in Command name
                               XPCmd::StaticXpCmdRouter,       // in Handler
                               1,                      // Receive input before plugin windows.
                               (void *) this
    );

} // Constructor..


void XPCmd::Begin() {
    XPLMCommandBegin( _xpcmd );
    _cmd_active = 1;
}


void XPCmd::Stop() {
    if( _cmd_active ) {
        XPLMCommandEnd( _xpcmd );
        _cmd_active = 0;
    }
}







int XPCmd::StaticXpCmdRouter(    XPLMCommandRef        inCommand,
                            XPLMCommandPhase     inPhase,
                            void *               inRefcon) {

    XPCmd *cmd = (XPCmd*)inRefcon;
    //GFMCPPro_Buttons *btn_router = (GFMCPPro_Buttons*)cmd->_button_router;

#if 1
    char caTmp[1024];
    snprintf( caTmp, 1024, "phase:%i cmdHandler: %s\n", inPhase, cmd->_name.c_str() );
    Mozzie::debug( caTmp );
#endif

    return cmd->_action_handler( inCommand, inPhase );

}



int XPCmd::_action_handler(XPLMCommandRef inCommand, XPLMCommandPhase inPhase) {
    //Hmmm.
}



//eof
