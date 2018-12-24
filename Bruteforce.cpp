//
// Created by nsalez on 16/11/18.
//

#include "Bruteforce.h"

namespace hack
{

    Bruteforce::Bruteforce(std::string const& p) : passwordFound(false)
    {
        /*if(!p.empty()) {
            this->password.resize(p.size());
            std::copy(p.begin(), p.end(), this->password.begin());
        }*/
        this->password = p;
    }


    void Bruteforce::dispSolution() const
    {
        if( passwordFound )
            std::cout << "Le mot de passe associé à la chaîne '" << this->password << "' est : '" << this->solution << "'" << std::endl;
        else
            std::cout << "Le mot de passe n'a pas été trouvé !" << std::endl;
    }


    const std::string &Bruteforce::getSolution() const {
        return solution;
    }



    double Bruteforce::getElapsedSearch()
    {
        std::chrono::duration<double> elapsed_seconds = this->end - this->start;
        return elapsed_seconds.count();
    }

}
