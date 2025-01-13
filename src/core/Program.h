//
// Created by arseniy on 13.1.25.
//

#ifndef PROGRAM_H
#define PROGRAM_H
#include <memory>

#include "creator/IComponentManager.h"
#include "executor/IExecutor.h"
#include "exporter/IExporter.h"
#include "reader/IReader.h"
#include "validator/IValidator.h"


class Program
{
public:
    virtual ~Program() = default;
    Program(std::unique_ptr<IReader> reader,
        std::unique_ptr<IComponentManager> componentManager,
            std::unique_ptr<IExecutor> executor,
            std::unique_ptr<IValidator> validator,
            std::unique_ptr<IExporter> exporter)
       : reader(std::move(reader)),
         componentManager(std::move(componentManager)),
         executor(std::move(executor)),
         validator(std::move(validator)),
         exporter(std::move(exporter)) {}

     virtual void run(int argc, char* argv[]);
private:
    std::unique_ptr<IReader> reader;
    std::unique_ptr<IComponentManager> componentManager;
    std::unique_ptr<IExecutor> executor;
    std::unique_ptr<IValidator> validator;
    std::unique_ptr<IExporter> exporter;
};



#endif //PROGRAM_H
