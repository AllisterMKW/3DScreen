#include <3ds.h>

static void fillTopScreen(u8 r, u8 g, u8 b)
{
    u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);

    for (int y = 0; y < 240; y++)
    {
        for (int x = 0; x < 400; x++)
        {
            int pos = (y * 400 + x) * 3;
            fb[pos + 0] = r;
            fb[pos + 1] = g;
            fb[pos + 2] = b;
        }
    }
}

int main(int argc, char* argv[])
{
    gfxInitDefault();
    consoleInit(GFX_BOTTOM, NULL);

    // Store current color
    u8 currentR = 0x00;
    u8 currentG = 0x00;
    u8 currentB = 0xFF; // Initial: Blue

    fillTopScreen(currentR, currentG, currentB);

    while (aptMainLoop())
    {
        hidScanInput();
        u32 kDown = hidKeysDown();

        bool colorChanged = false;

        if (kDown & KEY_A)
        {
            currentR = 0xFF;
            currentG = 0x00;
            currentB = 0x00;
            colorChanged = true;
        }

        if (kDown & KEY_B)
        {
            currentR = 0x00;
            currentG = 0x00;
            currentB = 0xFF;
            colorChanged = true;
        }

        if (kDown & KEY_X)
        {
            currentR = 0x00;
            currentG = 0xFF;
            currentB = 0x00;
            colorChanged = true;
        }

        if (colorChanged)
            fillTopScreen(currentR, currentG, currentB);

        if (kDown & KEY_START)
            break;

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
