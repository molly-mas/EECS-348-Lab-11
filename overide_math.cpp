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

    void clear(){
        if(data){
            for(int i = 0; i < n; i++){
                delete[] data[i];
                delete[] data;
                data = nullptr;
            }
            n = 0;
        }
    }
    void resize(int newnum){
        clear();
        n = newnum;
        data = new double*[n];
        for(int i = 0; i <n; i++){
            data[i] = new double[n];
        }

    }

    void add_spot(int index1, int index2, int value){
        data[index1][index2] = value;
    }

    void print_matrix(){
        std::cout << "Matrix: \n";
        for(int i = 0; i< n; i++){
            for(int j = 0; j<n; j++){
                std::cout << data[i][j] << "\t";
            }
        }
    }


};

void fill_matrixs(std::string filename, MathMatrix& m1, MathMatrix& m2){
    std::ifstream theFile (filename);
    int size;
    if (!theFile){
        throw new std::runtime_error("this file cant be found");
    }

    theFile >> size;
    m1.resize(size);
    m2.resize(size);

    for(int i = 0; i < size; i++){
        for(int j =0; j <size; j++){
            int val;
            theFile >> val; 
            m1.add_spot(i, j, val);
        }
    }

    for(int i = 0; i < size; i++){
        for(int j =0; j <size; j++){
            int val;
            theFile >> val; 
            m2.add_spot(i, j, val);
        }
    }
}
