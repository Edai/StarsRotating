//
// Created by edai on 19/03/18.
//

#include "Application.hpp"
#include "GraphicalCore.hpp"

Application::Application()
{
}

Application::~Application()
{
}

bool Application::Parse(Options *options, int ac, char** av)
{
    static struct option long_options[] =
            {
                    {"height", required_argument , 0, 'h'},
                    {"width",  required_argument, 0, 'w'},
                    {"title",   required_argument, 0, 't'},
                    {0, 0, 0, 0}
            };
    int option_index = 0;
    int c = getopt_long_only(ac, av, "h:w:t:",
                         long_options, &option_index);
    while (c > 0)
    {
        switch (c)
        {
            case 'h':
                options->height = atoi(optarg);
                break;
            case 'w':
                options->width = atoi(optarg);
                break;
            case 't':
                options->window_name = std::string(optarg);
                break;
            default:
                return (false);
        }
        c = getopt_long_only(ac, av, "h:w:t:",
                             long_options, &option_index);
    }
    if (options->window_name.empty())
        options->window_name = std::string(WINDOW_TITLE);
    if (options->width < 1 || options->height < 1)
    {
        options->width = DEFAULT_WIDTH;
        options->height = DEFAULT_HEIGHT;
        std::cout << "Invalid window dimensions... Setting default window dimensions." << std::endl;
    }
    return (true);
}

void Application::Start(int ac, char **av)
{
    Options *options = new Options();
    GraphicalCore *gc = GraphicalCore::Instance();

    if (!Parse(options, ac, av))
        return;
    gc->Run(ac, av, options);
}