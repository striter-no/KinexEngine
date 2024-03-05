#pragma once
#include <AdtClasses/AdtClasses.hpp>
#include "VectorFuncs.hpp"
#include "Random.hpp"

namespace eml{

    typedef vector<vector<double>> matrix_t;

    // Matrix_t functions

    matrix_t multiplyMatrix(const matrix_t& matrix1, const matrix_t& matrix2) {
        int rows1 = matrix1.size();
        int cols1 = matrix1[0].size();
        int rows2 = matrix2.size();
        int cols2 = matrix2[0].size();

        if (cols1 != rows2) {
            throw std::invalid_argument("Invalid matrix_t dimensions for multiplication: "+to_string(cols1) + " " + to_string(rows2));
        }

        matrix_t result(rows1, vector<double>(cols2, 0));

        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols2; j++) {
                for (int k = 0; k < cols1; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }

        return {result};
    }

    matrix_t divideMatrix(const matrix_t& matrix1, const matrix_t& matrix2) {
        int rows1 = matrix1.size();
        int cols1 = matrix1[0].size();
        int rows2 = matrix2.size();
        int cols2 = matrix2[0].size();

        if (cols1 != rows2) {
            throw std::invalid_argument("Invalid matrix_t dimensions for divide: "+to_string(cols1) + " " + to_string(rows2));
        }

        matrix_t result(rows1, vector<double>(cols2, 0));

        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols2; j++) {
                for (int k = 0; k < cols1; k++) {
                    result[i][j] += matrix1[i][k] / matrix2[k][j];
                }
            }
        }

        return {result};
    }

    vector<double> multiplyMatrixAndVector(const matrix_t& matrix, const vector<double>& vec) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        if (cols != vec.size()) {
            throw std::invalid_argument("Invalid matrix_t and vector dimensions for multiplication");
        }

        vector<double> result(rows, 0);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i] += matrix[i][j] * vec[j];
            }
        }

        return {result};
    }

    matrix_t convertVectorToMatrix(const vector<double>& vec) {
        matrix_t matrix_t;
        for (const auto& element : vec) {
            matrix_t.push_back({element});
        }
        return {matrix_t};
    }

    std::vector<std::vector<double>> vfsplit(const std::vector<double> &vc, int out_size) {
        std::vector<std::vector<double>> result;
        int elements_per_subvector = vc.size() / out_size;
        int remainder = vc.size() % out_size;
        int start_index = 0;

        for (int i = 0; i < out_size; i++) {
            int subvector_size = elements_per_subvector + (i < remainder ? 1 : 0);
            result.push_back(std::vector<double>(vc.begin() + start_index, vc.begin() + start_index + subvector_size));
            start_index += subvector_size;
        }

        return {result};
    }

    vector<double> vector_dot(const vector<double> &a, 
                            const vector<double> &b,
                            int out_size){
        vector<double> out, to_sum;

        for(const double &ae : a){
            for(const double &be : b){
            to_sum.push_back(be * ae);
        }}

        matrix_t to_sum2 = vfsplit(to_sum, out_size);
        for(const auto &vc: to_sum2){
            out.push_back(adc::vsum(vc));
        }

        return {out};
    }

    double vector_dot(const std::vector<double>& v1, const std::vector<double>& v2) {
        double result = 0.0;
        for (size_t i = 0; i < v1.size(); i++) {
            result += v1[i] * v2[i];
        }
        return result;
    }

    vector<double> mvector_dot(std::vector<double> v1, std::vector<double> v2) {
        vector<double> result(v1.size(), 0);
        for (size_t i = 0; i < v1.size(); i++) {
            for(size_t j = 0; j < v2.size(); j++)
            result[i] += v1[i] * v2[i];
        }
        return {result};
    }

    vector<double> mvector_dot(std::vector<double> v1, double f) {
        vector<double> result(v1.size(), 0);
        for (size_t i = 0; i < v1.size(); i++) {
            result[i] += v1[i] * f;
        }
        return {result};
    }

    matrix_t transposeMatrix(const matrix_t& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        matrix_t transposed(cols, vector<double>(rows));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                transposed[j][i] = matrix[i][j];
            }
        }

        return {transposed};
    }

    int get_xsize(const matrix_t& mt){
        return mt[0].size();
    }

    int get_ysize(const matrix_t& mt){
        return mt.size();
    }

    matrix_t newmatrix(const eml::vec2i &size, double val = 0.f){
        // cout<<3<<endl;
        matrix_t out(size.y);for(int y:adc::range(size.y)){
            out[y] = vector<double>((int)size.x, val);
        }
        // cout<<4<<' '<<out.size()<<' '<<out[0].size()<<endl;
        return {out};
    }

    enum SHAPE_TYPE{
        X_VECTOR,
        Y_VECTOR
    };

    template<class T = float>
    class Matrix{
        private:
        vector<vector<T>> data;

        public:
        
        Matrix(vector<vector<T>> data): data(data){;}
        Matrix(eml::vec2i size){
            data = newmatrix(size);
        }

        
        // {1, 0}
        // {0, 1}
        // {1, 1}
        Matrix(vector<T> layer, SHAPE_TYPE shpt){
            switch(shpt){
                case X_VECTOR:{
                    data = Matrix({layer.size(), 1}).getdata();
                    data[0] = layer;
                    break;
                }
                case Y_VECTOR:{
                    data = Matrix({1, layer.size()}).getdata();
                    for(int i:adc::range(layer.size())){data[i][0]=layer[i];}
                    break;
                }
            }
        }
        Matrix static random(eml::vec2i size, eml::vec2i random_size){
            Matrix m(size);
            for(int y:adc::range(size.y)){
                for(int x:adc::range(size.x)){
                    m.set({x, y}, uniform(random_size.x, random_size.y));
                }
            }
            return {m};
        }

        Matrix stabalize(T minv, T maxv){
            Matrix m(getsize());
            for(int y:adc::range(getsize().y)){
                m.setVec(y, vecclamp(data[y], minv, maxv));
            }
            return {m};
        }

        void self_stabalize(T minv, T maxv){
            for(int y:adc::range(getsize().y)){
                setVec(y, vecclamp(data[y], minv, maxv));
            }
        }

        void to_zero(){
            for(int y:adc::range(getsize().y)){
                for(int x:adc::range(getsize().x)){
                    set({x, y}, 0);
                }
            }
        }

        vector<vector<T>> getdata(){return data;}
        eml::vec2i getsize(){return {get_xsize(data), get_ysize(data)};}
        void set(eml::vec2i pos, T val){data[(int)pos.y][(int)pos.x] = val;}
        void setVec(int y, vector<T> vc){data[y]=vc;}

        // 3,2 -> 1,6
        Matrix to_yvector(){
            vector<vector<T>> tdata = newmatrix({1, getsize().x * getsize().y});
            int i = 0;
            for(int y:adc::range(getsize().y)){
                for(int x:adc::range(getsize().x)){
                    tdata[i][0] = data[y][x];
                    i++;
                }
            }
            return {tdata};
        }

        // 3,2 -> 6,1
        Matrix to_xvector(){
            vector<vector<T>> tdata = newmatrix({getsize().x * getsize().y, 1});
            int i = 0;
            for(int y:adc::range(getsize().y)){
                for(int x:adc::range(getsize().x)){
                    tdata[0][i] = data[y][x];
                    i++;
                }
            }
            return {tdata};
        }

        void reshape(eml::vec2i newsize){
            // vector<vector<T>> oldData = data;
            // vector<vector<T>> newData = newmatrix(newsize);

            // for(int y:adc::range(newsize.y)){for(int x:adc::range(newsize.x)){
                // ;
            // }}

            /*
            2(x), 3(y) -> 3(x), 2(y)

            [[0, 1],   -> [[0, 1, 2],
            [2, 3],       [3, 4, 5]]
            [4, 5]]     

            2(x), 3(y) -> 1(x), 6(y)

            [[0, 1],   -> [[0],
            [2, 3],       [1], 
            [4, 5]]       [2],
                        [3],
                        [4], 
                        [5]]
            
            4, 4 -> 8, 2
            [[ 0,  1,  2,  3],
            [ 4,  5,  6,  7],
            [ 8,  9, 10, 11],
            [12, 13, 14, 15]]
            ->
            [[0,  1,  2,  3, 4,  5,  6,  7],
            [8,  9, 10, 11, 12, 13, 14, 15]]

            6, 2 -> 3, 4
            [0, 1, 2, 3, 4,  5]
            [6, 7, 8, 9, 10,11]
            ->
            [0, 1, 2]
            [3, 4, 5],
            [6, 7, 8],
            [9,10,11]
            */
        }

        void transpose(){
            data = transposeMatrix(data);
        }

        void operator*=(Matrix b){
            data = multiplyMatrix(data, b.getdata());
        }
        Matrix operator*(Matrix b){return {multiplyMatrix(data, b.getdata())};}

        void operator/=(Matrix b){divideMatrix(data, b.getdata());}
        Matrix operator/(Matrix b){return {divideMatrix(data, b.getdata())};}

        void operator+=(Matrix b){
            if(b.getsize()!=getsize()){
                throw std::invalid_argument("Invalid sizes of matrixes to sum (+=): " + getsize().str() + "; " + b.getsize().str());
            }
            eml::vec2i bsize = b.getsize();
            for(int y:adc::range(bsize.y)){
                for(int x:adc::range(bsize.x)){
                    data[y][x] += b.getdata()[y][x];
                }
            }
        }
        Matrix operator+(Matrix b){
            if(b.getsize()!=getsize()){
                throw std::invalid_argument("Invalid sizes of matrixes to sum (+): " + getsize().str() + "; " + b.getsize().str());
            }
            eml::vec2i bsize = b.getsize();
            vector<vector<T>> data_t = data;
            for(int y:adc::range(bsize.y)){
                for(int x:adc::range(bsize.x)){
                    data_t[y][x] += b.getdata()[y][x];
                }
            }
            return {data_t};
        }

        void operator-=(Matrix b){
            if(b.getsize()!=getsize()){
                throw std::invalid_argument("Invalid sizes of matrixes to sub (-=): " + getsize().str() + "; " + b.getsize().str());
            }
            eml::vec2i bsize = b.getsize();
            for(int y:adc::range(bsize.y)){
                for(int x:adc::range(bsize.x)){
                    data[y][x] -= b.getdata()[y][x];
                }
            }
        }
        Matrix operator-(Matrix b){
            if(b.getsize()!=getsize()){
                throw std::invalid_argument("Invalid sizes of matrixes to sub (-): " + getsize().str() + "; " + b.getsize().str());
            }
            eml::vec2i bsize = b.getsize();
            vector<vector<T>> data_t = data;
            for(int y:adc::range(bsize.y)){
                for(int x:adc::range(bsize.x)){
                    data_t[y][x] -= b.getdata()[y][x];
                }
            }
            return {data_t};
        }

        void operator*=(T b){
            for(auto &l:data){for(T &e:l){
                e *= b;
            }}
        }
        Matrix operator*(T b){
            vector<vector<T>> data_ = data;
            for(auto &l:data_){for(T &e:l){
                e *= b;
            }}
            return {data_};
        }

        void operator/=(T b){
            for(auto &l:data){for(T &e:l){
                e /= b;
            }}
        }
        Matrix operator/(T b){
            vector<vector<T>> data_ = data;
            for(auto &l:data_){for(T &e:l){
                e /= b;
            }}
            return {data_};
        }

        void operator+=(T b){
            for(auto &l:data){for(T &e:l){
                e += b;
            }}
        }
        Matrix operator+(T b){
            vector<vector<T>> data_ = data;
            for(auto &l:data_){for(T &e:l){
                e += b;
            }}
            return {data_};
        }

        void operator-=(T b){
            for(auto &l:data){for(T &e:l){
                e -= b;
            }}
        }
        Matrix operator-(T b){
            vector<vector<T>> data_ = data;
            for(auto &l:data_){for(T &e:l){
                e -= b;
            }}
            return {data_};
        }

        Matrix operator*(vector<T> vc){
            vector<vector<T>> data_ = data;
            if(getsize().y == 1){
                for(int i:adc::range(getsize().x)){
                    data_[0][i] *= vc[i];
                }
            } else if(getsize().x == 1){
                for(int i:adc::range(getsize().y)){
                    data_[i][0] *= vc[i];
                }
            } else {
                cout<<"error\n";
            }
            return {data_};
        }
        void operator*=(vector<T> vc){
            if(getsize().y == 1){
                for(int i:adc::range(getsize().x)){
                    data[0][i] *= vc[i];
                }
            } else if(getsize().x == 1){
                for(int i:adc::range(getsize().y)){
                    data[i][0] *= vc[i];
                }
            } else {
                cout<<"error\n";
            }
        }

        // void operator*=(vec3 vc){
            // ;
        // }

        // void operator*=(vec4 vc){
        //     ;
        // }

        // vec3 operator*(){
        //     ;
        // }

        // vec4 operator*(){
        //     ;
        // }

        vector<T> getvec(){
            vector<T> o;
            if(getsize().y == 1){
                for(int i:adc::range(getsize().x)){
                    o.push_back(data[0][i]);
                }
            } else if(getsize().x == 1){
                for(int i:adc::range(getsize().y)){
                    o.push_back(data[i][0]);
                }
            } else {
                cout<<"error\n";
            }
            return {o};
        }

        SHAPE_TYPE getshape(){
            if(getsize().y == 1){
                return Y_VECTOR;
            }
            return X_VECTOR;
        }

        string str(){
            string out = "["; 
            for(int y:adc::range(data.size())){    
                if(y!=0){out += ' '; }
                out += "[";
                for(int x:adc::range(data[0].size())){
                    out += to_string(data[y][x]);
                    if(x != (data[0].size() - 1)){
                        out += ", ";
                    }
                }
                out += "]";
                if(y != data.size()-1){
                    out += '\n';
                }
            }
            out += "]";
            return {out};
        }

        Matrix(){;}
    };
};