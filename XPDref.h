//
// Created by br on 4/02/17.
//

#ifndef MOZZIE_XPDREF_H
#define MOZZIE_XPDREF_H

#include <string>

#include <XPLMDataAccess.h>

class XPDref {
public:
    XPDref( const std::string& name );

    XPLMDataRef _dref;

    std::string _name;

    bool _valid;


    // Used for delta-filtering to cut down on MQTT traffic.
    float _last_val;

    float getFloat();


};


#endif //MOZZIE_XPDREF_H
