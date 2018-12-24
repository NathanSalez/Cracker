//
// Created by nsalez on 01/12/18.
//

#ifndef CRACKER_BRUTEFORCEDICTIONNARY_H
#define CRACKER_BRUTEFORCEDICTIONNARY_H

#include "fstream"
#include "Bruteforce.h"

namespace hack {

    /**
     * Services de la classe :
     * Trouver un mot de passe correspondant à une chaîne chiffrée donnée, à l'aide de l'attaque par dictionnaire.
     */
    class BruteforceDictionnary : public Bruteforce
    {

    public:

        /**
         * Constructeur par données de la classe, si le fichier pathFile n'existe pas, arrête l'exécution.
         */
        BruteforceDictionnary(const std::string& p, std::string const& pathFile);


        /**
         * Retourne le nombre de possibilités associés au fichier
         */
        size_t getNumberPossibilities() const;


        /**
         * Méthode de craquage de mot de passe.
         * Parcourt chaque ligne du fichier jusqu'à ce que :
         *      - Le mot de passe soit trouvé.
         *      - La fin du fichier est atteint.
         *      - La lecture d'une ligne s'est mal passé.
         */
        void run();


    private:
        std::string pathFile;

    };


    /**
     * Renvoie true si le fichier dont le chemin est Pathfile, est lisible.
     */
    bool is_readable(const char * pathFile);
}



#endif //CRACKER_BRUTEFORCEDICTIONNARY_H
