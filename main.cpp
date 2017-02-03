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
// Created by br on 28/01/17.
//

#include <cstdio>
#include "main.h"

#include "Mozzie.h"
Mozzie* mozzie;

#include "Options.h"


PLUGIN_API int XPluginStart(
        char *		outName,
        char *		outSig,
        char *		outDesc){

    snprintf( outName, 256, "Mozzie v17.02.03.2236" );
    snprintf( outSig, 256, "github.com/benrussell/Mozzie" );
    snprintf( outDesc, 256, "MQTT Client" );

    XPLMDebugString("Mozzie - An MQTT client for X-Plane.\n"); //FIXME: use details for above to build this.

    return 1;

}

PLUGIN_API void XPluginStop(){

}


PLUGIN_API int XPluginEnable(void){

    // FIXME: Figure out full path to options file.
    Options opt = Options("Mozzie_prefs.txt");
    mozzie = new Mozzie( opt.get("client_name").c_str() );



    // FIXME: Figure out full path to options file.
    //Options opt = Options("Mozzie_prefs.txt");
    std::string sMQTTServer = opt.get("server_name");
    std::string sMQTTPort = opt.get("server_port");

    mozzie->open( sMQTTServer, atoi( sMQTTPort.c_str() ) );

    XPLMRegisterFlightLoopCallback( Mozzie::flcb, -1.f, mozzie );

    Mozzie::debug("Enabled.");

    return 1;

}

PLUGIN_API int XPluginDisable(void){

    delete( mozzie );

    Mozzie::debug("Disabled.");

    return 1;

}


PLUGIN_API void XPluginReceiveMessage(
        XPLMPluginID	inFromWho,
        int				inMessage,
        void *			inParam){

    // Ignore all messages from X-Plane.
    if( XPLM_PLUGIN_XPLANE != inFromWho ){

        mozzie->ipc_msg( inFromWho, inMessage, inParam );

    }

}






//eof

