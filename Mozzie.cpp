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


#include "Mozzie.h"

#include <iostream>

#include <XPLMUtilities.h>

#include <mosquittopp.h>

// Heavily influenced by; http://wiki.neuromeka.net/index.php?title=Implementing_MQTT_Client_using_C%2B%2B_with_libmosquitto#MQTT_Wrapper


Mozzie::Mozzie( const std::string &id ) : mosquittopp( id.c_str() ){

    mosqpp::lib_init();

}

Mozzie::~Mozzie() {

    Mozzie::debug("Mozzie destructor..\n");

}


bool Mozzie::open( const std::string &host, int port) {

    int keepalive = 120; //seconds
    connect( host.c_str(), port, keepalive ); // Connect to MQTT broker.

}



void Mozzie::on_connect(int rc) {

    char caDbg[1024];
    snprintf( caDbg, 1024, "Connected. Code: %d\n", rc );
    Mozzie::debug( caDbg );

    if( 0 == rc ){

        subscribe(
                NULL, //mid
                "sim/time" //topic
                //qos - not supplied.
        );

    } //if we connected..


} //::on_connect()


void Mozzie::on_message(const struct mosquitto_message *message) {
    Mozzie::debug("::on_message..\n");

} //::on_message()


void Mozzie::on_subscribe(int mid, int quos_count, const int *granted_quos) {
    Mozzie::debug("Subscription succeeded.\n");

} //::on_subscribe()


void Mozzie::xp_data_pump() {

    Mozzie::debug("data_pump running..(todo)\n");

    // Iterate over a list of exported datarefs.


} //::data_pump()






// Static
void Mozzie::debug( const std::string msg ){

    std::string sOutput = "Mozzie: " + msg;

#if 1
    XPLMDebugString( sOutput.c_str() );
#else
    printf( "%s", sOutput.c_str() );
#endif

} //::debug()





// X-Plane flight loop that handles MQTT processing.
// Static
float Mozzie::flcb(float inElapsedSinceLastCall,
                  float inElapsedTimeSinceLastFlightLoop,
                  int inCounter,
                  void *inRefcon) {

    Mozzie* tmp_mozzie = reinterpret_cast<Mozzie*>(inRefcon);

    tmp_mozzie->xp_data_pump();

    tmp_mozzie->loop();


    return -1.f; // Every frame.

}





void Mozzie::ipc_msg(
        XPLMPluginID	inFromWho,
        int				inMessage,
        void *			inParam
        ){

    switch( inMessage ){

        // Connection Params
        case e_Mozzie_Set_Client_ID:
            break;

        case e_Mozzie_Set_Host:
            break;

        case e_Mozzie_Set_Port:
            break;


        // Connection Control
        case e_Mozzie_Connect:

            break;

        case e_Mozzie_Disconnect:
            this->disconnect();
            break;


        // Subscription Control
        case e_Mozzie_Set_QOS:
            break;

        case e_Mozzie_Subscribe:
            /*
            this->subscribe(
                    mid,
                    sub name,
                    qos
                    );
                    */
            break;

        case e_Mozzie_UnSubscribe:
            break;


        // Publication Control
        case e_Mozzie_Publish:
            break;

        case e_Mozzie_UnPublish:
            break;


        // Message Control
        case e_Mozzie_Set_Topic:
            break;

        case e_Mozzie_Set_Message:
            break;

        case e_Mozzie_Send:
            break;


        default:
            break;
    }

}



//eof

