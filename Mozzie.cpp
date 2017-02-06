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
#include <cstring>

// Heavily influenced by; http://wiki.neuromeka.net/index.php?title=Implementing_MQTT_Client_using_C%2B%2B_with_libmosquitto#MQTT_Wrapper


Mozzie::Mozzie( const std::string &id ) : mosquittopp( id.c_str() ){

    mosqpp::lib_init();

    // publish sim time
    //_datarefs.push_back( new XPDref("sim/time/total_running_time_sec") );
    _datarefs.push_back( new XPDref("sim/cockpit2/gauges/indicators/wind_speed_kts") );

    // publish compass heading, perhaps filter through on-change detection..
    //_datarefs.push_back( new XPDref("sim/cockpit2/gauges/indicators/compass_heading_deg_mag") );

    // slow moving dref, better for debug.
    _datarefs.push_back( new XPDref("sim/flightmodel/weight/m_fuel_total") );

}

Mozzie::~Mozzie() {

    Mozzie::debug("Mozzie destructor..\n");

}


bool Mozzie::open( const std::string &host, int port) {

    int keepalive = 120; //seconds

    connect( host.c_str(), port, keepalive ); // Connect to MQTT broker.

}


void Mozzie::close(){

    this->publish(
            NULL, //mid
            "sim/connected", //topic
            2, //payload length
            (void*)"0", //payload
            0, //qos
            0 //retain
    );

    this->loop();

    disconnect();

}



void Mozzie::on_connect(int rc) {

    char caDbg[1024];
    snprintf( caDbg, 1024, "Connected. Code: %d\n", rc );
    Mozzie::debug( caDbg );

    if( 0 == rc ){

        // Issue a connection notice over MQTT.
        this->publish(
                NULL, //mid
                "sim/connected", //topic
                2, //payload length
                (void*)"1", //payload
                0, //qos
                0 //retain
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

    // Iterate over a list of exported datarefs.
    for (std::vector<XPDref*>::iterator it = _datarefs.begin() ; it != _datarefs.end(); ++it){

        XPDref* dref = *it;

        // reads from x-plane and does compare with internal cache
        dref->update();

        // check to see if we need to update the MQTT server with a new value?
        if( dref->_send_it ){

#if 1
            //send as converted text
            char caTmp[16];
            snprintf( caTmp, 16, "%0.5f", dref->_val );
            size_t payload_size = strlen( caTmp );

            publish(
                    NULL, //mid - int
                    dref->_name.c_str(), //topic - char*
                    payload_size, //payload length - int
                    (void*)caTmp, //payload - void*
                    0, //qos - int: 0,1,2
                    false //retain - bool
            );
#else
            //send as binary
            publish(
                    NULL, //mid - int
                    dref->_name.c_str(), //topic - char*
                    4, //payload length - int
                    (void*)&dref->_val, //payload - void*
                    0, //qos - int: 0,1,2
                    true //retain - bool
            );
#endif

        } //send it?

    } //loop over all queued drefs

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

    tmp_mozzie->loop(); //mosquitto lib data pump

    tmp_mozzie->xp_data_pump(); //x-plane io data pump

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

