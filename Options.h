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

#ifndef XP_MOZZIE_OPTIONS_H
#define XP_MOZZIE_OPTIONS_H

#include <string>
#include <map>

#include <vector>
#include <sstream>


class Options {
public:
    Options( const std::string filename );
    ~Options();

    std::string get( const std::string keyname );

private:

    std::vector<std::string> explode(std::string const & s, char delim);


    std::map<std::string, std::string> _map_keyvals;

    bool _destroy_raw_blob;
    std::string* _raw_blob;

};


#endif //XP_MOZZIE_OPTIONS_H
