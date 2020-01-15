#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include "termcolor.hpp"

#include "vfs/VFSFactory.h"
#include "vfs/VFSRegistry.h"
#include "vfs/IVFS.h"
#include "vfs/IVFSPlugin.h"

#include "vfs/IVFSDirectory.h"

/**
 * Parse input parameters as key->value structure
 * @param argc {int} Count of the input arguments.
 * @param argv {char**} Arguments data.
 * @return {std::map<std::string, std::string>} The key-value parameters.
 */
std::map<std::string, std::string> ParseParameters(int argc, char* argv[])
{
    std::map<std::string, std::string> result;
    bool parameterFound = false;
    std::string parameterName;
    for (int index = 0; index < argc; ++index)
    {
        std::string argument(argv[index]);
        if (!argument.empty())
        {
            if (parameterFound)
            {
                result.emplace(parameterName, argument);
                parameterFound = false;
                parameterName = "";
            }
            else if (argument[0] == '-')
            {
                parameterFound = true;
                parameterName = argument;
                continue;
            }
        }
    }

    return result;
}

/**
 * Load VFS Plugin.
 * @param parameters {std::map<std::string, std::string>&} The plugin configuration.
 * @return {std::shared_ptr<VFS::IVFSPlugin>} The reference to loaded plugin or nullptr.
 */
std::shared_ptr<VFS::IVFSPlugin> LoadPlugin(std::map<std::string, std::string>& parameters)
{
    if (parameters.find("-plugin") == parameters.end()) { return nullptr; }

    typedef std::shared_ptr<VFS::IVFSPlugin> (CreatePlugin)();
    boost::function<CreatePlugin> creator = boost::dll::import_alias<CreatePlugin>(parameters["-plugin"], "CreatePlugin", boost::dll::load_mode::append_decorations);
    if (creator.empty()) { return nullptr; }

    return creator();
}

/**
 * Entry point of the VFS manager.
 * @param argc {int} Count of the input arguments.
 * @param argv {char**} Arguments data.
 * @return {int} Exit Status code.
 */
int main(int argc, char* argv[])
{
    std::map<std::string, std::string> parameters = ParseParameters(argc, argv);

    std::cout << termcolor::green << "*******************************************\n";
    std::cout << termcolor::green << "*       Virtual File System Manager       *\n";
    std::cout << termcolor::green << "*******************************************\n\n";

    try
    {
        std::shared_ptr<VFS::IVFS> vfs = VFS::VFSFactory::Create(parameters["-vfs"], parameters);
        VFS::VFSRegistry::GetInstance().RegisterRoot(vfs);
        std::cout << termcolor::blue << "Virtual File System Created: " << termcolor::white << vfs->GetName() << "\n";

        std::shared_ptr<VFS::IVFSPlugin> plugin = LoadPlugin(parameters);
        if (plugin != nullptr)
        {
            plugin->Init(vfs);
            plugin->Run();
            plugin->Cleanup();
        }
    }
    catch (std::exception& e)
    {
        std::string what(e.what());
        std::cout << termcolor::red << what << std::endl;
        return 1;
    }

    return 0;
}
