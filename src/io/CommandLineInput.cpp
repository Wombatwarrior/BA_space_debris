//
// Created by Oliver on 16.05.21.
//

#include "CommandLineInput.h"

CommandLineInput::CommandLineInput(int argc, char **argv) {
    parseCommandLine(argc, argv);
}

CommandLineInput::~CommandLineInput() {

}

void CommandLineInput::parseCommandLine(int argc, char **argv){
    if (argc > 1) {
        input_file_name = std::string(argv[1]);
        if (input_file_name.size() < 5){
            // too short to contain filename plus ".xyz" file extension
        } else{
            // check for input file extension
            std::string type_str=input_file_name.substr(input_file_name.size()-4, 4);
            if(type_str.compare(".txt")){
                input_file_type=FileInput::TXT;
            }else{
                // not supported file format
            }
        }
        try {
            for (int i = 2; i < argc; ++i) {
                std::string option = std::string(argv[i]);
                // Make sure we aren't at the end of argv
                if (i + 1 < argc) {
                    if (option == "-output_file_name" || option == "-o") {
                        if (output_file_name.size() < 5){
                            // too short to contain filename plus ".xyz" file extension
                        } else{
                            // check for output file extension
                            std::string type_str=output_file_name.substr(output_file_name.size()-4, 4);
                            if(type_str.compare(".txt")){
                                output_file_type=FileOutput::TXT;
                            }else{
                                // not supported file format
                            }
                        }
                    }  else {
                        // unknown option
                    }
                    // flags could be legal at the end of the argument
                } else if (i == argc - 1) {
                    // unknown option
                }
            }
        } catch (std::logic_error &e) {
            std::string error_message =
                    std::string("Error while parsing command line. please check your input.\n") + e.what();
            throw std::invalid_argument(error_message);
        }
    } else {
        std::string error_message = "Erroneous program call!\n ./debris_sim <input_file_name> [-o <output_file_name>]";
        throw std::invalid_argument(error_message);
    }
}

 std::string &CommandLineInput::getInputFileName()  {
    return input_file_name;
}

void CommandLineInput::setInputFileName( std::string &inputFileName) {
    input_file_name = inputFileName;
}

FileInput::Type CommandLineInput::getInputFileType()  {
    return input_file_type;
}

void CommandLineInput::setInputFileType(FileInput::Type inputFileType) {
    input_file_type = inputFileType;
}

 std::string &CommandLineInput::getOutputFileName()  {
    return output_file_name;
}

void CommandLineInput::setOutputFileName( std::string &outputFileName) {
    output_file_name = outputFileName;
}

FileOutput::Type CommandLineInput::getOutputFileType()  {
    return output_file_type;
}

void CommandLineInput::setOutputFileType(FileOutput::Type outputFileType) {
    output_file_type = outputFileType;
}
