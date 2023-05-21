import time
import tkinter as tk
from tkinter import messagebox
import random
from PIL import ImageTk, Image

# Define the size of the board
BOARD_SIZE = 600
player_1_pos = 0
player_2_pos = 0
turn = 0
speed = 0.5

# board entities
snakes = {32: 10, 36: 6, 48: 26, 62: 18, 88: 24, 95: 56, 97: 78}
ladders = {1: 38, 4: 14, 8: 30, 21: 42, 28: 76, 50: 67, 71: 92, 80: 99}

# Create the root window
root = tk.Tk()

# board image
img = ImageTk.PhotoImage(Image.open(
    "board_image.png").resize((BOARD_SIZE, BOARD_SIZE)))

# Load the dice images
dice_images = [ImageTk.PhotoImage(Image.open(f"dice/dice-{i}.png").resize((40,40))) for i in range(1, 7)]

# Create the canvas
canvas = tk.Canvas(root, width=BOARD_SIZE, height=BOARD_SIZE, bg="red")
canvas.create_image(0, 0, anchor=tk.NW, image=img)

canvas.grid(row=0, column=0, columnspan=2)

pl1_lab = tk.Label(root, text="Player 1")
pl2_lab = tk.Label(root, text="Player 2")
pl1_score = tk.Label(root, text="0")
pl2_score = tk.Label(root, text="0")

pl1_lab.grid(row=1, column=0)
pl1_score.grid(row=1, column=1)

pl2_lab.grid(row=2, column=0)
pl2_score.grid(row=2, column=1)


def get_cords(pos):
    pl_x = (pos-1) % 10
    pl_y = (pos-1) // 10
    if (pl_y % 2 == 0):
        return (pl_x*60+15, 600 - pl_y*60 - 15, pl_x*60+45, 600 - pl_y*60-45)
    else:
        return (600 - pl_x*60 - 15, 600 - pl_y*60 - 15, 600 - pl_x*60 - 45, 600 - pl_y*60-45)


def update_canvas(canvas):
    canvas.delete("all")
    canvas.create_image(0, 0, anchor=tk.NW, image=img)
    # draw player circles
    pl1 = get_cords(player_1_pos)
    pl2 = get_cords(player_2_pos)

    canvas.create_oval(pl1[0], pl1[1]-5, pl1[2], pl1[3]-5, fill="blue")
    canvas.create_oval(pl2[0], pl2[1]+5, pl2[2], pl2[3]+5, fill="green")

    pl1_score.config(text=str(player_1_pos))
    pl2_score.config(text=str(player_2_pos))

    # update labels and canvas
    pl1_score.update()
    pl2_score.update()
    canvas.update()


def roll_dice():
    # Roll the dice
    dice_roll = random.randint(1, 6)
    # Update the label with the dice roll image
    dice_label.config(image=dice_images[dice_roll - 1])
    dice_label.update()
    return dice_roll


def reset():
    global player_1_pos, player_2_pos, turn
    player_1_pos = 0
    player_2_pos = 0
    turn = 0
    update_canvas(canvas)
    turn_label.config(text="Player 1's turn")
    button.config(text="Roll Dice", command=play)


def check_winner():
    if (player_1_pos == 100):
        turn_label.config(text="Player 1 wins")
        messagebox.showinfo("Game Over", "Player 1 wins")
    elif (player_2_pos == 100):
        turn_label.config(text="Player 2 wins")
        messagebox.showinfo("Game Over", "Player 2 wins")
    else:
        return
    button.config(text="Play Again", command=reset)


def move_player(player, pos, new_pos, direct=False):
    global player_1_pos, player_2_pos
    if (direct):
        if (player == 0):
            player_1_pos = pos
        else:
            player_2_pos = pos
        update_canvas(canvas)
    else:
        for i in range(pos, new_pos+1):
            if (player == 0):
                player_1_pos = i
            else:
                player_2_pos = i
            update_canvas(canvas)
            time.sleep(speed)
        update_canvas(canvas)


def update_speed(val):
    global speed
    speed = float(val)


def play():
    global turn, player_1_pos, player_2_pos
    space = roll_dice()
    button.config(state=tk.DISABLED)
    if (turn == 0):
        if (player_1_pos + space > 100):
            turn = 1
            turn_label.config(text="Player 2's turn")
            button.config(state=tk.NORMAL)
            return
        move_player(turn, player_1_pos, player_1_pos+space)
        # player_1_pos += space
        if (player_1_pos in snakes.keys()):
            player_1_pos = snakes[player_1_pos]
            move_player(turn, player_1_pos, 0, True)
        elif (player_1_pos in ladders.keys()):
            player_1_pos = ladders[player_1_pos]
            move_player(turn, player_1_pos, 0, True)

        if (space == 6):
            turn_label.config(text="Player 1's turn")
        else:
            turn_label.config(text="Player 2's turn")
            turn = 1
    else:
        if (player_2_pos + space > 100):
            turn = 0
            turn_label.config(text="Player 1's turn")
            button.config(state=tk.NORMAL)
            return
        move_player(turn, player_2_pos, player_2_pos+space)
        # player_2_pos += space
        if (player_2_pos in snakes):
            player_2_pos = snakes[player_2_pos]
            move_player(turn, player_2_pos, 0, True)
        elif (player_2_pos in ladders):
            player_2_pos = ladders[player_2_pos]
            move_player(turn, player_2_pos, 0, True)

        if (space == 6):
            turn_label.config(text="Player 2's turn")
        else:
            turn_label.config(text="Player 1's turn")
            turn = 0
    button.config(state=tk.NORMAL)
    check_winner()


turn_label = tk.Label(root, text="Player 1's turn")
turn_label.grid(row=3, column=0, columnspan=2)

dice_label = tk.Label(root, text="Dice")
button = tk.Button(root, text="Roll Dice", command=play)
dice_label.grid(row=4, column=0)
button.grid(row=4, column=1)

speed_label = tk.Label(root, text="Speed")
speed_label.grid(row=5, column=0)
speed_select = tk.Scale(root, from_=0.1, to=1, resolution=0.1,
                        orient=tk.HORIZONTAL, length=200, command=update_speed)
speed_select.grid(row=5, column=1)
speed_select.set(0.5)


root.mainloop()
