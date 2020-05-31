// Include the most common headers from the C standard library
/*  AnimeKage
    Copyright (C) 2020, Pescu 

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation at version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    In addition, the following extra clauses are in effect:

    7b) Requiring preservation of specified reasonable legal notices or
    author attributions in that material or in the Appropriate Legal
    Notices displayed by works containing it;

    7c) Prohibiting misrepresentation of the origin of that material, or
    requiring that modified versions of such material be marked in
    reasonable ways as different from the original version;
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

void openAnimeKage() 
{
    Result rc;
    WebCommonConfig config;

    // Create the config.
    rc = webPageCreate(&config, "https://anime.kage.ro");

    if (R_SUCCEEDED(rc)) {
        rc = webConfigSetWhitelist(&config, "^http*"); // Keeping the whitelist matching everything (cleaner/less annoying).
        if (R_SUCCEEDED(rc)) { // Launch the applet and wait for it to exit.
            rc = webConfigShow(&config, NULL);
        } else {
            printf("Something went wrong opening the browser.");
        }
    }
    else {
        printf("Something went wrong making the config object.");
    }
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    consoleInit(NULL);

    printf("AnimeKage\n\nPress PLUS to close.\n");

    bool isApp = true;
    if (!(appletGetAppletType() == AppletType_Application)) {
        printf(CONSOLE_RED "Not running in APPLICATION mode. Not launching AnimeKage.\n");
        printf("Launch this program from APPLICATION mode instead.\n");
        printf(CONSOLE_YELLOW "If you are using Atmosphere (you should),\ndo not mitm the album but an actual title.\n\n");
        isApp = false;
    } else {
        printf(CONSOLE_GREEN "Press A to start AnimeKage (needed if you manually exited).\n\n");
    }
    printf(CONSOLE_RESET "Copyright (c) Pescu, 2020\n\nReleased under the AGPLv3.\Not licensable under later versions and clause 7b and 7c are in effect.");

    if (isApp)
        openAnimeKage();
    // Main loop
    while (appletMainLoop())
    {
        // Scan all the inputs. This should be done once for each frame
        hidScanInput();

        // hidKeysDown returns information about which buttons have been
        // just pressed in this frame compared to the previous one
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS)
            break;

        if (kDown & KEY_A)
            if (isApp)
                openAnimeKage();
        consoleUpdate(NULL);
    }
    consoleExit(NULL);
    return 0;
}