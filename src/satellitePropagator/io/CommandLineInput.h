//
// Created by Oliver on 16.05.21.
//

#pragma once
#include "FileInput.h"
#include "FileOutput.h"
#include <filesystem>
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
     * #input_file_path, #input_file_type, #output_file_path and
     * #output_file_type The file types are determined by the file extensions.
     *
     * @param argc Number of command line parameters
     * @param argv Pointer array holding the argument strings
     */
    void parseCommandLine(int argc, char** argv);

    InputFile::Type input_file_type = InputFile::TXT; /**< Holds the type of the input file*/
    OutputFile::Type output_file_type = OutputFile::CSV; /**< Holds the type of the output file*/
    std::filesystem::path input_file_path {}; /**< Path to the input file */
    std::filesystem::path output_file_path {}; /**< Path to the main output file. USed to construct other output file paths */
    bool run_thesis_calculations=false; /**< if set to true, we want to run pre defined simulations **/
public:
    /**
     * @brief Getter function for #input_file_type
     *
     * @return Value of #input_file_type
     */
    [[nodiscard]] InputFile::Type getInputFileType() const;

    /**
     * @brief Setter function for #input_file_type
     *
     * @param inputFileType New value of #input_file_type
     */
    void setInputFileType(InputFile::Type inputFileType);

    /**
     * @brief Getter function for #output_file_type
     *
     * @return Value of #output_file_type
     */
    [[nodiscard]] OutputFile::Type getOutputFileType() const;

    /**
     * @brief Setter function for #output_file_type
     *
     * @param outputFileType New value of #output_file_type
     */
    void setOutputFileType(OutputFile::Type outputFileType);

    /**
     * @brief Getter function for #input_file_path
     *
     * @return Value of #input_file_path
     */
    [[nodiscard]] const std::filesystem::path& getInputFilePath() const;
    std::filesystem::path& getInputFilePath();

    /**
     * @brief Setter function for #input_file_path
     *
     * @param inputFilePath New value of #input_file_path
     */
    void setInputFilePath(const std::filesystem::path& inputFilePath);

    /**
     * @brief Getter function for #output_file_path
     *
     * @return Value of #output_file_path
     */
    [[nodiscard]] const std::filesystem::path& getOutputFilePath() const;
    std::filesystem::path& getOutputFilePath();

    /**
     * @brief Setter function for #output_file_path
     *
     * @param outputFilePath New value of #output_file_path
     */
    void setOutputFilePath(const std::filesystem::path& outputFilePath);

    /**
     * @brief Getter function for #run_thesis_calculations
     *
     * @return value of #run_thesis_calculations
     */
     [[nodiscard]] const bool& getRunThesisCalculations() const;
};
