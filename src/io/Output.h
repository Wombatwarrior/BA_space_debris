//
// Created by ubuntu on 13.05.21.
//

#pragma once
#include <fstream>
#include "../debris/DebrisContainer.h"
class Output {
public:
    enum Type {TXT};
    Output(Debris::DebrisContainer &debris_arg)
    : debris (debris_arg)
    {}
    virtual ~Output();

    void writeDebrisData();
private:
    Debris::DebrisContainer &debris;
    std::string file_name;
    Type output_file_type;

    void writeDebrisTXT();

public:
    Debris::DebrisContainer &getDebris() ;
    void setDebris(Debris::DebrisContainer &debris);
    const std::string &getFileName() ;
    void setFileName(const std::string &fileName);
    Type getOutputFileType() ;
    void setOutputFileType(Type outputFileType);
};