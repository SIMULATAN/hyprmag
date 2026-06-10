#include <getopt.h>
#include <strings.h>

#include <iostream>

#include "hyprmag.hpp"

static void help(void) {
    std::cout << "Hyprmag usage: hyprmag [arg [...]].\n\nArguments:\n"
              << " -h | --help              | Show this help message\n"
              << " -i | --render-inactive   | Render (freeze) inactive displays\n"
              << " -r | --radius            | Define lens radius\n"
              << " -s | --scale             | Define lens scale\n"
              << " -g | --draw-grid         | Draw a pixel grid\n"
              << " -c | --grid-colour       | Colour for the grid, rgba from 0 to 1\n";
}

int main(int argc, char** argv, char** envp) {
    g_pHyprmag = std::make_unique<CHyprmag>();

    while (true) {
        static struct option long_options[] = {{"help", no_argument, NULL, 'h'},
                                               {"render-inactive", no_argument, NULL, 'i'},
                                               {"radius", required_argument, NULL, 'r'},
                                               {"scale", required_argument, NULL, 's'},
                                               {"draw-grid", no_argument, NULL, 'g'},
                                               {"grid-colour", required_argument, NULL, 'gc'},
                                               {NULL, 0, NULL, 0}};

        int                  c = getopt_long(argc, argv, "hir:s:gc:", long_options, NULL);

        if (c == -1)
            break;

        switch (c) {
            case 'h': help(); exit(0);
            case 'i': g_pHyprmag->m_bRenderInactive = true; break;
            case 'r': g_pHyprmag->m_iRadius         = atoi(optarg); break;
            case 's': g_pHyprmag->m_fScale          = atof(optarg); break;
            case 'g': g_pHyprmag->m_bDrawPixelGrid  = true; break;
            case 'gc': {
                if (sscanf(optarg, "%lf %lf %lf %lf",
                    &g_pHyprmag->m_vGridColour[0],
                    &g_pHyprmag->m_vGridColour[1],
                    &g_pHyprmag->m_vGridColour[2],
                    &g_pHyprmag->m_vGridColour[3]) != 4) {
                std::cerr << "Invalid colour format. Use \"r g b a\", e.g.: \"0.8 0.3 0.2 0.6\"\n";
                exit(1);
                }
                break;
            }
            default: help(); exit(1);
        }
    }

    if (g_pHyprmag->m_iRadius <= 0 || g_pHyprmag->m_iRadius == INT32_MAX) {
        std::cerr << "Radius must be between 1 and " << INT32_MAX << "!\n";
        exit(1);
    }
    if (g_pHyprmag->m_fScale < 0.5f || g_pHyprmag->m_fScale > 10.0f) {
        std::cerr << "Scale must be between 0.5 and 10!\n";
        exit(1);
    }

    g_pHyprmag->init();

    return 0;
}
