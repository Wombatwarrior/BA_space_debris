//
// Created by Oliver on 13.05.21.
//

#include "FileOutput.h"

FileOutput::~FileOutput() {

}

Debris::DebrisContainer &FileOutput::getDebris()  {
    return *debris;
}

void FileOutput::setDebris(Debris::DebrisContainer &debris) {
    FileOutput::debris = &debris;
}

 std::string &FileOutput::getOutputFileName()  {
    return output_file_name;
}

void FileOutput::setOutputFileName( std::string &outputFileName) {
    output_file_name = outputFileName;
}

FileOutput::Type FileOutput::getOutputFileType()  {
    return output_file_type;
}

void FileOutput::setOutputFileType(FileOutput::Type outputFileType) {
    output_file_type = outputFileType;
}
