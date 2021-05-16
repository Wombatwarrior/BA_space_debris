//
// Created by Oliver on 16.05.21.
//

#pragma once
#include <string>
#include "FileInput.h"
#include "FileOutput.h"

class CommandLineInput {
public:
    CommandLineInput(int argc, char **argv);
    virtual ~CommandLineInput();
private:
    void parseCommandLine(int argc, char **argv);
    std::string input_file_name="input";
    FileInput::Type input_file_type=FileInput::TXT;
    std::string output_file_name="output";
    FileOutput::Type output_file_type=FileOutput::TXT;
public:
    std::string &getInputFileName() ;
    void setInputFileName( std::string &inputFileName);
    FileInput::Type getInputFileType() ;
    void setInputFileType(FileInput::Type inputFileType);
    std::string &getOutputFileName() ;
    void setOutputFileName( std::string &outputFileName);
    FileOutput::Type getOutputFileType() ;
    void setOutputFileType(FileOutput::Type outputFileType);
};
