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
#SBATCH --time=00:05:00
module load slurm_setup
module load amplifier_xe
source ${AMPLIFIER_XE_BASE}/apsvars.sh
rm -rf ../result
mkdir ../result
:: aps --result-dir=./../result ./debris_sim ../test_files/test_input.txt -o ./test_files/test.csv
amplxe-cl -collect hotspots -result-dir ./../result -quiet ./debris_sim ../test_files/test_input.txt -o ./test_files/test.csv
