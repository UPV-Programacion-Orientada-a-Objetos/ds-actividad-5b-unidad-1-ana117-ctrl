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

//matriz dinamica
template <typename T>
class MatrizDinamica : public MatrizBase<T> {
private:
    T** _datos;
    
    void asignarMemoria() {
        _datos = new T*[this->_filas];
        for (int i = 0; i < this->_filas; i++) {
            _datos[i] = new T[this->_columnas];
        }
    }
    
    void liberarMemoria() {
        if (_datos != nullptr) {
            for (int i = 0; i < this->_filas; i++) {
                delete[] _datos[i];
            }
            delete[] _datos;
            _datos = nullptr;
        }
    }

    public:
    // Constructor
    MatrizDinamica(int filas, int columnas) : MatrizBase<T>(filas, columnas) {
        asignarMemoria();
        // Inicializar en cero
        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                _datos[i][j] = T(0);
            }
        }
    }

        // Destructor
    ~MatrizDinamica() {
        cout << "Liberando memoria de Matriz Dinámica..." << endl;
        liberarMemoria();
    }
    
    void cargarValores() override {
        cout << "Ingrese los valores para la matriz (" << this->_filas << "x" << this->_columnas << "):" << endl;
        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                cout << "Elemento [" << i << "][" << j << "]: ";
                cin >> _datos[i][j];
            }
        }
    }
    
    MatrizBase<T>* sumar(const MatrizBase<T>& otra) const override {
        // Por implementar
        return nullptr;
    }
    
    void imprimir() const override {
        // Por implementar
    }
};

//Main
int main() {
    cout << "--- Sistema Genérico de Álgebra Lineal ---" << endl;
    cout << ">> Demostración de Genericidad (Tipo FLOAT) <<"<< endl;
    
    return 0;
}