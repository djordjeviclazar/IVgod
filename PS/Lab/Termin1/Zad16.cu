%%cu
#include <cuda.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define N 20

__global__ void kernel1(int* A, int* B, int* C)
{
    int length = N * N;
    int index = threadIdx.x, pom;

    while(index < length)
    {
        pom = A[index] - B[index];
        C[index] = pom < 0 ? 0 : pom;
     
        index += blockDim.x;
    }
}

__global__ void kernel2(int* A, int* B, int* C)
{
    int length = N * N;
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int threadNumber = blockDim.x * gridDim.x, pom;

    while(index < length)
    {
        pom = A[index] - B[index];
        C[index] = pom < 0 ? 0 : pom;
     
        index += threadNumber;
    }
}

bool test(int* A, int* B, int* C)
{
    int length = N * N;
 
    for(int i = 0; i < length; i++)
    {
       int result = A[i] - B[i];
       if (result < 0) { result = 0; }
       if (result != C[i])
       {
           return false;
       }
    }
 
    return true;
}

int* generateMatrix()
{
    const int length = N * N;
 
    int* result = new int[length];
    
    for(int i = 0; i < N * N; i++)
    {
        result[i] = rand() % 100;
    }
 
    return result;
}

void printMatrix(int* A)
{
    int length = N * N, k = 0;
    for(int i = 0; i < length; i++)
    {
        std::cout << A[i] << "\t";

        if(++k >= N)
        {
            k = 0;
            std::cout << "\r\n";
        }
        
    }
 
    std::cout << "-----------------------------------------\r\n";
}

int main(void)
{
    srand(time(0));
    const int length = N * N;
    int *A = generateMatrix(), *B = generateMatrix(), *C = new int[length]; 
    int *Adev, *Bdev, *Cdev ;
  	bool result = false;
 
    cudaMalloc(&Adev, length * sizeof(int));
    cudaMalloc(&Bdev, length * sizeof(int));
    cudaMalloc(&Cdev, length * sizeof(int));
 
    cudaMemcpy(Adev, A, length * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(Bdev, B, length * sizeof(int), cudaMemcpyHostToDevice);

    kernel1<<<1, 20>>>(Adev, Bdev, Cdev);
    cudaMemcpy(C, Cdev, length * sizeof(int), cudaMemcpyDeviceToHost);
 
    result = test(A, B, C);
    if(result) { std::cout << "Correct"; }
    else { std::cout << "Incorrect"; }
 
    std::cout << "\r\n";
    printMatrix(A);
    std::cout << "\r\n";
    printMatrix(B);
    std::cout << "\r\n";
    printMatrix(C);
	
    kernel2<<<20, 1>>>(Adev, Bdev, Cdev);
    cudaMemcpy((void*)C, (void*)Cdev, length * sizeof(int), cudaMemcpyDeviceToHost);
 
    result = test(A, B, C);
    if(result) { std::cout << "Correct"; }
    else { std::cout << "Incorrect"; }
    std::cout << "\r\n";
 
    kernel2<<<5, 4>>>(Adev, Bdev, Cdev);
    cudaMemcpy((void*)C, (void*)Cdev, length * sizeof(int), cudaMemcpyDeviceToHost);
 
    result = test(A, B, C);
    if(result) { std::cout << "Correct"; }
    else { std::cout << "Incorrect"; }
    std::cout << "\r\n";
 
    kernel2<<<2, 10>>>(Adev, Bdev, Cdev);
    cudaMemcpy((void*)C, (void*)Cdev, length * sizeof(int), cudaMemcpyDeviceToHost);
 
    result = test(A, B, C);
    if(result) { std::cout << "Correct"; }
    else { std::cout << "Incorrect"; }
    std::cout << "\r\n";
 
    kernel2<<<10, 2>>>(Adev, Bdev, Cdev);
    cudaMemcpy((void*)C, (void*)Cdev, length * sizeof(int), cudaMemcpyDeviceToHost);

    result = test(A, B, C);
    if(result) { std::cout << "Correct"; }
    else { std::cout << "Incorrect"; }
    std::cout << "\r\n";
 
    /*free*/
    delete[] A; delete[] B; delete[] C;
    A = 0; B = 0; C = 0;

    cudaFree(Adev);
    cudaFree(Bdev);
    cudaFree(Cdev);

    cudaDeviceReset();

    return 0;
}