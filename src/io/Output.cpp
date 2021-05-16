//
// Created by Oliver on 13.05.21.
//

#include "Output.h"

Output::~Output() {

}

Debris::DebrisContainer &Output::getDebris()  {
    return debris;
}

void Output::setDebris(Debris::DebrisContainer &debris) {
    Output::debris = debris;
}

const std::string &Output::getFileName()  {
    return file_name;
}

void Output::setFileName(const std::string &fileName) {
    file_name = fileName;
}

Output::Type Output::getOutputFileType()  {
    return output_file_type;
}

void Output::setOutputFileType(Output::Type outputFileType) {
    output_file_type = outputFileType;
}
