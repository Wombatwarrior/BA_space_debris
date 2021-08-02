//
// Created by Oliver on 13.05.21.
//

#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <utility>

#include "satellitePropagator/debris/DebrisContainer.h"

/**
 * @class FileInput
 *
 * @brief Reads input data from a file
 */
class FileInput {
public:
    /**
     * @enum Type
     *
     * @brief Enumerates the possible file types used for input
     */
    enum Type {
        TXT, /**< File with .txt extension. Lines are in the format
        "<token>=<value>" and lines starting with "#" are ignored. Debris
        data is represented in TLE format as block at the end of the file
        after the line "TLE"*/
    };

    /**
     * @brief Creates new FileInput object and reads in data
     *
     * Constructor reads in the data from the given input file of the given
     * FileInput::Type and safes the result in the private member variables.
     *
     * @param debris_arg Reference to the Debris:DebrisContainer object to add
     * Debris::Debris objects to
     * @param input_file_path_arg Complete name of the input file to read data
     * from
     * @param input_file_type_arg FileInput::Type of the input file
     */
    FileInput(Debris::DebrisContainer& debris_arg,
        std::filesystem::path input_file_path_arg,
        Type input_file_type_arg)
        : debris(&debris_arg)
        , input_file_path(std::move(input_file_path_arg))
        , input_file_type(input_file_type_arg)
    {
        readDebrisData();
    }

    /**
     * @brief Default destructor
     *
     * Destroys the FileInput object
     */
    virtual ~FileInput();

    /**
     * @brief Reads data from a file
     *
     * Reads the data from the file with the #input_file_path
     * by calling a specialized function depending on the FileInput::Type
     * #input_file_type
     */
    void readDebrisData();

private:
    /**
     * @struct TxtLineContent
     *
     * @brief Represents the content of a line of a #TXT file
     *
     * A line of a #TXT file has the format "<token>=<value>".
     * This struct is used to have simpler access to the two components separated
     * by the "="
     */
    struct TxtLineContent {
        std::string
            token; /**< represents the kind of data represented by the line*/
        std::string value; /**< holds the actual value of the data*/
    };

    /**
     * @brief Splits up a given line of a #TXT file
     *
     * Splits up a given line of a #TXT file into the
     * FileInput::TxtLineContent::token string and the
     * FileInput::TxtLineContent::value string and returns
     * FileInput::TxtLineContent struct holding the two strings
     *
     * @param line A string representing a line of a #TXT file
     * @return FileInput::TxtLineContent struct holding the result of splitting
     * up the line
     */
    static struct TxtLineContent tokenizeLine(const std::string& line);

    /**
     * @brief Sets the member variable of a given Debris::Debris object
     *
     * Sets the member variable of a given Debris::Debris object.
     * The values are given in a string of the format
     * "Debris::Debris::position|Debris::Debris::velocity|Debris::Debris::acc_t0|Debris::Debris::acc_t1"
     * Splits up the string and extracts the four 3D vectors representing the
     * state of a Debris::Debris object. Writes the extracted values into the
     * member variables of the given Debris::Debris object referenced by d
     *
     * @param d Reference to the Debris::Debris object to write the read values
     * to
     * @param line A string representing the state of a Debris::Debris object in
     * the format "position|velocity|acc_t0|acc_t1"
     */
    static void setDebrisValues(Debris::Debris& d, const std::string& line);

    /**
     * @brief Sets the configuration vector specifying the
     * Acceleration::AccelerationComponent to apply
     *
     * Sets the configuration vector specifying the
     * Acceleration::AccelerationComponent to apply based on a string
     * representation of a 8D bool vector encoding the
     * Acceleration::AccelerationComponent to apply in the simulation. The Order
     * of flags is
     * - #Acceleration::KEP
     * - #Acceleration::J2
     * - #Acceleration::C22
     * - #Acceleration::S22
     * - #Acceleration::SOL
     * - #Acceleration::LUN
     * - #Acceleration::SRP
     * - #Acceleration::DRAG
     *
     * The vector entry encoding is
     * - 0 = false
     * - 1 = true
     *
     *
     * @param line String representation of a 8D bool vector encoding the
     * Acceleration::AccelerationComponent to apply in the simulation. The Order
     * of flags is [KEP, J2, C22, S22, SOL, LUN, SRP, DRAG]
     */
    void setConfigValues(const std::string& line);

