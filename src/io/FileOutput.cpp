//
// Created by Oliver on 13.05.21.
//

#include "FileOutput.h"

FileOutput::FileOutput(Debris::DebrisContainer &debris_arg, std::string output_file_name_arg, FileOutput::Type output_file_type_arg)
: debris (&debris_arg), output_file_name(output_file_name_arg), output_file_type(output_file_type_arg), out(output_file_name_arg) {
    out << std::setprecision(std::numeric_limits<double>::digits10 + 1);
    if (output_file_type == CSV) {
        // column names
        out << "time,";
        out << "position x,";
        out << "position y,";
        out << "position z,";
        out << "position norm,";
        out << "velocity x,";
        out << "velocity y,";
        out << "velocity z,";
        out << "velocity norm,";
        out << "acc_t0 x,";
        out << "acc_t0 y,";
        out << "acc_t0 z,";
        out << "acc_t0 norm,";
        out << "acc_t0 x,";
        out << "acc_t0 y,";
        out << "acc_t0 z,";
        out << "acc_t0 norm\n";
    }
}



FileOutput::~FileOutput() {

}

void FileOutput::writeDebrisData(double t) {
    switch (output_file_type) {
        case TXT:
            writeDebrisTXT(t);
            break;
        case CSV:
            writeDebrisCSV(t);
            break;
        default:
            break;
    }
}

void FileOutput::writeDebrisCSV(double t) {
    for (auto d : debris->getDebrisVector()){
        out << t << ',';
        IOUtils::to_ostream(d.getPosition(),out);
        out << ',' << d.getHeight() << ',';
        IOUtils::to_ostream(d.getVelocity(), out);
        out << ',' << d.getSpeed() << ',';
        IOUtils::to_ostream(d.getAccT0(), out);
        out << ',' << d.getAccT0Norm() << ',';
        IOUtils::to_ostream(d.getAccT1(), out);
        out << ',' << d.getAccT1Norm();
        out << '\n';
    }
}

void FileOutput::writeDebrisTXT(double t) {
    // NOT IMPLEMENTED YET
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
