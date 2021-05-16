//
// Created by Oliver on 13.05.21.
//

#pragma once
#include <fstream>
#include "../debris/DebrisContainer.h"
class FileOutput {
public:
    enum Type {TXT};
    FileOutput(Debris::DebrisContainer &debris_arg, std::string output_file_name_arg, Type output_file_type_arg)
    : debris (debris_arg), output_file_name(output_file_name_arg), output_file_type(output_file_type)
    {}
    virtual ~FileOutput();

    void writeDebrisData();
private:
    Debris::DebrisContainer &debris;
    std::string output_file_name;
    Type output_file_type;

    void writeDebrisTXT();

public:
    Debris::DebrisContainer &getDebris() ;
    void setDebris(Debris::DebrisContainer &debris);
    std::string &getOutputFileName() ;
    void setOutputFileName( std::string &outputFileName);
    Type getOutputFileType() ;
    void setOutputFileType(Type outputFileType);
};