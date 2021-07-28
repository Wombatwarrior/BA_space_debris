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
 * @enum Type
 *
 * @brief Enumerates the possible file types used for input
 */
namespace InputFile {
enum Type {
    TXT, /**< File with .txt extension. Lines are in the format
        "<token>=<value>" and lines starting with "#" are ignored. Debris
        data is represented in TLE format as block at the end of the file
        after the line "TLE"*/
};
}
/**
 * @class FileInput
 *
 * @brief Reads input data from a file
 */
template <class Container, class D>
class FileInput {
public:
    /**
     * @brief Creates new FileInput object and reads in data
     *
     * Constructor reads in the data from the given input file of the given
     * InputFileType and safes the result in the private member variables.
     *
     * @param container_arg Reference to the Debris:DebrisContainer object to add
     * Debris::Debris objects to
     * @param input_file_path_arg Complete name of the input file to read data
     * from
     * @param input_file_type_arg InputFileType of the input file
     */
    FileInput(Container& container_arg,
        std::filesystem::path input_file_path_arg,
        InputFile::Type input_file_type_arg)
        : container(&container_arg)
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
     * by calling a specialized function depending on the InputFileType
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
    static void setDebrisValues(D& d, const std::string& line);

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

    Debris::DebrisContainer<D>*
        container
        = nullptr; /**< Reference to a Debris::DebrisContainer object to add
             Debris::Debris objects read from the input file*/
    std::filesystem::path input_file_path {}; /**< Complete name of the input file containing
                                the file extension*/
    InputFile::Type input_file_type = InputFile::TXT; /**< InputFile::InputFileType of the input file*/
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
     * @brief Getter function for #container
     *
     * @return Value of #container
     */
    [[nodiscard]] const Debris::DebrisContainer<D>& getContainer() const;
    Debris::DebrisContainer<D>& getContainer();

    /**
     * @brief Setter function for #container
     *
     * @param container New value of #container
     */
    void setContainer(Debris::DebrisContainer<D>& container);

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
    [[nodiscard]] InputFile::Type getInputFileType() const;

