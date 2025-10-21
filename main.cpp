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

    // Constructor de copia (deep copy)
    MatrizDinamica(const MatrizDinamica<T>& otra) : MatrizBase<T>(otra._filas, otra._columnas) {
        asignarMemoria();
        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                _datos[i][j] = otra._datos[i][j];
            }
        }
    }

    // Operador de asignación (deep copy)
    MatrizDinamica<T>& operator=(const MatrizDinamica<T>& otra) {
        if (this != &otra) {
            liberarMemoria();
            this->_filas = otra._filas;
            this->_columnas = otra._columnas;
            asignarMemoria();
            for (int i = 0; i < this->_filas; i++) {
                for (int j = 0; j < this->_columnas; j++) {
                    _datos[i][j] = otra._datos[i][j];
                }
            }
        }
        return *this;
    }

    // Constructor de movimiento
    MatrizDinamica(MatrizDinamica<T>&& otra) noexcept : MatrizBase<T>(otra._filas, otra._columnas) {
        _datos = otra._datos;
        otra._datos = nullptr;
        otra._filas = 0;
        otra._columnas = 0;
    }

    // Operador de asignación de movimiento
    MatrizDinamica<T>& operator=(MatrizDinamica<T>&& otra) noexcept {
        if (this != &otra) {
            liberarMemoria();
            this->_filas = otra._filas;
            this->_columnas = otra._columnas;
            _datos = otra._datos;
            otra._datos = nullptr;
            otra._filas = 0;
            otra._columnas = 0;
        }
        return *this;
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

    void setValor(int i, int j, T valor) {
        if (i >= 0 && i < this->_filas && j >= 0 && j < this->_columnas) {
            _datos[i][j] = valor;
        }
    }
    
    MatrizBase<T>* sumar(const MatrizBase<T>& otra) const override {
        // Por implementar
        return nullptr;
    }
    
    void imprimir() const override {
        for (int i = 0; i < this->_filas; i++) {
            cout << "| ";
            for (int j = 0; j < this->_columnas; j++) {
                cout << fixed << setprecision(1) << _datos[i][j];
                if (j < this->_columnas - 1) cout << " | ";
            }
            cout << " |" << endl;
        }
    }
};

//Main
int main() {
    cout << "--- Sistema Genérico de Álgebra Lineal ---" << endl;
    cout << ">> Demostración de Genericidad (Tipo FLOAT) <<"<< endl;

    MatrizDinamica<float>* A = new MatrizDinamica<float>(2, 2);
    A->setValor(0, 0, 1.5f);
    A->setValor(0, 1, 2.0f);
    A->setValor(1, 0, 3.5f);
    A->setValor(1, 1, 4.0f);
    
    cout << "Matriz A (original):" << endl;
    A->imprimir();
    cout<<endl;

    //probar constructor de copia 
    MatrizDinamica<float>B(*A);
    cout << "Matriz B (copia de A):" << endl;
    B.imprimir();
    
    delete A;
        
    return 0;
}