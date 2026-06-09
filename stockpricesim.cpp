#include <iostream>
#include <raylib.h> // Raylib library used for graphics
#include <string>

using namespace std;

float prices[100]; // stores simulated stock prices for 100 time steps
Color linecolors[100];

void generateprices(float startprice, float drift, float volatility, int mode, float floor = 1) {
    prices[0] = startprice;
    linecolors[0] = WHITE;

    for (int i = 1; i < 100; i++) {
        if (mode == 1) {
            // Geometric Brownian Motion (GBM) price simulation
            // randomshock: discrete Wiener process approximation
            float randomshock = GetRandomValue(-100, 100) / 100.0f;
            prices[i] = prices[i - 1] * (1 + drift + volatility * randomshock);
        } else {
            float randomshock = GetRandomValue(-100, 100) / 100.0f;
            prices[i] = prices[i - 1] * (1 - 0.02f + volatility * randomshock);
        }

        if (prices[i] < floor) {
            prices[i] = floor;
        }

        if (prices[i] >= prices[i - 1]) {
            linecolors[i] = GREEN;
        } else {
            linecolors[i] = RED;
        }
    }
}

// get high
float high() {
    float h = prices[0];
    for (int i = 0; i < 100; i++) {
        if (h < prices[i]) {
            h = prices[i];
        }
    }
    return h;
}

// get low
float low() {
    float l = prices[0];
    for (int i = 0; i < 100; i++) {
        if (l > prices[i]) {
            l = prices[i];
        }
    }
    return l;
}

int main() {
    InitWindow(800, 600, "STOCK PRICE SIMULATOR"); // creates window
    SetTargetFPS(60);

    int volMode = 1;
    float volatility = 0.02f;
    string startpriceString = "100";
    bool simstarted = false;
    int count = 1;

    while (!WindowShouldClose()) { // important while loop, it keeps the window open until clicked close
        int key = GetCharPressed();
        if (key >= '0' && key <= '9') {
            if (startpriceString.size() < 4) {
                startpriceString += (char)key;
            }
        }

        if (IsKeyPressed(KEY_BACKSPACE) && startpriceString.size() > 0) {
            startpriceString.pop_back();
        }

        if (startpriceString.size() > 0) {
            int val = stoi(startpriceString);
            if (val > 1000) {
                startpriceString.pop_back();
            }
            if (val < 10 && startpriceString.size() == 2) {
                startpriceString.pop_back();
            }
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mx = GetMouseX();
            int my = GetMouseY();

            if (mx > 20 && mx < 120 && my > 545 && my < 580) {
                volMode = 0;
                volatility = 0.01f;
            }
            if (mx > 130 && mx < 230 && my > 545 && my < 580) {
                volMode = 1;
                volatility = 0.02f;
            }
            if (mx > 240 && mx < 340 && my > 545 && my < 580) {
                volMode = 2;
                volatility = 0.05f;
            }
            if (mx > 350 && mx < 500 && my > 545 && my < 580) {
                float startprice = 100;
                if (startpriceString.size() > 0) {
                    startprice = stof(startpriceString);
                }
                generateprices(startprice, 0.001f, volatility, 1);
                count = 1;
                simstarted = true;
            }
            if (mx > 510 && mx < 660 && my > 545 && my < 580) {
                float startprice = 100;
                if (startpriceString.size() > 0) {
                    startprice = stof(startpriceString);
                }
                generateprices(startprice, 0.001f, volatility, 0, 50);
                count = 1;
                simstarted = true;
            }
        }

        if (simstarted && count < 100 && GetTime() > count * 0.05) {
            count++;
        }

        float h = high();
        float l = low();

        if (h - l < 1) {
            h = l + 1;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("STOCK PRICE SIMULATOR", 20, 15, 25, WHITE); // gives the heading to the window

        if (simstarted) {
            for (int i = 1; i < count; i++) {
                float x1 = 50 + (i - 1) * 10;
                float x2 = 50 + i * 10;
                float y1 = 500 - ((prices[i - 1] - 1) / (h - 1) * 350);
                float y2 = 500 - ((prices[i] - 1) / (h - 1) * 350);
                DrawLine(x1, y1, x2, y2, linecolors[i]);
            }
        }

        string price = "Price: $" + to_string((int)prices[count - 1]);
        string hi = "High: $" + to_string((int)h);
        string lo = "Low: $" + to_string((int)l);

        DrawText(price.c_str(), 20, 50, 20, DARKBLUE);
        DrawText(hi.c_str(), 20, 75, 20, GREEN);
        DrawText(lo.c_str(), 20, 100, 20, RED);

        DrawRectangle(600, 45, 160, 30, DARKGRAY);
        DrawText(startpriceString.c_str(), 610, 52, 18, WHITE);
        DrawText("Start Price ($10-1000):", 600, 25, 15, WHITE);

        DrawText("Model: Geometric Brownian Motion (GBM)", 20, 515, 15, GRAY);

        // creating buttons as more variety of inputs and respective outputs can be shown
        Color lowbtn;
        if (volMode == 0) {
            lowbtn = GREEN;
        } else {
            lowbtn = DARKGRAY;
        }
        DrawRectangle(20, 545, 100, 35, lowbtn);
        DrawText("Low Vol", 28, 554, 16, WHITE);

        Color midbtn;
        if (volMode == 1) {
            midbtn = GREEN;
        } else {
            midbtn = DARKGRAY;
        }
        DrawRectangle(130, 545, 100, 35, midbtn);
        DrawText("Med Vol", 138, 554, 16, WHITE);

        Color hibtn;
        if (volMode == 2) {
            hibtn = GREEN;
        } else {
            hibtn = DARKGRAY;
        }
        DrawRectangle(240, 545, 100, 35, hibtn);
        DrawText("High Vol", 248, 554, 16, WHITE);

        DrawRectangle(350, 545, 150, 35, DARKBLUE);
        DrawText("Simulate!", 368, 554, 16, WHITE);

        DrawRectangle(510, 545, 150, 35, DARKPURPLE);
        DrawText("Bear Market!", 520, 554, 16, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
