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
