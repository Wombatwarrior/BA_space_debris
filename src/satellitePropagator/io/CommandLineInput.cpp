//
// Created by Oliver on 28.07.21.
//

#include "CommandLineInput.h"

CommandLineInput::CommandLineInput(int argc, char** argv)
{
    parseCommandLine(argc, argv);
}

CommandLineInput::~CommandLineInput() = default;

void CommandLineInput::parseCommandLine(int argc, char** argv)
{
    if (argc > 1) {
        input_file_path = std::filesystem::path(argv[1]);
        // check for input file extension
        std::string type_str = input_file_path.extension();
        if (type_str == ".txt") {
            input_file_type = InputFile::Type::TXT;
        } else {
            // not supported file format
            std::string error_message = type_str + " is no supported .xyz file extension for input";
            throw std::invalid_argument(error_message);
        }
        try {
            for (int i = 2; i < argc; ++i) {
                std::string option = std::string(argv[i]);
                // Make sure we aren't at the end of argv
                if (i + 1 < argc) {
                    if (option == "-output_file_name" || option == "-o") {
                        output_file_path = std::filesystem::path(argv[++i]);
                        // check for output file extension
                        type_str = output_file_path.extension();
                        if (type_str == ".txt") {
                            output_file_type = OutputFile::TXT;
                            // for now only csv files are supported
                            std::string error_message = " .txt output is not yet implemented. use "
                                                        ".csv";
                            throw std::invalid_argument(error_message);
                        } else if (type_str == ".csv") {
                            output_file_type = OutputFile::CSV;
                        } else {
                            // not supported file format
                            std::string error_message = type_str + " is no supported .xyz file extension "
                                                                   "for output";
                            throw std::invalid_argument(error_message);
                        }
                    } else if(option == "-c") {
                        run_thesis_calculations=true;
                    } else {
                        // unknown option
                        std::string error_message = "unknown argument " + option;
                        throw std::invalid_argument(error_message);
                    }
                // flags could be legal at the end of the argument
                } else if (i == argc - 1) {
                    if(option == "-c") {
                        run_thesis_calculations=true;
                    } else {
                        // unknown option
                        std::string error_message = "unknown or incomplete argument " + option;
                        throw std::invalid_argument(error_message);
                    }
                }
            }
        } catch (std::logic_error& e) {
            std::string error_message = std::string(
                                            "Error while parsing command line. please check "
                                            "your input.\n")
                + e.what();
            throw std::invalid_argument(error_message);
        }
    } else {
        std::string error_message = "Erroneous program call!\n ./debris_sim "
                                    "<input_file_name> [-o <output_file_name>]";
        throw std::invalid_argument(error_message);
    }
}

InputFile::Type CommandLineInput::getInputFileType() const
{
    return input_file_type;
}

void CommandLineInput::setInputFileType(InputFile::Type inputFileType)
{
    input_file_type = inputFileType;
}

OutputFile::Type CommandLineInput::getOutputFileType() const
{
    return output_file_type;
}

void CommandLineInput::setOutputFileType(OutputFile::Type outputFileType)
{
    output_file_type = outputFileType;
}

std::filesystem::path& CommandLineInput::getInputFilePath()
{
    return input_file_path;
}

void CommandLineInput::setInputFilePath(const std::filesystem::path& inputFilePath)
{
    input_file_path = inputFilePath;
}

const std::filesystem::path& CommandLineInput::getOutputFilePath() const
{
    return output_file_path;
}

std::filesystem::path& CommandLineInput::getOutputFilePath()
{
    return output_file_path;
}

void CommandLineInput::setOutputFilePath(const std::filesystem::path& outputFilePath)
{
    output_file_path = outputFilePath;
}

const std::filesystem::path &CommandLineInput::getInputFilePath() const {
    return input_file_path;
}

const bool &CommandLineInput::getRunThesisCalculations() const {
    return run_thesis_calculations;
}
