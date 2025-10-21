#include <iostream>
#include <iomanip>

using namespace std;

//clase base abstracta 
template <typename T>
class MatrizBase {
protected:
    int _filas;
    int _columnas;

public:
    MatrizBase(int filas, int columnas) : _filas(filas), _columnas(columnas) {}
    virtual ~MatrizBase() {}
    
    virtual void cargarValores() = 0;
    virtual MatrizBase<T>* sumar(const MatrizBase<T>& otra) const = 0;
    virtual void imprimir() const = 0;
    
    int getFilas() const { return _filas; }
    int getColumnas() const { return _columnas; }
};

//Main
int main() {
    cout << "--- Sistema Genérico de Álgebra Lineal ---" << endl;
    cout << ">> Demostración de Genericidad (Tipo FLOAT) <<"<< endl;
    
    return 0;
}