import turtle
import re

# Function to parse the instructions and draw the lines accordingly
def draw_message_from_instructions(instructions):
    # Set up the turtle
    screen = turtle.Screen()
    screen.setup(width=800, height=600)
    t = turtle.Turtle()
    t.speed(0)  # Set the turtle speed to the fastest

    # Loop through each instruction
    for instruction in instructions:
        # Parse the instruction
        parts = instruction.split(' ', 1)
        if len(parts) < 2:
            continue  # Skip lines without action/value pair
        action = parts[0]
        value = parts[1].strip()
        
        # Extract only numeric characters from the value
        numeric_value = re.sub(r'\D', '', value)
        
        # Perform the action
        if action == 'Avance':
            t.forward(int(numeric_value))
        elif action == 'Recule':
            t.backward(int(numeric_value))
        elif action == 'Tourne':
            angle = int(re.search(r'\d+', value).group())
            direction = 'gauche' if 'gauche' in value else 'droite'
            if direction == 'gauche':
                t.left(angle)
            elif direction == 'droite':
                t.right(angle)

    # Keep the window open until it's closed by the user
    turtle.done()

# Function to read instructions from a file
def read_instructions_from_file(file_path):
    with open(file_path, 'r') as file:
        instructions = file.readlines()
    return instructions

# Path to the instruction file
file_path = './turtle'

# Read instructions from the file
instructions = read_instructions_from_file(file_path)

# Draw the message based on the instructions
draw_message_from_instructions(instructions)