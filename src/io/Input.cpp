//
// Created by ubuntu on 13.05.21.
//

#include "Input.h"

Input::~Input() {

}

Debris::DebrisContainer &Input::getDebris()  {
    return debris;
}

void Input::setDebris(Debris::DebrisContainer &debris) {
    Input::debris = debris;
}

const std::string &Input::getFileName()  {
    return file_name;
}

void Input::setFileName(const std::string &fileName) {
    file_name = fileName;
}

Input::Type Input::getInputFileType()  {
    return input_file_type;
}

void Input::setInputFileType(Input::Type inputFileType) {
    input_file_type = inputFileType;
}
