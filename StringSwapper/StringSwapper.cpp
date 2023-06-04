#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::fstream archivos;
std::fstream LeerArchivo(const char*);
std::vector<std::string> InterpretarArchivo(std::fstream&);
void WipeArchivo(const char*);
void GuardarArchivo(const char*);
void Intercambiar_texto();
std::vector<std::string> Vector_global;

bool FILE_EXIST;
bool SUCESSFUL;


int main(int argc, const char* argv[])
{
    std::cout << "We have " << argc - 1 << " text files to parse." << std::endl;
    std::cout << "Remember to have your < ; > in your file if not this won't work!" << std::endl;
    try {
        for (int i = 1; i < argc; i++)
        {
            SUCESSFUL = true;
            FILE_EXIST = true;

            std::cout << "============================================" << std::endl;
            std::cout << "Parsing: " << argv[i] << ".txt" << std::endl;
            archivos = LeerArchivo(argv[i]);
            Vector_global = InterpretarArchivo(archivos);

            Intercambiar_texto();

            WipeArchivo(argv[i]);
            GuardarArchivo(argv[i]);

            if (SUCESSFUL)
            {
                std::cout << argv[i] << ".txt has been parsed correctly!" << std::endl;
            }

            Vector_global.clear();
            std::cout << "============================================" << std::endl;
        }
        return 0;
    }
    catch (std::ifstream::failure)
    {
        std::cout << "An error happened while parsing the files." << std::endl;
        return -1;
    }
    catch (const char* msg)
    {
        std::cout << "Couldn't parse this file -> " << msg << std::endl;
        return -1;
    }
    catch (std::exception)
    {
        std::cout << "General error, make sure to put everything with <;> and <=>" << std::endl;
        return -1;
    }
}

std::fstream LeerArchivo(const char* text_name)
{
    try {
        std::string txt;
        txt = ".txt";

        std::fstream archivo;

        archivo.open(text_name + txt, std::ios::in);

        if (archivo.is_open())
        {
            FILE_EXIST = true;
            return archivo;
        }
        throw std::ifstream::failure("");

    }
    catch (std::ifstream::failure) {
        std::cout << "Couldn't open " << text_name << " - " <<
            "Make sure your file is in the same directory as the program!" << std::endl;
        FILE_EXIST = false;
        SUCESSFUL = false;
    }
}

std::vector<std::string> InterpretarArchivo(std::fstream& archivo)
{
    try {
        std::string Linea;
        std::vector<std::string> instruccion;
        const int zero = 0;

        while (!archivo.eof())
        {
            while (std::getline(archivo, Linea))
            {
                size_t posicion;

                if ((posicion = Linea.find(";")) == std::string::npos)
                {
                    throw "Please use <;> in your instructions!";
                }

                while (((posicion = Linea.find(";")) != std::string::npos))
                {
                    instruccion.push_back(Linea.substr(zero, posicion));
                    Linea.erase(0, posicion + 1);
                }
            }
        }
        archivo.close();
        return instruccion;
    }
    catch (std::exception)
    {
        std::cout << "Something has gone wrong when reading the file!" << std::endl;
        SUCESSFUL = false;
    }
    catch (const char* msg)
    {
        std::cout << msg << std::endl;
        SUCESSFUL = false;
    }
}

void Intercambiar_texto()
{
    try {
        char equal;
        equal = '=';
        size_t posicion;
        const int zero = 0;
 
        std::string f_part;
        std::string s_part;

        for (int i = 0; i< Vector_global.size(); i++)
        {
            if (Vector_global[i].find(equal) == std::string::npos) {
                throw "No (=) found in the text file!";
            }

            posicion = Vector_global[i].find(equal);
            f_part = Vector_global[i].substr(zero, Vector_global[i].find("="));
            s_part = Vector_global[i].substr(Vector_global[i].find("=")+1, std::string::npos);

            Vector_global[i] = s_part + " = " + f_part + ";";
        }

    }
    catch (const char* msg)
    {
        std::cout << msg << std::endl;
        SUCESSFUL = false;
    }
}

void WipeArchivo(const char* text_name)
{
    try
    {
        std::string txt;
        txt = "_swapped.txt";
        std::ofstream archivo;
        if (!FILE_EXIST || !SUCESSFUL)
        {
            throw std::exception("");
        }
        archivo.open(text_name + txt, std::ofstream::out | std::ofstream::trunc);
        archivo.close();
       
    }
    catch (std::exception e)
    {
        std::cout << "Cannot wipe the file before writing" << std::endl;
        SUCESSFUL = false;
    }
    
}
void GuardarArchivo(const char* text_name) 
{
    try 
    {
        std::string txt;
        txt = "_swapped.txt";
        std::ofstream archivo; 		
        if (FILE_EXIST && SUCESSFUL)
        {
            archivo.open(text_name + txt);

            if (archivo.is_open())
            {
                for (std::string str : Vector_global)
                {
                    archivo << str << std::endl;
                }
            }
            else {
                throw std::exception("");
            }
        }
        else {
            throw std::exception("");
        }
    }
    catch (std::exception e)
    {
        std::cout << "Cannot save the file!" << std::endl;
        SUCESSFUL = false;
    }
}
