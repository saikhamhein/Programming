# Simulating the Monty Hall problem
import random
initial = input("Initial choice (A,B,C)? ").upper()
action = input("Always Switch/Hold (S,H) ? ").upper()
doors = ["A", "B", "C"]
totWins = 0
print("Let's play 100 times")
for i in range(100):
    placed = random.choice(doors)  # Prize placed randomly
    chosen = initial               # Your first choice
    used = [chosen, placed]       # Moderator chooses an empty door
    avail = [door for door in doors if door not in used]
    opened = random.choice(avail)
    if action == "S":             # You switch to remaining door
        avail = [door for door in doors if door not in [chosen, opened]]
        chosen = avail[0]          # should be the only door left
    youWin = (chosen == placed)
    if youWin:
        totWins += 1
    print("  Prize placed behind", placed,)
    print("-You chose", initial, "-Moderator opened", opened,)
    if action == "H":
        print("-You held to", chosen,)
    else:
        print("-You switched to", chosen,)
    if youWin:
        print("-You win (wins now", totWins, ")",)
    # print
