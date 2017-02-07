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
// Created by br on 7/02/17.
//

#ifndef MOZZIE_XPDREFSFILE_H
#define MOZZIE_XPDREFSFILE_H

#include <string>
#include <vector>
#include <regex>


// Parses a standard datarefs file.


struct dref_details{
    std::string name;
    std::string type;
};



class XPDrefsFile {
private:
    std::string* _raw_blob;

    std::vector<std::string> explode(std::string const & s, char delim);


public:
    XPDrefsFile( const std::string& filename );

    std::vector<dref_details> svDatarefNames;

};


#endif //MOZZIE_XPDREFSFILE_H
