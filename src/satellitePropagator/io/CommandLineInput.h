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
template <class D>
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

public:
    /**
     * @brief Getter function for #input_file_type
     *
     * @return Value of #input_file_type
     */
    [[nodiscard]] typename InputFile::Type getInputFileType() const;

    /**
     * @brief Setter function for #input_file_type
     *
     * @param inputFileType New value of #input_file_type
     */
    void setInputFileType(typename InputFile::Type inputFileType);

    /**
     * @brief Getter function for #output_file_type
     *
     * @return Value of #output_file_type
     */
    [[nodiscard]] typename OutputFile::Type getOutputFileType() const;

    /**
     * @brief Setter function for #output_file_type
     *
     * @param outputFileType New value of #output_file_type
     */
    void setOutputFileType(typename OutputFile::Type outputFileType);

    /**
     * @brief Getter function for #input_file_path
     *
     * @return Value of #input_file_path
     */
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
};

template <class D>
CommandLineInput<D>::CommandLineInput(int argc, char** argv)
{
    parseCommandLine(argc, argv);
}

template <class D>
CommandLineInput<D>::~CommandLineInput() = default;

template <class D>
void CommandLineInput<D>::parseCommandLine(int argc, char** argv)
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
                    } else {
                        // unknown option
                        std::string error_message = "unknown argument " + option;
                        throw std::invalid_argument(error_message);
                    }
                    // flags could be legal at the end of the argument
                } else if (i == argc - 1) {
                    // unknown option
                    std::string error_message = "unknown or incomplete argument " + option;
                    throw std::invalid_argument(error_message);
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

template <class D>
InputFile::Type CommandLineInput<D>::getInputFileType() const
{
    return input_file_type;
}

template <class D>
void CommandLineInput<D>::setInputFileType(InputFile::Type inputFileType)
{
    input_file_type = inputFileType;
}

template <class D>
OutputFile::Type CommandLineInput<D>::getOutputFileType() const
{
    return output_file_type;
}

template <class D>
void CommandLineInput<D>::setOutputFileType(OutputFile::Type outputFileType)
{
    output_file_type = outputFileType;
}

template <class D>
std::filesystem::path& CommandLineInput<D>::getInputFilePath()
{
    return input_file_path;
}

template <class D>
void CommandLineInput<D>::setInputFilePath(const std::filesystem::path& inputFilePath)
{
    input_file_path = inputFilePath;
}

template <class D>
const std::filesystem::path& CommandLineInput<D>::getOutputFilePath() const
{
    return output_file_path;
}

template <class D>
std::filesystem::path& CommandLineInput<D>::getOutputFilePath()
{
    return output_file_path;
}

template <class D>
void CommandLineInput<D>::setOutputFilePath(const std::filesystem::path& outputFilePath)
{
    output_file_path = outputFilePath;
}
