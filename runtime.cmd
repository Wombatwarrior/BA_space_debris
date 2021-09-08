#!/bin/bash
#SBATCH -J BA_profile
#SBATCH -o ./../../output/%x.%j.%N.out
#SBATCH -D ./build
#SBATCH --clusters=serial
#SBATCH --partition=serial_std
#SBATCH --get-user-env
#SBATCH --mail-type=END
#SBATCH --cpus-per-task=1
#SBATCH --mail-user=oliver.boesing@tum.de
#SBATCH --export=NONE
#SBATCH --time=02:00:00
module load slurm_setup
module load amplifier_xe
module load llvm/10.0.0
module unload intel-mpi/2019-intel
module unload intel
module switch gcc/10.2.0
source ${AMPLIFIER_XE_BASE}/apsvars.sh
rm -rf ../result
mkdir ../result
:: aps --result-dir=./../result ./debris_sim ../test_files/test_input.txt -c
amplxe-cl -collect hotspots -result-dir ./../result -quiet ./debris_sim ../test_files/test_input.txt -c
