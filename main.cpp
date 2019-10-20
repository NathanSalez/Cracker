#include "BruteforceSimple.h"
#include "BruteforceDictionnary.h"

enum class typeTest
{
    begin,
    simpleV1,   // cherche le mot de passe, constituée de caractères numériques, associée à la chaîne "7459138".
    simpleV1_2,
    simpleV1_3, // Comparer le temps de recherche avec simple V2_3
    simpleV1_4, // Donne le temps nécessaire pour chercher toutes les permutations alphanumériques d'un ensemble de 5 caractères
    simpleV2,   // test de BruteforceSimple avec maxSize = minSize
    simpleV2_2, // test de BruteforceSimple avec maxSize = minSize = 1
    simpleV2_3, // a comparer avec simpleV1_3
    dictionnary,
    end
};


void testBot(typeTest mode);

int main() {
    /** (V1)
     * hack::typeSet::letter :
     * Longueur : 3 lettres | Durée de la recherche : 0.156669 secondes
     * Longueur : 4 lettres | Durée de la recherche : 4.19172 secondes
     * Longueur : 5 lettres | Durée de la recherche : 208.161 secondes
     *
     * hack::typeSet::alphanumeric :
     * Longueur : 3 lettres | Durée de la recherche : 0.210586 secondes
     * Longueur : 4 lettres | Durée de la recherche : 9.65888 secondes
     * Longueur : 5 lettres | Durée de la recherche : 529.137 secondes
     */


    /** (V4)
     * hack::typeSet::letter :
     * Longueur : 3 lettres | Durée de la recherche : 0.115616 secondes
     * Longueur : 4 lettres | Durée de la recherche : 3.42189 secondes
     * Longueur : 5 lettres | Durée de la recherche : 184.541 secondes
     *
     * hack::typeSet::alphanumeric :
     * Longueur : 3 lettres | Durée de la recherche : 0.159784 secondes
     * Longueur : 4 lettres | Durée de la recherche : 6.81374 secondes
     * Longueur : 5 lettres | Durée de la recherche : 448.138 secondes
     */

    // Permet d'obtenir le nombre de tests effectués en comptant le nombre de lignes du fichier
    // Pour cela, on redirige la sortie clog vers un fichier texte.
    // Remarque : décommenter la ligne 12 de Cracker.h
#ifdef __BRUTEFORCE_SIMPLE_COUNT_DEBUG
    std::ofstream logOut("tests.txt");
    std::clog.rdbuf(logOut.rdbuf());
#endif

    //testBot(typeTest::simpleV1);
    testBot(typeTest::simpleV1_2);
    //testBot(typeTest::simpleV1_3);
    //testBot(typeTest::simpleV1_4);
    //testBot(typeTest::simpleV2);
    //testBot(typeTest::simpleV2_2);
    //testBot(typeTest::simpleV2_3);
    //testBot(typeTest::dictionnary);
    return 0;
}


void testBot(typeTest mode)
{
    hack::Cracker * bot = nullptr;
    std::vector<char> container;
    container.push_back('a');
    container.push_back('b');
    container.push_back('c');
    switch(mode)
    {
        case typeTest::simpleV1 :
            bot = new hack::BruteforceSimple("7459138",7,hack::typeSet::number);
            break;

        case typeTest::simpleV1_2 :
            bot = new hack::BruteforceSimple("ccc",5,container);
            break;

        case typeTest::simpleV1_3 :
            bot = new hack::BruteforceSimple("midis",5,hack::typeSet::lowLetter);
            break;

        case typeTest::simpleV1_4 :
            bot = new hack::BruteforceSimple("",5,hack::typeSet::alphanumeric);
            break;

        case typeTest::simpleV2 :
            bot = new hack::BruteforceSimple("cac",4,container,4);
            break;

        case typeTest::simpleV2_2 :
            bot = new hack::BruteforceSimple("24",1,hack::typeSet::alphanumeric ,1);
            break;

        case typeTest::simpleV2_3 :
            bot = new hack::BruteforceSimple("midis",5,hack::typeSet::lowLetter,5);
            break;

        case typeTest::dictionnary :
            bot = new hack::BruteforceDictionnary("test","ficPass.txt");
            break;

        default : return;
    }

    std::cout << "Durée de recherche initialisée : " << bot->getElapsedSearch() << std::endl;
    std::cout << "Nombre de possibilités : " << bot->getNumberPossibilities() << std::endl;
    bot->run();
    bot->dispSolution();
    std::cout << "Durée de la recherche : " << bot->getElapsedSearch() << " secondes" << std::endl;
}