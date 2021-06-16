//
// Created by Oliver on 16.05.21.
//

#pragma once
#include "FileInput.h"
#include "FileOutput.h"
#include <string>

/**
 * @class CommandLineInput
 *
 * @brief Parses input/output files from command line arguments
 */
class CommandLineInput {
public:
    /**
     * @brief Constructor taking in argc and argv parameters similar to the main
     * function
     * @param argc Number of command line parameters
     * @param argv Pointer array holding the argument strings
     */
    CommandLineInput(int argc, char** argv);

    /**
     * @brief Default destructor
     *
     * Destroys the CommandLineInput object
     */
    virtual ~CommandLineInput();

private:
    /**
     * @brief The internal parsing function
     *
     * Parses the command line arguments ans sets the private member variables
     * #input_file_name, #input_file_type, #output_file_name and
     * #output_file_type The file types are determined by the file extensions.
     * The tile name still contain the extension.
     *
     *
     * @param argc Number of command line parameters
     * @param argv Pointer array holding the argument strings
     */
    void parseCommandLine(int argc, char** argv);

    std::string input_file_name = "input"; /**< Holds the complete file name of the input file*/
    FileInput::Type input_file_type = FileInput::TXT; /**< Holds the type of the input file*/
    std::string output_file_name = "output"; /**< Holds the complete file name of the output file*/
    FileOutput::Type output_file_type = FileOutput::TXT; /**< Holds the type of the output file*/
public:
    /**
     * @brief Getter function for #input_file_name
     *
     * @return Value of #input_file_name
     */
    std::string& getInputFileName();

    /**
     * @brief Setter function for #input_file_name
     *
     * @param inputFileName New value of #input_file_name
     */
    void setInputFileName(std::string& inputFileName);

    /**
     * @brief Getter function for #input_file_type
     *
     * @return Value of #input_file_type
     */
    FileInput::Type getInputFileType();

    /**
     * @brief Setter function for #input_file_type
     *
     * @param inputFileType New value of #input_file_type
     */
    void setInputFileType(FileInput::Type inputFileType);

    /**
     * @brief Getter function for #output_file_name
     *
     * @return Value of #output_file_name
     */
    std::string& getOutputFileName();

    /**
     * @brief Setter function for #output_file_name
     *
     * @param outputFileName New value of #output_file_name
     */
    void setOutputFileName(std::string& outputFileName);

    /**
     * @brief Getter function for #output_file_type
     *
     * @return Value of #output_file_type
     */
    FileOutput::Type getOutputFileType();

    /**
     * @brief Setter function for #output_file_type
     *
     * @param outputFileType New value of #output_file_type
     */
    void setOutputFileType(FileOutput::Type outputFileType);
};
