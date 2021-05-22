//
// Created by Oliver on 13.05.21.
//

#include "FileOutput.h"

FileOutput::~FileOutput() {

}

void FileOutput::writeDebrisData(double t) {
    switch (output_file_type) {
        case TXT:
            std::cout << "txt" << std::endl;
            writeDebrisTXT(t);
            break;
        case CSV:
            std::cout << "csv" << std::endl;
            writeDebrisCSV(t);
            break;
        default:
            std::cout << "default" << std::endl;

    }
}

void FileOutput::writeDebrisCSV(double t) {
    std::cout << "write time: " << t << std::endl;
    for (auto d : debris->getDebrisVector()){
        out << t << ',';
        IOUtils::array3DToCSV(out,d.getPosition());
        out << ',' << d.getHeight() << ',';
        IOUtils::array3DToCSV(out, d.getVelocity());
        out << ',' << d.getSpeed() << ',';
        IOUtils::array3DToCSV(out, d.getAccT0());
        out << ',' << d.getAccT0Norm() << ',';
        IOUtils::array3DToCSV(out, d.getAccT1());
        out << '\n';
    }
}

void FileOutput::writeDebrisTXT(double t) {

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