    /**
     * @brief Setter function for #input_file_type
     *
     * @param inputFileType New value of #input_file_type
     */
    void setInputFileType(InputFile::Type inputFileType);

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

template <class Container, class D>
FileInput<Container, D>::~FileInput() = default;

template <class Container, class D>
void FileInput<Container, D>::readDebrisData()
{
    switch (input_file_type) {
    case InputFile::TXT:
        readDebrisTXT();
        break;
    }
}

template <class Container, class D>
struct FileInput<Container, D>::TxtLineContent FileInput<Container, D>::tokenizeLine(
    const std::string& line) {
    TxtLineContent l;
    auto split_pos = line.find('=');
    l.token = line.substr(0, split_pos);
    l.value = line.substr(split_pos + 1);
    return l;
}

template <class Container, class D>
void FileInput<Container, D>::setDebrisValues(D& d, const std::string& line)
{
    auto position_split_pos = line.find('|');
    auto velocity_split_pos = line.find('|', position_split_pos + 1);
    auto acc_split_pos = line.find('|', velocity_split_pos + 1);
    auto aom_split_pos = line.find('|', acc_split_pos + 1);
    auto bc_inv_split_pos = line.find('|', aom_split_pos + 1);
    std::string position_str = line.substr(0, position_split_pos);
    std::string velocity_str = line.substr(position_split_pos + 1, velocity_split_pos);
    std::string acc_t0_str = line.substr(velocity_split_pos + 1, acc_split_pos);
    std::string acc_t1_str = line.substr(acc_split_pos + 1, aom_split_pos);
    std::string aom_str = line.substr(aom_split_pos + 1, bc_inv_split_pos);
    std::string bc_inv_str = line.substr(bc_inv_split_pos + 1);
    std::array<double, 3> vec {};

    auto x_split_pos = position_str.find(',');
    auto y_split_pos = position_str.find(',', x_split_pos + 1);
    vec[0] = stod(position_str.substr(0, x_split_pos));
    vec[1] = stod(position_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(position_str.substr(y_split_pos + 1));
    d.setPosition(vec);

    x_split_pos = velocity_str.find(',');
    y_split_pos = velocity_str.find(',', x_split_pos + 1);
    vec[0] = stod(velocity_str.substr(0, x_split_pos));
    vec[1] = stod(velocity_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(velocity_str.substr(y_split_pos + 1));
    d.setVelocity(vec);

    x_split_pos = acc_t0_str.find(',');
    y_split_pos = acc_t0_str.find(',', x_split_pos + 1);
    vec[0] = stod(acc_t0_str.substr(0, x_split_pos));
    vec[1] = stod(acc_t0_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(acc_t0_str.substr(y_split_pos + 1));
    d.setAccT0(vec);

    x_split_pos = acc_t1_str.find(',');
    y_split_pos = acc_t1_str.find(',', x_split_pos + 1);
    vec[0] = stod(acc_t1_str.substr(0, x_split_pos));
    vec[1] = stod(acc_t1_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(acc_t1_str.substr(y_split_pos + 1));
    d.setAccT1(vec);

    d.setAom(stod(aom_str));

    d.setBcInv(stod(bc_inv_str));
}

template <class Container, class D>
void FileInput<Container, D>::setConfigValues(const std::string& line)
{
    std::stringstream ss(line);
    for (int i = 0; i < 8; ++i) {
        ss >> acc_config[i];
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }
}

template <class Container, class D>
void FileInput<Container, D>::readDebrisTXT()
{
    std::ifstream input_file(input_file_path);
    std::string line;
    struct TxtLineContent line_content;
    Debris::Debris d;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            if (line.empty() or line[0] == '#') {
                continue;
            }
            line_content = tokenizeLine(line);
            if (line_content.value.empty()) {
                // no value
                continue;
            }
            if (line_content.token == "delta_t") {
                delta_t = stod(line_content.value);
            } else if (line_content.token == "write_delta_t") {
                write_delta_t = stod(line_content.value);
            } else if (line_content.token == "start_t") {
                start_t = stod(line_content.value);
            } else if (line_content.token == "end_t") {
                end_t = stod(line_content.value);
            } else if (line_content.token == "acc_config") {
                setConfigValues(line_content.value);
            } else if (line_content.token == "debris") {
                setDebrisValues(d, line_content.value);
                container->addDebris(d);
            } else {
                // unknown token
            }
        }
    }
}

template <class Container, class D>
const Debris::DebrisContainer<D>& FileInput<Container, D>::getContainer() const
{
    return *container;
}

template <class Container, class D>
Debris::DebrisContainer<D>& FileInput<Container, D>::getContainer()
{
    return *container;
}

template <class Container, class D>
void FileInput<Container, D>::setContainer(Debris::DebrisContainer<D>& container)
{
    FileInput<Container, D>::container = &container;
}

template <class Container, class D>
const std::filesystem::path& FileInput<Container, D>::getInputFilePath() const
{
    return input_file_path;
}

template <class Container, class D>
std::filesystem::path& FileInput<Container, D>::getInputFilePath()
{
    return input_file_path;
}

template <class Container, class D>
void FileInput<Container, D>::setInputFilePath(const std::filesystem::path& inputFilePath)
{
    input_file_path = inputFilePath;
}

template <class Container, class D>
InputFile::Type FileInput<Container, D>::getInputFileType() const
{
    return input_file_type;
}

template <class Container, class D>
void FileInput<Container, D>::setInputFileType(InputFile::Type inputFileType)
{
    input_file_type = inputFileType;
}

template <class Container, class D>
double FileInput<Container, D>::getDeltaT() const
{
    return delta_t;
}

template <class Container, class D>
void FileInput<Container, D>::setDeltaT(double deltaT)
{
    delta_t = deltaT;
}

template <class Container, class D>
double FileInput<Container, D>::getWriteDeltaT() const
{
    return write_delta_t;
}

template <class Container, class D>
void FileInput<Container, D>::setWriteDeltaT(double writeDeltaT)
{
    write_delta_t = writeDeltaT;
}

template <class Container, class D>
double FileInput<Container, D>::getStartT() const
{
    return start_t;
}

template <class Container, class D>
void FileInput<Container, D>::setStartT(double startT)
{
    start_t = startT;
}

template <class Container, class D>
double FileInput<Container, D>::getEndT() const
{
    return end_t;
}

template <class Container, class D>
void FileInput<Container, D>::setEndT(double endT)
{
    end_t = endT;
}

template <class Container, class D>
const std::array<bool, 8>& FileInput<Container, D>::getAccConfig() const
{
    return acc_config;
}

template <class Container, class D>
std::array<bool, 8>& FileInput<Container, D>::getAccConfig()
{
    return acc_config;
}

template <class Container, class D>
void FileInput<Container, D>::setAccConfig(const std::array<bool, 8>& accConfig)
{
    acc_config = accConfig;
}
