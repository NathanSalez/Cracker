//
// Created by nsalez on 16/11/18.
//

#ifndef CRACKER_BRUTEFORCE_H
#define CRACKER_BRUTEFORCE_H

#include <iostream>
#include <string>
#include <chrono>   // pour obtenir le temps de recherche

// #define __DISP_TESTS__

namespace hack {

    /**
     * Services de la classe :
     * - Tester une possibilité (trySolution).
     * - Obtenir la durée de recherche d'un mot de passe (getElapsedSearch).
     * - Obtenir la solution via un string ou via son affichage (getSolution et dispSolution).
     * Cette classe nous permet s'il réussit son crackage, de connaitre le mot de passe d'un utilisateur.
     */
    class Bruteforce {

    protected :
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        bool passwordFound;
        std::string password;   /**< Le mot de passe à trouver, on suppose qu'on ne peut pas y accéder. */
        std::string solution;   /**< La solution, qui dans le cas présent, sera égal à password si on trouve le mot de passe. */


        /**
         * Utilisé dans la méthode run, teste si la chaine t correpond au mot de passe password.
         * @return true si la chaine t correspond au mot de passe, false sinon.
         */
        inline
        bool trySolution(std::string const& t)
        {
            // Ici on n'effecute qu'une comparaison.
            // Mais à l'avenir, on pourrait très bien avoir un mot de passe crypté dans "password"
#ifdef __DISP_TESTS__
            std::clog << "On teste la chaîne suivante : " << t << std::endl;
#endif
            return t == this->password;
        }


    public:

        Bruteforce(Bruteforce const& b) = delete;

        Bruteforce& operator=( Bruteforce const& b) = delete;

        /**
         * Constructeur par données
         */
        explicit Bruteforce(std::string const& p);

        /**
         * Retourne la durée de recherche du mot de passe, sous la forme d'un double.
         */
        double getElapsedSearch();

        /**
         * Affiche le mot de passe s'il a été trouvé.
         * Si ce n'est pas le cas, affiche une chaîne vide.
         */
        void dispSolution() const;

        /**
         * Accsseur de l'attribut solution.
         * @return
         */
        const std::string &getSolution() const;

        /**
         * Méthode de craquage de mot de passe.
         */
        virtual void run() = 0;

        /**
         * Retourne le nombre de possibilités associés aux propriétés de l'instance Bruteforce.
         */
        virtual size_t getNumberPossibilities() const = 0;

        ~Bruteforce() = default;

    };

}


#endif //CRACKER_BRUTEFORCE_H
