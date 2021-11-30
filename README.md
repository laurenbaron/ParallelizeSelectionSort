# Parallelizing Selection Sort
CISC 372-011: Swetha Sankar, Lauren Baron, Brendan Green


## Introduction 
We sought to parallelize selection sort with both OpenMP and OpenACC. We tested the efficiency of our parallelization by targeting multicore CPUs with both OpenMP and OpenACC. We also accelerated the OpenACC code with GPUs.

## Requirements
We used an NVC compiler for all of our timed runs
>> module load nvhpc/21.7

We use CUDA to use NVIDIA SMI
>> module load cuda/11.1.1

## Configuration 
OpenMP multicore CPU: 
>> nvc -mp openmp_10k.c -o mc_mp

(NOTE: change .c file according to the input size you want) 

>> sbatch mpBatch 

(NOTE: change cores and threads in the mpBatch script accordingly)

OpenACC multicore CPU:
>> nvc -acc -ta=multicore -Minfo=accel acc_10k.c -o mc_acc

(NOTE: change .c file according to the input size you want) 

>> sbatch accMcBatch 

(NOTE: change cores and threads in the accMcBatch script accordingly)

OpenACC GPU: 
>> nvc -acc -ta=tesla -Minfo=accel acc_10k.c -o gpu_acc

(NOTE: change .c file according to the input size you want)

>> sbatch accGpuBatch

(NOTE: change GPUs in the accBatch script accordingly)

View SMI:
>> sbatch accGpuBatch
>> sbatch SMIbatch 

View output:
>> more slurm-jobID.out

## Troubleshooting
Make sure the nvhpc module is loaded before compiling the code

## Maintainers
Swetha Sankar, Lauren Baron, Brendan Green
