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

#ifndef XP_MOZZIE_MAIN_H
#define XP_MOZZIE_MAIN_H


#include <XPLMDataAccess.h>

#include <XPLMPlugin.h>
#include <XPLMProcessing.h>

#include <XPLMUtilities.h>



PLUGIN_API int XPluginStart(
        char *		outName,
        char *		outSig,
        char *		outDesc);

PLUGIN_API void XPluginStop();


PLUGIN_API int XPluginEnable(void);

PLUGIN_API int XPluginDisable(void);


PLUGIN_API void XPluginReceiveMessage(
        XPLMPluginID	inFromWho,
        int				inMessage,
        void *			inParam);




#endif //XP_MOZZIE_MAIN_H
