//
// Created by nsalez on 01/12/18.
//

#include "BruteforceDictionnary.h"

namespace hack
{
    BruteforceDictionnary::BruteforceDictionnary(const std::string& p, const std::string& pathFile) : Cracker(p)
    {
        if( ! is_readable(pathFile.c_str()))
        {
            exit(5);
        }
        else
        {
            this->pathFile.resize(pathFile.size());
            std::copy(pathFile.begin(), pathFile.end(), this->pathFile.begin());
        }
    }


    size_t BruteforceDictionnary::getNumberPossibilities() const
    {
        std::ifstream flux( this->pathFile);
        std::string line;
        size_t nb = 0;
        while( std::getline(flux, line) )
        {
            ++nb;
            //std::clog << "Ligne lue : \"" << line << "\"" << std::endl;
        }

        return nb;
    }




    void BruteforceDictionnary::run()
    {
        std::ifstream flux( this->pathFile);
        std::string line;
        this->start = std::chrono::system_clock::now();
        while( std::getline(flux, line) )
        {
            if( this->trySolution(line) )
            {
                this->passwordFound = true;
                this->solution = line;
                this->end = std::chrono::system_clock::now();
                return;
            }
        }
        this->end = std::chrono::system_clock::now();
    }



    bool is_readable(const char *filePath)  // cf developpez.com
    {
        std::ifstream fichier( filePath);
        return !fichier.fail();
    }

}