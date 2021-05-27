//
// Created by Oliver on 13.05.21.
//

#pragma once
#include <fstream>
#include <iomanip>
#include "../debris/DebrisContainer.h"
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
        TXT, /**< File with .txt extension. Lines are in the format "<token>=<value>" and lines starting with "#" are ignored*/
        CSV /**< output data into a .csv file */
    };

    /**
     * @brief Creates new FileOutput object
     *
     * Constructor sets #debris, #output_file_name amd #output_file_type private member variables.
     *
     * @param debris_arg Reference to the Debris:DebrisContainer object to take Debris::Debris objects data from
     * @param output_file_name_arg Complete name of the output file to write data to
     * @param output_file_type_arg FileOutput::Type of the output file
     */
    FileOutput(Debris::DebrisContainer &debris_arg, std::string output_file_name_arg, Type output_file_type_arg);

    /**
     * @brief Default destructor
     *
     * Destroys the FileOutput object
     */
    virtual ~FileOutput();

    /**
     * @brief Writes data to a file
     *
     * Writes the data to the file with the #output_file_name
     * by calling a specialized function depending on the FileOutput::Type #output_file_type
     */
    void writeDebrisData(double t);
private:
    /**
     * @brief NOT IMPLEMENTED Specialized function to write the data to a #TXT file
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

    Debris::DebrisContainer *debris;/**< Reference to a Debris::DebrisContainer object to add Debris::Debris objects read from the input file*/
    std::string output_file_name;/**< Complete name of the output file containing the file extension*/
    Type output_file_type;/**< FileOutput::Type of the output file*/
    std::ofstream out;/**< output file stream*/
public:

    /**
     * @brief Getter function for #debris
     *
     * @return Value of #debris
     */
    Debris::DebrisContainer &getDebris();

    /**
     * @brief Setter function for #debris
     *
     * @param debris New value of #debris
     */
     void setDebris(Debris::DebrisContainer &debris);

    /**
     * @brief Getter function for #output_file_name
     *
     * @return Value of #output_file_name
     */
    std::string &getOutputFileName();

    /**
     * @brief Setter function for #output_file_name
     *
     * @param outputFileName New value of #output_file_name
     */
    void setOutputFileName(std::string &outputFileName);

    /**
     * @brief Getter function for #output_file_type
     *
     * @return New value of #output_file_type
     */
    Type getOutputFileType();

    /**
     * @brief Setter function for #output_file_type
     *
     * @param outputFileType Value of #output_file_type
     */
    void setOutputFileType(Type outputFileType);
};