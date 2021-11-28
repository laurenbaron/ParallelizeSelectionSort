# Parallelizing Selection Sort
CISC 372-011: Swetha Sankar, Lauren Baron, Brendan Green


## Introduction 
We sought to parallelize selection sort with both OpenMP and OpenACC. We tested the efficiency of our parallelization by targeting multicore CPUs with both OpenMP and OpenACC. We also acclerated the OpenACC code with GPUs.

## Requirements
We used an NVC compiler for all of our timed runs
>> module load nvhpc/21.7

## Configuration

>> sbatch <Batch file name>
>> more slurm-<jobID>.out

## Troubleshooting
Make sure the nvhpc module is loaded before compiling the code

## Maintainers
Swetha Sankar, Lauren Baron, Brendan Green
