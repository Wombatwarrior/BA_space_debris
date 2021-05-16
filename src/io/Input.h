//
// Created by Oliver on 13.05.21.
//

#pragma once
#include <string>
#include <fstream>
#include "../debris/DebrisContainer.h"
class Input{
public:
    enum Type {TXT};
    Input(Debris::DebrisContainer &debris_arg)
            : debris (debris_arg)
    {}
    virtual ~Input();

    void readDebrisData();
private:
    Debris::DebrisContainer &debris;
    std::string file_name;
    Type input_file_type;

    void readDebrisTXT();

public:
    Debris::DebrisContainer &getDebris() ;
    void setDebris(Debris::DebrisContainer &debris);
    const std::string &getFileName() ;
    void setFileName(const std::string &fileName);
    Type getInputFileType() ;
    void setInputFileType(Type inputFileType);
};