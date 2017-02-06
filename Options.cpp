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

#include "Options.h"
#include "Mozzie.h"

#include <regex>

#include <XPLMUtilities.h>
#include <sys/stat.h>

Options::Options( const std::string filename ){

    // Setup some sane default key values.
    _map_keyvals["client_name"] = "X-Plane/Mozzie";
    _map_keyvals["server_name"] = "localhost";
    _map_keyvals["server_port"] = "1883";



    // Read and parse...

    this->_destroy_raw_blob = false;

    FILE* fh = fopen( filename.c_str(), "rb" );
    if( fh ){

        size_t filesize=0;

        struct stat stat_info;
        int stat_ret = stat( filename.c_str(), &stat_info);

        if( -1 == stat_ret ) {
            //stat failed!

        }else {

            filesize = (size_t)stat_info.st_size;

        }

        char* blob = (char*)malloc( filesize );

        fread(
                blob,
                1,
                filesize,
                fh
            );

        this->_destroy_raw_blob = true;
        this->_raw_blob = new std::string( blob );

        free( blob );
        fclose( fh );


        // Parse the grud damn thing.

        std::vector<std::string> svLines = this->explode( *this->_raw_blob, '\n' );
        size_t line_count = svLines.size();
        for( size_t lx=0; lx < line_count; lx++ ){

            std::vector<std::string> svTokens = this->explode( svLines[lx], '=' );

            if( 2 == svTokens.size() ){
                std::string sKey = svTokens[0];
                std::string sVal = svTokens[1];

                sVal = std::regex_replace( sVal, std::regex("\r"), "" );
                sVal = std::regex_replace( sVal, std::regex("\n"), "" );

                this->_map_keyvals[ sKey ] = sVal;

                //detect and ignore comments
                if( '#' != sKey[0] ){
                    std::string sMsg = "  " + sKey + "=" + sVal + "\r\n";
                    Mozzie::debug( sMsg );
                } //if comment marker

            } //did the line split neatly into two items?

        } //loop over all the lines in the file

    }else{

        // No options file was located. Create a buffer, fill it with defaults, write it to disk.
        std::string sOptionsDefaults = "";

        sOptionsDefaults += "client_name=" + _map_keyvals["client_name"] + "\r\n";
        sOptionsDefaults += "server_name=" + _map_keyvals["server_name"] + "\r\n";
        sOptionsDefaults += "server_port=" + _map_keyvals["server_port"] + "\r\n";

        FILE* fh = fopen( filename.c_str(), "wb" );
        if( fh ){
            fwrite( sOptionsDefaults.c_str(), sOptionsDefaults.size(), 1, fh );
            fclose( fh );

            Mozzie::debug("Created default <XP>/mozzie_prefs.txt\r\n");

        }else{
            Mozzie::debug("ERROR: Could not create default <XP>/mozzie_prefs.txt\r\n");
        }


    }

}


Options::~Options(){
    if( this->_destroy_raw_blob ){
        delete( this->_raw_blob );
    }

}



std::string Options::get( const std::string keyname ){

    std::map<std::string, std::string>::iterator it;

    it = _map_keyvals.find( keyname );
    if( _map_keyvals.end() != it ){
        return it->second;

    } // find options key:value pair and return valure.


    return "";

}


std::vector<std::string> Options::explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}


//eof
