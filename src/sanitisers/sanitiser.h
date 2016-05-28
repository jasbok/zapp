#ifndef SANITISER_H
#define SANITISER_H

#include "analysers/target_analyser.h"
#include "analysers/type_analyser.h"

class sanitiser
{
public:
    static void sanitise_environment(const target_analyser& target_analyser, type_analyser::target_type type);
    static void dosbox(const target_analyser &target_analyser);
    static void lowercase_file_contents(const QString &path);
    static void sanitise_config(const QString &path);
};

#endif // SANITISER_H
