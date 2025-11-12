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

    void add_spot(int index1 = 0, int index2 =0, int value = 100){
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

    MathMatrix operator+(const MathMatrix& other) const{
        MathMatrix result(n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j<n; j++){
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    MathMatrix operator*(const MathMatrix& other) const{
        MathMatrix result(n);
        int val = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j<n; j++){
                for(int k = 0; k <n; k++){
                    val = data[i][k] * other.data[k][j];
                    val += val;
                }
                result.data[i][j] = val;
                val = 0;
            }
        }

        return result;
    }

    int grab_val(int index1, int index2){
        return data[index1][index2];
    }

    int get_size(){
        return n;
    }

    double* get_row(int index) const{
        return data[index];
    }

    void swap_row(int index, double* val){
        data[index] = val;
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
    theFile.close();
}

void swap_row(MathMatrix a, int index1 = 0, int index2 = 1){
    int size = a.get_size();
    if (index1 >= size || index2 >= size || index1 < 0 || index2 < 0){
        std::cerr << "Invalid Index\n";
        throw std::exception();
    }
    double* temp = a.get_row(index1);
    a.swap_row(index1, a.get_row(index2));
    a.swap_row(index2, temp);
    std::cout << "Swapped rows: \n";
    a.print_matrix();
}

void add_diag(MathMatrix a){
    int val = 0;
    int size = a.get_size();
    for(int i = 0; i <size; i++){
        val += a.grab_val(i,i);
    }
    std::cout<< "Diagonal Sum of Matrix: " << val;
}


void swap_col(MathMatrix a, int index1 =0, int index2=1){
    int size = a.get_size();
    if (index1 >= size || index2 >= size || index1 < 0 || index2 < 0){
        std::cerr << "Invalid Index\n";
        throw std::exception();
    }
    int temp;
    for(int i = 0; i<size; i++){
        temp = a.grab_val(i, index1);
        a.add_spot(i, index1, a.grab_val(i, index2));
        a.add_spot(i,index2, temp);
    }
    std::cout << "Swapped Columns: \n";
    a.print_matrix();

}


//make main dont for get to free after adding 

