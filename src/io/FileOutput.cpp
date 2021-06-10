//
// Created by Oliver on 13.05.21.
//

#include "FileOutput.h"
#include "physics/AccelerationAccumulator.h"

FileOutput::FileOutput(Debris::DebrisContainer& debris_arg,
    std::string output_file_name_arg,
    FileOutput::Type output_file_type_arg,
    std::array<bool, 8>& acc_config)
    : debris(&debris_arg)
    , output_file_name(output_file_name_arg)
    , output_file_type(output_file_type_arg)
    , out(output_file_name_arg)
    , acc_out(output_file_name_arg + "_acc.csv")
{
    out << std::setprecision(std::numeric_limits<double>::digits10 + 1);
    acc_out << std::setprecision(std::numeric_limits<double>::digits10 + 1);
    if (output_file_type == CSV) {
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
        out << "acc_t1 norm\n";

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
        acc_out << "acc_total x,acc_total y,acc_total z,acc_total norm\n";
    }
}

FileOutput::~FileOutput() { }

void FileOutput::writeDebrisData(double t)
{
    switch (output_file_type) {
    case TXT:
        writeDebrisTXT(t);
        break;
    case CSV:
        writeDebrisCSV(t);
        break;
    default:
        break;
    }
}

void FileOutput::writeDebrisCSV(double t)
{
    for (auto d : debris->getDebrisVector()) {
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

void FileOutput::writeDebrisTXT(double t)
{
    // NOT IMPLEMENTED YET
}

void FileOutput::writeAcc_start(double t)
{
    acc_out << acc_row_count++ << ',';
    acc_out << t << ',';
}

void FileOutput::writeAcc_value(std::array<double, 3>& acc_val)
{
    IOUtils::to_ostream(acc_val, acc_out);
    acc_out << "," << MathUtils::euclideanNorm(acc_val) << ",";
}

void FileOutput::writeAcc_end(std::array<double, 3>& acc_val)
{
    IOUtils::to_ostream(acc_val, acc_out);
    acc_out << "," << MathUtils::euclideanNorm(acc_val) << "\n";
}

Debris::DebrisContainer& FileOutput::getDebris()
{
    return *debris;
}

void FileOutput::setDebris(Debris::DebrisContainer& debris)
{
    FileOutput::debris = &debris;
}

std::string& FileOutput::getOutputFileName()
{
    return output_file_name;
}

void FileOutput::setOutputFileName(std::string& outputFileName)
{
    output_file_name = outputFileName;
}

FileOutput::Type FileOutput::getOutputFileType()
{
    return output_file_type;
}

void FileOutput::setOutputFileType(FileOutput::Type outputFileType)
{
    output_file_type = outputFileType;
}
