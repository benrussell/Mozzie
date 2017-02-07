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


#ifndef XP_MOZZIE_LIBRARY_H
#define XP_MOZZIE_LIBRARY_H

#include <string>
#include <vector>

#include <mosquittopp.h>
#include <XPLMProcessing.h>


#include "XPDref.h"


class Mozzie : public mosqpp::mosquittopp{
private:
    std::vector<XPDref*> _datarefs;

    void _setup_published_datarefs();
    void _setup_subscribed_datarefs();


public:
    Mozzie( const std::string &id );
    ~Mozzie();


    // opens connection to server,
    bool open( const std::string &host, int port ); //TODO: connect() function doesn't want to overload - C++ syntax issue.
    void close();

    void on_connect( int rc );
    void on_message( const struct mosquitto_message *message );
    void on_subscribe( int mid, int quos_count, const int *granted_quos );



    void xp_data_pump(); //needs to be a public function because we call it using a deref'd pointer passed to flcb as arg


    static void debug( const std::string msg );

    static float flcb(
                    float                inElapsedSinceLastCall,
                    float                inElapsedTimeSinceLastFlightLoop,
                    int                  inCounter,
                    void *               inRefcon
                    );

    void ipc_msg(
            XPLMPluginID	inFromWho,
            int				inMessage,
            void *			inParam
    );


};





//FIXME: Probably easier to all/most of this with datarefs and commands?

enum Mozzie_IPC_Message_Types{

    // Connection Params
    e_Mozzie_Set_Client_ID,
    e_Mozzie_Set_Host,
    e_Mozzie_Set_Port,

    // Connection Control
    e_Mozzie_Connect,
    e_Mozzie_Disconnect,

    // Subscription Control
    e_Mozzie_Set_QOS,
    e_Mozzie_Subscribe,
    e_Mozzie_UnSubscribe,

    // Publication Control
    e_Mozzie_Publish,
    e_Mozzie_UnPublish,

    // Message Control
    e_Mozzie_Set_Topic,
    e_Mozzie_Set_Message,
    e_Mozzie_Send

};



#endif