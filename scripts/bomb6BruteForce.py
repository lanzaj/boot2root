import subprocess
from itertools import permutations

# Function to run the program with given input and check output
def run_program(input_strings):
    process = subprocess.Popen(['/home/laurie/bomb'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, _ = process.communicate(input_strings.encode())
    return output.decode().strip()

# Strings to provide as input
strings = [
    "Public speaking is very easy.\n",
    "1 2 6 24 120 720\n",
    "1 b 214\n",
    "9\n",
    "opekmq\n"
]

# Generate all permutations of 1 to 6
permutations_1_to_6 = permutations(range(1, 7))

# Loop through all permutations and run the program
for i, perm in enumerate(permutations_1_to_6, 1):
    # Convert permutation to string with whitespace separator
    input_str = ' '.join(str(num) for num in perm) + "\n"
    # Construct input strings including the last one
    all_input_strings = strings[0] + strings[1] + strings[2] + strings[3] + strings[4] + input_str
    # Run the program
    print("Running with input: {}".format(all_input_strings))
    result = run_program(all_input_strings)
    # Print program output and current combination
    print("Attempt {}: Combination {}, Output: {}".format(i, input_str, result))
    # Check if "BOOM" is not in the result
    if "BOOM" not in result:
        print("Success! Combination found:", input_str)
        break
