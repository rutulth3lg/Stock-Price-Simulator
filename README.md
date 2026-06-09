# Stock Price Simulator

A real-time interactive stock price simulator built in C++ using the **Raylib** graphics library, implementing **Geometric Brownian Motion (GBM)** to model realistic price movement.

## What It Does
- Simulates 100 time steps of stock price movement in real time
- Visualizes price as a live line chart with green (up) and red (down) coloring
- Displays live High, Low, and Current Price
- Supports custom starting price input ($10–$1000)
- Three volatility modes: Low, Medium, High
- Two market modes: Bull (upward drift via GBM) and Bear (downward drift)

## How It Works

### Price Simulation — Geometric Brownian Motion
GBM is the standard model used in quantitative finance (and the Black-Scholes options pricing formula) to simulate asset prices:

```
P(t) = P(t-1) * (1 + drift + volatility * randomShock)
```

- `drift` — the expected upward trend (0.001 per step in bull mode)
- `volatility` — controls how much the price can swing each step
- `randomShock` — discrete approximation of a Wiener process (random walk)

In bear market mode, the drift turns negative, simulating a declining market with a price floor.

### Volatility Modes
| Mode | Volatility |
|------|------------|
| Low  | 0.01 (1%)  |
| Med  | 0.02 (2%)  |
| High | 0.05 (5%)  |

## Controls
- Type a number ($10–$1000) to set the starting price
- Click **Low / Med / High Vol** to select volatility
- Click **Simulate!** to run a bull market simulation
- Click **Bear Market!** to run a bear market simulation

## How to Run

### Install Raylib
```bash
brew install raylib       # macOS
sudo apt install raylib   # Linux
```

### Compile and Run
```bash
g++ main.cpp -o simulator -lraylib
./simulator
```

## Tech Stack
- C++
- Raylib (graphics and input)
- Geometric Brownian Motion (GBM) price model
