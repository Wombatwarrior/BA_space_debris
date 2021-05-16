//
// Created by Oliver on 13.05.21.
//

#pragma once
#include <string>
#include <fstream>
#include "../debris/DebrisContainer.h"
class FileInput{
public:
    enum Type {TXT};
    FileInput(Debris::DebrisContainer &debris_arg, std::string input_file_name_arg, Type input_file_type_arg)
    : debris (debris_arg), input_file_name(input_file_name_arg), input_file_type(input_file_type_arg)
    {
        readDebrisData();
    }
    virtual ~FileInput();

    void readDebrisData();
private:
    struct line_content {
        std::string token;
        std::string value;
    };

    struct line_content tokenize_line(const std::string &line);

    void setDebrisValues(Debris::Debris &d, const std::string &line);

    void setConfigValues(const std::string &line);

    void readDebrisTXT();

    Debris::DebrisContainer &debris;
    std::string input_file_name;
    Type input_file_type;
    double delta_t;
    double start_t;
    double end_t;
    std::array<bool,8> acc_config;

public:
    Debris::DebrisContainer &getDebris() ;
    void setDebris(Debris::DebrisContainer &debris);
    std::string &getInputFileName() ;
    void setInputFileName( std::string &inputFileName);
    Type getInputFileType() ;
    void setInputFileType(Type inputFileType);
    double getDeltaT() ;
    void setDeltaT(double deltaT);
    double getStartT() ;
    void setStartT(double startT);
    double getEndT() ;
    void setEndT(double endT);
    std::array<bool, 8> &getAccConfig() ;
    void setAccConfig( std::array<bool, 8> &accConfig);
};