    /**
     * @brief Specialized function to read the data from a #TXT file
     */
    void readDebrisTXT();

    Debris::DebrisContainer*
        debris
        = nullptr; /**< Reference to a Debris::DebrisContainer object to add
             Debris::Debris objects read from the input file*/
    std::filesystem::path input_file_path {}; /**< Complete name of the input file containing
                                the file extension*/
    Type input_file_type = TXT; /**< InputFile::Type of the input file*/
    double delta_t = 0; /**< Time step to use in the simulation*/
    double start_t = 0; /**< Start time of the simulation*/
    double end_t = 0; /**< End time of the simulation*/
    double write_delta_t = 0; /**< Time interval to write output */
    /**
     * @brief 8D bool vector encoding the Acceleration::AccelerationComponent to
     * apply in the simulation.
     *
     * 8D bool vector encoding the Acceleration::AccelerationComponent to apply
     * in the simulation. The Order of flags is
     * - #Acceleration::KEP
     * - #Acceleration::J2
     * - #Acceleration::C22
     * - #Acceleration::S22
     * - #Acceleration::SOL
     * - #Acceleration::LUN
     * - #Acceleration::SRP
     * - #Acceleration::DRAG
     */
    std::array<bool, 8> acc_config {};

public:
    /**
     * @brief Getter function for #debris
     *
     * @return Value of #debris
     */
    [[nodiscard]] const Debris::DebrisContainer& getDebris() const;
    Debris::DebrisContainer& getDebris();

    /**
     * @brief Setter function for #debris
     *
     * @param debris New value of #debris
     */
    void setDebris(Debris::DebrisContainer& debris);

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
     * @brief Getter function for #input_file_type
     *
     * @return Value of #input_file_type
     */
    [[nodiscard]] Type getInputFileType() const;

    /**
     * @brief Setter function for #input_file_type
     *
     * @param inputFileType New value of #input_file_type
     */
    void setInputFileType(Type inputFileType);

    /**
     * @brief Getter function for #delta_t
     *
     * @return Value of #delta_t
     */
    [[nodiscard]] double getDeltaT() const;

    /**
     * @brief Setter function for #write_delta_t
     *
     * @param writeDeltaT New value of #write_delta_t
     */
    void setWriteDeltaT(double writeDeltaT);

    /**
     * @brief Getter function for #write_delta_t
     *
     * @return Value of #write_delta_t
     */
    [[nodiscard]] double getWriteDeltaT() const;

    /**
     * @brief Setter function for #delta_t
     *
     * @param deltaT New value of #delta_t
     */
    void setDeltaT(double deltaT);

    /**
     * @brief Getter function for #start_t
     *
     * @return Value of #start_t
     */
    [[nodiscard]] double getStartT() const;

    /**
     * @brief Setter function for #start_t
     *
     * @param startT New value of #start_t
     */
    void setStartT(double startT);

    /**
     * @brief Getter function for #end_t
     *
     * @return Value of #end_t
     */
    [[nodiscard]] double getEndT() const;

    /**
     * @brief Setter function for #end_t
     *
     * @param endT New value of #end_t
     */
    void setEndT(double endT);

    /**
     * @brief Getter function for #acc_config
     *
     * @return Value of #acc_config
     */
    [[nodiscard]] const std::array<bool, 8>& getAccConfig() const;
    std::array<bool, 8>& getAccConfig();

    /**
     * @brief Setter function for #acc_config
     *
     * @param accConfig New value of #acc_config
     */
    void setAccConfig(const std::array<bool, 8>& accConfig);
};