# Desert-Game-Simulator

A console-based **desert exploration and trading simulator** developed entirely in **C++**, featuring autonomous caravans, procedural item generation, and turn-based gameplay.  
The project demonstrates **advanced object-oriented programming**, inheritance, and polymorphism, bringing complex system behaviors to life through a simple terminal interface.

---

## 📋 Overview

The simulator models a vast desert world populated with:

- **Cities** — Trading hubs for caravans  
- **Caravans** — Player-controlled and autonomous units  
- **Barbarians** — Hostile, roaming NPC caravans  
- **Random Items** — Procedurally generated objects with various effects  

Players command caravans to **explore, trade, and survive** while managing **water, crew, and cargo**.  
The world is rendered textually using a **buffer-based visualization system**, ensuring smooth and efficient terminal updates.

---

## 🛠️ Technologies Used

- **C++17** — Core language  
- **Object-Oriented Design** — Classes, inheritance, encapsulation, polymorphism  
- **Smart Pointers** — Unique and shared pointers for memory safety  
- **STL Containers** — Vectors and algorithms for entity organization  
- **Terminal UI** — Console-based simulation display and user input  

---

## 🔬 Core Concepts Implemented

- **Inheritance & Polymorphism** — Reusable logic across items, cities, and caravans  
- **Autonomous Behavior** — Non-player caravans operate automatically based on environment and proximity  
- **Event-Driven Updates** — Storms, combat, and item discovery handled per simulation step  
- **Smart Memory Management** — Prevent memory leaks using smart pointers  
- **Encapsulated World State** — All game logic managed through the `Interface` and `Desert` classes  

---

## ♟️ Gameplay Elements

### Cities
- Act as trading hubs for caravans  
- Buy and sell goods  
- Hire crew and refill resources  

### Caravans
Four main caravan types:

| Type | Description |
|------|-------------|
| Commerce Caravan | Focused on trade and cargo capacity |
| Military Caravan | Strong in attack and defense, suited for combat |
| Barbarian Caravan | Autonomous, aggressive NPC caravan |
| Hestia | Special, resilient unit for survival |

### Items
Random items scattered throughout the desert:

| Item | Effect |
|------|--------|
| Treasure Chest | Grants resources or wealth |
| Mine | Damages caravans |
| Cage | Temporarily traps a caravan |
| Pandora’s Box | Random beneficial or harmful effect |
| Oasis | Refills a caravan’s water supply completely |

### Combat System
- Occurs when caravans occupy the same coordinates  
- Only user caravans and barbarians engage in combat  
- Barbarians never consume water and do not retreat  
- Commerce and military caravans differ in attack and resilience  
- Water transfer does **not** occur during combat  

---

## 🖥️ Commands

### In the simulation console
| Command | Description |
|---------|-------------|
| `config <file>` | Load a map configuration file |
| `compraC <city> <type>` | Buy a caravan (C = Trade, M = Military, S = Secret) |
| `move <id> <direction>` | Move a caravan (D = Right, E = Left, C = Up, B = Down) |
| `tripul <id> <n>` | Hire n crew members |
| `vende <id>` | Sell all goods from a caravan |
| `auto <id>` | Enable autonomous mode for a caravan |
| `stop <id>` | Disable autonomous mode for a caravan |
| `barbaro <l> <c>` | Spawn a barbarian caravan at given coordinates |
| `areia <l> <c> <r>` | Trigger a sandstorm centered at (l, c) with radius r |
| `prox <n>` | Advance the simulation by n turns |
| `terminar` | End the simulation |

---

## ▶️ How to Build and Run

- Developed using **CLion** (JetBrains) as the main IDE  
- Open or import the project folder in CLion  
- CLion automatically detects the configuration via `CMakeLists.txt`  
- Build and run the project directly from the IDE  
