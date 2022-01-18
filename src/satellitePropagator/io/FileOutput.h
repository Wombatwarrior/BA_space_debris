//
// Created by Oliver on 13.05.21.
//

#pragma once
#include <filesystem>
#include <fstream>
#include <iomanip>

#include "satellitePropagator/debris/DebrisContainer.h"
#include "satellitePropagator/physics/AccelerationComponents/AccelerationComponents.h"

/**
* @enum OutputFileType
*
* @brief Enumerates the possible file types used for output
*/
namespace OutputFile {
enum Type {
    TXT, /**< File with .txt extension. Lines are in the format
    "<token>=<value>" and lines starting with "#" are ignored*/
    CSV /**< output data into a .csv file */
};
}

/**
 * @class FileOutput
 *
 * @brief Writes output data to a file
 */
template <class Container>
class FileOutput {
public:
    /**
     * @brief Creates new FileOutput object
     *
     * Constructor sets #container, #output_file_path amd #output_file_type private
     * member variables.
     *
     * @param container_arg Reference to the Debris:DebrisContainer object to take
     * Debris::Debris objects data from
     * @param output_file_path_arg Path to the main output file to write data
     * to
     * @param output_file_type_arg OutputFileType of the output file
     * @param acc_config Configuration vector for acceleration output
     */
    FileOutput(Container& container_arg,
        std::filesystem::path output_file_path_arg,
        OutputFile::Type output_file_type_arg,
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
     * by calling a specialized function depending on the OutputFileType
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

    Container*
        container; /**< Reference to a Debris::DebrisContainer object to add
             Debris::Debris objects read from the input file*/
    std::filesystem::path output_file_path; /**< Path to the main output file*/
    OutputFile::Type output_file_type = OutputFile::CSV; /**< OutputFileType of the output file*/
    std::ofstream out; /**< output file stream*/
    double row_count = 0; /**< keeps track of the row number for indexing the lines */
    std::filesystem::path acc_output_file_path; /**< Path to the acceleration output file*/
    std::ofstream acc_out; /**< output file stream for output of single acceleration components*/
    double acc_row_count = 0; /**< keeps track of the row number for indexing the lines of the acceleration data*/
public:
    /**
     * @brief Getter function for #container
     *
     * @return Value of #container
     */
    const Container& getContainer() const;
    Container& getContainer();

    /**
     * @brief Setter function for #container
     *
     * @param container New value of #container
     */
    void setContainer(Container& container);

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
    OutputFile::Type getOutputFileType() const;

    /**
     * @brief Setter function for #output_file_type
     *
     * @param outputFileType Value of #output_file_type
     */
    void setOutputFileType(OutputFile::Type outputFileType);

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

template <class Container>
FileOutput<Container>::FileOutput(Container& container_arg,
    std::filesystem::path output_file_path_arg,
    OutputFile::Type output_file_type_arg,
    std::array<bool, 8>& acc_config)
    : container(&container_arg)
    , output_file_path(output_file_path_arg)
    , output_file_type(output_file_type_arg)
    , out(output_file_path)
    , acc_output_file_path(output_file_path_arg.replace_extension().concat("_acc.csv"))
    , acc_out(acc_output_file_path)
{
    out << std::setprecision(std::numeric_limits<double>::digits10 + 1);
    acc_out << std::setprecision(std::numeric_limits<double>::digits10 + 1);
    if (output_file_type == OutputFile::CSV) {
        // row counter starts at 0
        row_count = 0;
        acc_row_count = 0;
        // column names
        out << "index,";
        out << "time,";
        out << "position x,";
        out << "position y,";
        out << "position z,";
        out << "position norm,";
        out << "velocity x,";
        out << "velocity y,";
        out << "velocity z,";
        out << "velocity norm,";
        out << "acc_t0 x,";
        out << "acc_t0 y,";
        out << "acc_t0 z,";
        out << "acc_t0 norm,";
        out << "acc_t1 x,";
        out << "acc_t1 y,";
        out << "acc_t1 z,";
        out << "acc_t1 norm" << std::endl;

        // column names for the accelerations
        acc_out << "index,";
        acc_out << "time,";
        if (acc_config[Acceleration::KEP]) {
            acc_out << "acc_kep x,acc_kep y,acc_kep z,acc_kep norm,";
        }
        if (acc_config[Acceleration::J2]) {
            acc_out << "acc_j2 x,acc_j2 y,acc_j2 z,acc_j2 norm,";
        }
        if (acc_config[Acceleration::C22]) {
            acc_out << "acc_c22 x,acc_c22 y,acc_c22 z,acc_c22 norm,";
        }
        if (acc_config[Acceleration::S22]) {
            acc_out << "acc_s22 x,acc_s22 y,acc_s22 z,acc_s22 norm,";
        }
        if (acc_config[Acceleration::SOL]) {
            acc_out << "acc_sol x,acc_sol y,acc_sol z,acc_sol norm,";
        }
        if (acc_config[Acceleration::LUN]) {
            acc_out << "acc_lun x,acc_lun y,acc_lun z,acc_lun norm,";
        }
        if (acc_config[Acceleration::SRP]) {
            acc_out << "acc_srp x,acc_srp y,acc_srp z,acc_srp norm,";
        }
        if (acc_config[Acceleration::DRAG]) {
            acc_out << "acc_drag x,acc_drag y,acc_drag z,acc_drag norm,";
        }
        acc_out << "acc_total x,acc_total y,acc_total z,acc_total norm" << std::endl;
    }
}

template <class Container>
FileOutput<Container>::~FileOutput() = default;

template <class Container>
void FileOutput<Container>::writeDebrisData(double t)
{
    switch (output_file_type) {
    case OutputFile::TXT:
        writeDebrisTXT(t);
        break;
    case OutputFile::CSV:
        writeDebrisCSV(t);
        break;
    default:
        break;
    }
}

template <class Container>
void FileOutput<Container>::writeDebrisCSV(double t)
{
    for (auto d : container->getDebrisVector()) {
        out << row_count++ << ',';
        out << t << ',';
        IOUtils::to_ostream(d.getPosition(), out);
        out << ',' << d.getHeight() << ',';
        IOUtils::to_ostream(d.getVelocity(), out);
        out << ',' << d.getSpeed() << ',';
        IOUtils::to_ostream(d.getAccT0(), out);
        out << ',' << d.getAccT0Norm() << ',';
        IOUtils::to_ostream(d.getAccT1(), out);
        out << ',' << d.getAccT1Norm();
        out << '\n';
    }
}

template <class Container>
void FileOutput<Container>::writeDebrisTXT(double)
{
    // NOT IMPLEMENTED YET
}

template <class Container>
void FileOutput<Container>::writeAcc_start(double t)
{
    acc_out << acc_row_count++ << ',';
    acc_out << t << ',';
}

template <class Container>
void FileOutput<Container>::writeAcc_value(const std::array<double, 3>& vec)
{
    IOUtils::to_ostream(vec, acc_out);
    acc_out << "," << MathUtils::euclideanNorm(vec) << ",";
}

template <class Container>
void FileOutput<Container>::writeAcc_end(const std::array<double, 3>& vec)
{
    IOUtils::to_ostream(vec, acc_out);
    acc_out << "," << MathUtils::euclideanNorm(vec) << "\n";
}

template <class Container>
const Container& FileOutput<Container>::getContainer() const
{
    return *container;
}

template <class Container>
Container& FileOutput<Container>::getContainer()
{
    return *container;
}

template <class Container>
void FileOutput<Container>::setContainer(Container& container)
{
    FileOutput<Container>::container = &container;
}

template <class Container>
const std::filesystem::path& FileOutput<Container>::getOutputFilePath() const
{
    return output_file_path;
}

template <class Container>
std::filesystem::path& FileOutput<Container>::getOutputFilePath()
{
    return output_file_path;
}

template <class Container>
void FileOutput<Container>::setOutputFilePath(const std::filesystem::path& outputFilePath)
{
    output_file_path = outputFilePath;
}

template <class Container>
OutputFile::Type FileOutput<Container>::getOutputFileType() const
{
    return output_file_type;
}

template <class Container>
void FileOutput<Container>::setOutputFileType(OutputFile::Type outputFileType)
{
    output_file_type = outputFileType;
}

template <class Container>
const std::filesystem::path& FileOutput<Container>::getAccOutputFilePath() const
{
    return acc_output_file_path;
}

template <class Container>
std::filesystem::path& FileOutput<Container>::getAccOutputFilePath()
{
    return acc_output_file_path;
}

template <class Container>
void FileOutput<Container>::setAccOutputFilePath(const std::filesystem::path& accOutputFilePath)
{
    acc_output_file_path = accOutputFilePath;
}
