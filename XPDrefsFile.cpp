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

#include <sys/stat.h>
#include "XPDrefsFile.h"

#include "Mozzie.h"


XPDrefsFile::XPDrefsFile( const std::string &filename ) {

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

        this->_raw_blob = new std::string( blob );

        free( blob );
        fclose( fh );


        // Parse the grud damn thing.

        std::vector<std::string> svLines = this->explode( *this->_raw_blob, '\n' );
        size_t line_count = svLines.size();
        for( size_t lx=0; lx < line_count; lx++ ){

            std::vector<std::string> svTokens = this->explode( svLines[lx], '\t' );

            // There are a bunch of useless data points in the file.
            // We only want the name and the data type.
            if( svTokens.size() >= 2 ){
                std::string sKey = svTokens[0];
                std::string sVal = svTokens[1];

                dref_details tmp_dref;
                tmp_dref.name = svTokens[0];
                tmp_dref.type = svTokens[1];

                svDatarefNames.push_back( tmp_dref );

                std::string sMsg = "  dref:(" + sKey + ")(" + sVal + ")\r\n";
                Mozzie::debug( sMsg );

            } //did the line split neatly into two items?

        } //loop over all the lines in the file


        delete( this->_raw_blob );

    }else{

        std::string sMsg = "Could not open file: " + filename + "\r\n";
        Mozzie::debug( sMsg );

    }

} //constructor







std::vector<std::string> XPDrefsFile::explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}