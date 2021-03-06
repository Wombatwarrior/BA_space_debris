//
// Created by Oliver on 13.05.21.
//

#pragma once
#include <filesystem>
#include <fstream>
#include <iomanip>

#include "satellitePropagator/debris/DebrisContainer.h"
/**
 * @class FileOutput
 *
 * @brief Writes output data to a file
 */
class FileOutput {
public:
    /**
     * @enum Type
     *
     * @brief Enumerates the possible file types used for output
     */
    enum Type {
        TXT, /**< File with .txt extension. Lines are in the format
        "<token>=<value>" and lines starting with "#" are ignored*/
        CSV /**< output data into a .csv file */
    };

    /**
     * @brief Creates new FileOutput object
     *
     * Constructor sets #debris, #output_file_path amd #output_file_type private
     * member variables.
     *
     * @param debris_arg Reference to the Debris:DebrisContainer object to take
     * Debris::Debris objects data from
     * @param output_file_path_arg Path to the main output file to write data
     * to
     * @param output_file_type_arg FileOutput::Type of the output file
     * @param acc_config Configuration vector for acceleration output
     */
    FileOutput(Debris::DebrisContainer& debris_arg,
        std::filesystem::path output_file_path_arg,
        Type output_file_type_arg,
        std::array<bool, 8>& acc_config);

    /**
     * @brief Default destructor
     *
     * Destroys the FileOutput object
     */
    virtual ~FileOutput();

    /**
     * @brief Writes data to a file
     *
     * Writes the data to the file with the #output_file_path
     * by calling a specialized function depending on the FileOutput::Type
     * #output_file_type
     */
    void writeDebrisData(double t);

    /**
     * @brief Starts a new output line
     *
     * @param t Current time
     */
    void writeAcc_start(double t);

    /**
     * @brief Writes the content of a 3D Vector to the output file
     *
     * @param vec Reference to the 3D vector
     */
    void writeAcc_value(const std::array<double, 3>& vec);

    /**
     * @brief Writes the last 3D vector of a line to the output file
     *
     * @param vec Reference to the 3D vector
     */
    void writeAcc_end(const std::array<double, 3>& vec);

private:
    /**
     * @brief NOT IMPLEMENTED Specialized function to write the data to a #TXT
     * file
     *
     * @param t Current simulation time
     */
    void writeDebrisTXT(double t);

    /**
     * @brief Specialized function to write the data to a #CSV file
     *
     * Row structure:
     * time,position,||position||,velocity,||velocity||,acc_t0,||acc_t0||,acc_t1,||acc_t1||,
     *
     * @param t Current simulation time
     */
    void writeDebrisCSV(double t);

    Debris::DebrisContainer*
        debris; /**< Reference to a Debris::DebrisContainer object to add
             Debris::Debris objects read from the input file*/
    std::filesystem::path output_file_path; /**< Path to the main output file*/
    Type output_file_type = CSV; /**< FileOutput::Type of the output file*/
    std::ofstream out; /**< output file stream*/
    double row_count = 0; /**< keeps track of the row number for indexing the lines */
    std::filesystem::path acc_output_file_path; /**< Path to the acceleration output file*/
    std::ofstream acc_out; /**< output file stream for output of single acceleration components*/
    double acc_row_count = 0; /**< keeps track of the row number for indexing the lines of the acceleration data*/
public:
    /**
     * @brief Getter function for #debris
     *
     * @return Value of #debris
     */
    const Debris::DebrisContainer& getDebris() const;
    Debris::DebrisContainer& getDebris();

    /**
     * @brief Setter function for #debris
     *
     * @param debris New value of #debris
     */
    void setDebris(Debris::DebrisContainer& debris);

    /**
     * @brief Getter function for #output_file_path
     *
     * @return Value of #output_file_path
     */
    const std::filesystem::path& getOutputFilePath() const;
    std::filesystem::path& getOutputFilePath();

    /**
     * @brief Setter function for #output_file_path
     *
     * @param outputFilePath New value of #output_file_path
     */
    void setOutputFilePath(const std::filesystem::path& outputFilePath);

    /**
     * @brief Getter function for #output_file_type
     *
     * @return New value of #output_file_type
     */
    Type getOutputFileType() const;

    /**
     * @brief Setter function for #output_file_type
     *
     * @param outputFileType Value of #output_file_type
     */
    void setOutputFileType(Type outputFileType);

    /**
      * @brief Getter function for #acc_output_file_path
      *
      * @return Value of #acc_output_file_path
      */
    const std::filesystem::path& getAccOutputFilePath() const;
    std::filesystem::path& getAccOutputFilePath();

    /**
     * @brief Setter function for #acc_output_file_path
     *
     * @param accOutputFilePath New value of #acc_output_file_path
     */
    void setAccOutputFilePath(const std::filesystem::path& accOutputFilePath);
};