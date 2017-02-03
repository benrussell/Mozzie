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
    virtual ~GFCommand(){};

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
