#!/bin/bash
#SBATCH -J BA_runtime_analysis
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
module load llvm/10.0.0
module unload intel-mpi/2019-intel
module unload intel
module switch gcc/10.2.0
./debris_sim ../test_files/test_input.txt -c