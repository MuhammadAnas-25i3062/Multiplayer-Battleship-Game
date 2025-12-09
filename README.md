# 🚢 Battleship Game

A classic two-player naval strategy game built in C++ with a colorful console interface.

## Features
- 🎨 Color-coded ships and attacks
- 🎯 Manual or random ship placement
- 📊 Scoring system (+10 per hit, -1 per miss)
- 🏆 Game history with leaderboard
- 💥 Visual feedback for destroyed ships
- ⚡ Dynamic fires (6 - destroyed ships)

## How to Play
1. Each player places 5 ships on their 10x10 board
2. Players take turns attacking enemy coordinates
3. Win by destroying all enemy ships OR reaching 150 points
4. Fires decrease as you lose ships

## Requirements
- C++ compiler (GCC, MinGW, MSVC)
- Windows OS (uses Windows.h for colors)

## Controls
- Use numbers to select menu options
- Enter coordinates (0-9) for attacks
- Follow on-screen prompts for ship placement

## Ship Types
| Ship | Size |
|------|------|
| Aircraft Carrier | 5 |
| Battleship | 4 |
| Destroyer | 3 |
| Submarine | 3 |
| Patrol Boat | 2 |

## Screenshots
<img width="722" height="553" alt="Screenshot 2025-12-09 225016" src="https://github.com/user-attachments/assets/9b1527af-49a2-467a-90e7-0003a8596ea0" />

<img width="1007" height="793" alt="Screenshot 2025-12-09 225034" src="https://github.com/user-attachments/assets/daa598d4-112b-48b2-a82c-cf648a660fcf" />

<img width="1911" height="823" alt="Screenshot 2025-12-09 225115" src="https://github.com/user-attachments/assets/d6a3c382-542d-4a9b-a8c0-af719e5d0e78" />


## Future Improvements
- AI opponent
- Network multiplayer
- Save/load games
- Sound effects
