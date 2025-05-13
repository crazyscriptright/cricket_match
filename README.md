# Cricket Final One

This project is a cricket match simulation program written in C. It allows users to simulate a cricket match between two teams, input scores, and determine the winner based on the scores.

## Features

- Input scores for two teams.
- Simulate overs and balls for each team.
- Display scores for each team, including individual player statistics.
- Calculate and display the winner of the match.
- Award "Man of the Match" based on the highest individual score.

## How to Run

1. Compile the program using a C compiler. For example:
   ```bash
   gcc cricketfinaone.c -o cricketfinaone

2. Run the compiled program:
    ./cricketfinaone

Follow the on-screen instructions to input the number of overs, player names, and scores.

## Controls and Input
- Enter the number of overs (maximum 20).
- Input player names or use default names.
- Enter runs scored on each ball or `W` for a wicket.
- The program calculates scores, run rates, and determines the winner.
## Example Output

- **Team Scores and Player Statistics**: Displays the total scores for each team along with individual player performance.
- **Match Result**: Announces the winner, e.g., "Team1 won by X runs" or "Team2 won by Y wickets."
- **Man of the Match**: Highlights the player with the highest individual score.

## Dependencies

- Standard C libraries:
    - `stdio.h`
    - `stdlib.h`
    - `string.h`
    - `ctype.h`
    - `time.h`
    - `windows.h`

## Notes

- The program supports:
    - A maximum of **20 overs** per match.
    - Up to **11 players** per team.
- **Error Handling**:
    - Invalid inputs, such as runs greater than 6 or non-numeric entries, are managed with appropriate error messages.

## License

This project is **open-source** and available for use and modification under the specified license terms.

