#!/bin/bash

# ==The=Worst=Snake=Game=Ever=64==================================
# AUTHOR: Rafał Włodarczyk 2024-11-16
# DESCRIPTION: A simple maze game created in Bash. 
#              Find the exit.
# ===================================The=Worst=Snake=Game=Ever=64=

# ==Configuration=================================================
# -w, Optional: width of the maze (default: terminal width - 1)
# -h, Optional: height of the maze (default: terminal height - 1)
# ================================================================

width=$(( $(tput cols) - 1 ))
height=$(( $(tput lines) - 1 ))

# =Parse=command-line=arguments===================================
# Use getopt to override defaults if provided
# ================================================================

while getopts "w:h:" opt; do
  case $opt in
    w) width=$OPTARG ;;
    h) height=$OPTARG ;;
    *) echo "Usage: $0 [-w width] [-h height]" >&2; exit 1 ;;
  esac
done

if ! [[ $width =~ ^[0-9]+$ && $width -gt 0 ]]; then
  echo "Invalid width: $width. It must be a positive integer." >&2
  exit 1
fi

if ! [[ $height =~ ^[0-9]+$ && $height -gt 0 ]]; then
  echo "Invalid height: $height. It must be a positive integer." >&2
  exit 1
fi

if ((width < 5 || height < 5)); then
  echo "Terminal is too small for a maze. Minimum size is 5x5."
  exit 1
fi

# =Variable=Initialization========================================
# Here I initialize:
# - maze grid with borders (█), walls (1), and paths (0)
# - stack for DFS algorithm, traversal directions (no-diagonals)
# - create and push the starting point of the maze to the stack
# - player position - default at (1,1)
# ================================================================

declare -A maze
for ((i = 0; i < height; i++)); do
  for ((j = 0; j < width; j++)); do
    if ((i == 0 || i == height - 1 || j == 0 || j == width - 1)); then
      maze[$i,$j]="█"  # Border
    else
      maze[$i,$j]=1    # Wall
    fi
  done
done

maze[1,1]=0

declare -a stack
directions=("-1 0" "1 0" "0 -1" "0 1")  # Up, Down, Left, Right
stack+=(1,1)

player_x=1
player_y=1

# =Maze=Generation================================================
# Uses DFS https://en.wikipedia.org/wiki/Maze_generation_algorithm
# 
# Algorithm Steps:
# 1. While the stack is not empty:
# 2. Pop the top cell from the stack
# 3. Shuffle the directions array
# 4. For each direction:
#    - Check if the new cell is within the maze bounds
#    - Check if the new cell is a wall
#    - If both conditions are met:
#      - Mark the new cell as a path
#      - Mark the cell in between as a path
#      - Push the new cell to the stack
# 5. Repeat until the stack is empty
# 6. Mark the exit cell as a path (its neighbors as well)
# ================================================================

shuffle_directions() {
  for ((i = ${#directions[@]} - 1; i > 0; i--)); do
    j=$((RANDOM % (i + 1)))
    # Swap
    temp="${directions[i]}"
    directions[i]="${directions[j]}"
    directions[j]="$temp"
  done
}

function dfs() {
  while ((${#stack[@]} > 0)); do
    current="${stack[-1]}"
    IFS=',' read -r x y <<< "$current"
    stack=("${stack[@]:0:${#stack[@]}-1}")
    
    shuffle_directions

    for dir in "${directions[@]}"; do
      IFS=' ' read -r dx dy <<< "$dir"
      nx=$((x + 2 * dx))
      ny=$((y + 2 * dy))
      
      if ((nx > 0 && nx < height - 1 && ny > 0 && ny < width - 1)); then
        if [[ ${maze[$nx,$ny]} -eq 1 ]]; then
          maze[$nx,$ny]=0
          maze[$((x + dx)),$((y + dy))]=0
          
          stack+=("$nx,$ny")
        fi
      fi
    done
  done
}

dfs

maze[$((height - 2)),$((width - 2))]=0
maze[$((height - 3)),$((width - 2))]=0
maze[$((height - 2)),$((width - 3))]=0

# =Output Maze Array==============================================
# - '█' for borders
# - '░' for walls
# - ' ' for paths
# ================================================================

maze[$player_x,$player_y]="@"

draw_maze() {
  clear
  for ((i = 0; i < height; i++)); do
    row=""
    for ((j = 0; j < width; j++)); do
      case ${maze[$i,$j]} in
        "█") row+="█" ;;  # Border
        1) row+="░" ;;    # Wall
        0) row+=" " ;;    # Path
        "@") row+="\033[32m@\033[0m" ;;  # Player in green
      esac
    done
    echo -e "$row"
  done
}

draw_player() {
  tput cup $player_x $player_y
  echo -e "\033[32m@\033[0m"
}

# =Player=Movement================================================
# - Move the player in the maze, only if the position is walkable
# - w: up
# - s: down
# - a: left
# - d: right
# ================================================================

move_player() {
  local dx=0 dy=0
  case $1 in
    w) dx=-1 ;;
    s) dx=1 ;;
    a) dy=-1 ;;
    d) dy=1 ;;
    *) return ;;
  esac
  
  new_x=$((player_x + dx))
  new_y=$((player_y + dy))

  if ((new_x < 1 || new_x >= height - 1 || new_y < 1 || new_y >= width - 1)); then
    return
  fi
  
  if [[ ${maze[$new_x,$new_y]} -eq 0 ]]; then
    tput cup $player_x $player_y
    echo -e " "
    
    maze[$player_x,$player_y]=0
    player_x=$new_x
    player_y=$new_y
    maze[$player_x,$player_y]="@"
    
    draw_player
  fi
}


# =Main=Loop=======================================================
# - Accept player input
# - Move the player
# - Redraw the maze
# - Check winning condition and exit if met
# =================================================================

draw_maze

while true; do
  read -n 1 -s key
  move_player "$key"
  tput cup $height 0
  if ((player_x == height - 2 && player_y == width - 2)); then
    echo -e "\n\033[32mYou reached the exit! You've won! 🎉\033[0m"
    break
  fi
done

# =End=of=The=Worst=Snake=Game=Ever=64=============================
# Thank you for playing! :catbois_are_welcome:
# =================================================================
