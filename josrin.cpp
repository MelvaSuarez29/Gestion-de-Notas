
#include <iostream>
#include <cctype>

using namespace std;


bool login() {
    string usuario, clave;
    int intentos = 3;

    while (intentos > 0) {
        cout << "\n=== LOGIN ===" << endl;
        cout << "Usuario: ";
        getline(cin, usuario);
        cout << "Clave: ";
        getline(cin, clave);

        if (usuario == "admin" && clave == "1234") {
            cout << "\nLogin exitoso!" << endl;
            return true;
        } else {
            intentos--;
            cout << "Datos incorrectos. Intentos restantes: " << intentos << endl;
        }
    }

    cout << "Acceso denegado." << endl;
    return false;
}


bool cedulaValida(string cedula) {
    if (cedula.length() != 10) {
        cout << "La cédula debe tener 10 dígitos\n";
        return false;
    }

    for (char c : cedula) {
        if (!isdigit(c)) {
            cout << "La cédula solo debe contener números\n";
            return false;
        }
    }

    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    if (!((provincia >= 1 && provincia <= 24) || provincia == 30)) {
        cout << "Código de provincia inválido\n";
        return false;
    }

    return true;
}


bool esLetraValida(char c) {
    if (isalpha((unsigned char)c) || c == ' ')
        return true;

    unsigned char uc = (unsigned char)c;
    return (uc == 241 || uc == 209); 
}


bool validarNombre(string nombre) {
    if (nombre.empty()) {
        cout << "El nombre no puede estar vacío\n";
        return false;
    }

    for (char c : nombre) {
        if (!esLetraValida(c)) {
            cout << "Nombre inválido. Solo letras y espacios\n";
            return false;
        }
    }
    return true;
}


double validarNota() {
    double nota;
    while (true) {
        cout << "Ingrese la nota (0.0 - 10.0): ";
        cin >> nota;

        if (cin.fail() || nota < 0 || nota > 10) {
            cout << "Nota inválida\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            cin.ignore();
            return nota;
        }
    }
}


int validarSemestre() {
    int semestre;
    while (true) {
        cout << "Ingrese semestre (1-5): ";
        cin >> semestre;

        if (cin.fail() || semestre < 1 || semestre > 5) {
            cout << "Semestre inválido\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            cin.ignore();
            return semestre;
        }
    }
}
