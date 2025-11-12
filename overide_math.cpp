#include <iostream>
#include <fstream> 
#include <string>
#include <stdio.h>

class MathMatrix{
    private:
        int n;
        double** data;
    
    public:
    MathMatrix(int size){
        n = size;
        data = new double*[n];
        for(int i = 0; i<n; i++){
            data[i] = new double[n];
        }
    }

    ~MathMatrix(){
        for(int i = 0; i < n; i++){
            delete[] data[i];
            delete[] data;
        }
    }

    


};

