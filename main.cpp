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

    // Sobrecarga del operador +
    MatrizBase<T>* operator+(const MatrizBase<T>& otra) const {
        return sumar(otra);
    }
    
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
        if (this->_filas != otra.getFilas() || this->_columnas != otra.getColumnas()) {
            cout << "Error: Las dimensiones no coinciden para la suma." << endl;
            return nullptr;
        }
        
        MatrizDinamica<T>* resultado = new MatrizDinamica<T>(this->_filas, this->_columnas);
        
        const MatrizDinamica<T>* otraDinamica = dynamic_cast<const MatrizDinamica<T>*>(&otra);
        
        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                if (otraDinamica) {
                    resultado->_datos[i][j] = _datos[i][j] + otraDinamica->_datos[i][j];
                }
            }
        }
        
        return resultado;
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

    template <typename U, int M, int N>
    friend class MatrizEstatica;
};

//Matriz estatica
template <typename T, int M, int N>
class MatrizEstatica : public MatrizBase<T> {
private:
    T _datos[M][N];

public:
    MatrizEstatica() : MatrizBase<T>(M, N) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                _datos[i][j] = T(0);
            }
        }
    }
    
    void cargarValores() override {
        cout << "Ingrese los valores para la matriz (" << M << "x" << N << "):" << endl;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << "Elemento [" << i << "][" << j << "]: ";
                cin >> _datos[i][j];
            }
        }
    }
    
    void setValor(int i, int j, T valor) {
        if (i >= 0 && i < M && j >= 0 && j < N) {
            _datos[i][j] = valor;
        }
    }
    
    MatrizBase<T>* sumar(const MatrizBase<T>& otra) const override {
        if (M != otra.getFilas() || N != otra.getColumnas()) {
            cout << "Error: Las dimensiones no coinciden para la suma." << endl;
            return nullptr;
        }
        
        MatrizDinamica<T>* resultado = new MatrizDinamica<T>(M, N);
        
        const MatrizEstatica<T, M, N>* otraEstatica = dynamic_cast<const MatrizEstatica<T, M, N>*>(&otra);
        const MatrizDinamica<T>* otraDinamica = dynamic_cast<const MatrizDinamica<T>*>(&otra);
        
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                T valorOtra = T(0);
                if (otraEstatica) {
                    valorOtra = otraEstatica->_datos[i][j];
                } else if (otraDinamica) {
                    valorOtra = otraDinamica->_datos[i][j];
                }
                resultado->setValor(i, j, _datos[i][j] + valorOtra);
            }
        }
        
        return resultado;
    }
    
    void imprimir() const override {
        for (int i = 0; i < M; i++) {
            cout << "| ";
            for (int j = 0; j < N; j++) {
                cout << fixed << setprecision(1) << _datos[i][j];
                if (j < N - 1) cout << " | ";
            }
            cout << " |" << endl;
        }
    }
};

//Main
int main() {
    cout << "--- Sistema Genérico de Álgebra Lineal ---" << endl << endl;
    
     // Probar MatrizDinamica
    MatrizBase<float>* A = new MatrizDinamica<float>(2, 2);
    dynamic_cast<MatrizDinamica<float>*>(A)->setValor(0, 0, 1.5f);
    dynamic_cast<MatrizDinamica<float>*>(A)->setValor(0, 1, 2.0f);
    dynamic_cast<MatrizDinamica<float>*>(A)->setValor(1, 0, 3.5f);
    dynamic_cast<MatrizDinamica<float>*>(A)->setValor(1, 1, 4.0f);
    
    cout << "Matriz Dinámica A:" << endl;
    A->imprimir();
    cout << endl;
    
    // Probar MatrizEstatica
    MatrizBase<float>* B = new MatrizEstatica<float, 2, 2>();
    dynamic_cast<MatrizEstatica<float, 2, 2>*>(B)->setValor(0, 0, 0.5f);
    dynamic_cast<MatrizEstatica<float, 2, 2>*>(B)->setValor(0, 1, 1.0f);
    dynamic_cast<MatrizEstatica<float, 2, 2>*>(B)->setValor(1, 0, 2.5f);
    dynamic_cast<MatrizEstatica<float, 2, 2>*>(B)->setValor(1, 1, 3.0f);
    
    cout << "Matriz Estática B:" << endl;
    B->imprimir();
    cout << endl;
    
    // Sumar Dinámica + Estática
    MatrizBase<float>* C = *A + *B;
    cout << "Matriz C = A + B (Dinámica + Estática):" << endl;
    C->imprimir();
    
    delete A;
    delete B;
    delete C;
    
    return 0;
}