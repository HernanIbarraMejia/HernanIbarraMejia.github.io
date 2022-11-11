# Import the random module
import random

########################################
#
#
# ANNIE'S CODE BELOW
#
#
########################################


# random_step() takes no arguments and returns either 1 or -1, randomly.
# It will help us simulate Annie's random walk later.


def random_step():
    possible_values = [-1, 1]
    # The random.choice() method chooses one of the elements of the list randomly.
    step = random.choice(possible_values)
    return step

# annies_walk(number_of_steps,polygon) takes two arguments (with self-explanatory names) and simulates one of Annie's random walks.
# It returns whatever vertex she ended up at


def annies_walk(number_of_steps, polygon):
    # Annie starts at vertex 0
    annies_position = 0
    # Annie is going to take "number_of_steps" steps.
    for i in range(number_of_steps):
        # Annie either takes one step clockwise or anticlockwise.
        annies_position += random_step()
    # We may have stepped out of the range of vertices, giving us absurd answers such as 'Annie finished at vertex -8'.
    # To fix this, we reduce our answer to its remainder modulo "polygon"
    # For example, in a pentagon, if we get that Annie is in vertex 21 we know she's really in vertex 1 because we cycle every 5 vertices.
    annies_position = annies_position % polygon
    return annies_position


# This function is called when the user wants to simulate some walks by Annie


def annies_simulation():
    # Parameters.
    # repetitions: the number of walks Annie takes.
    # number_of_steps: how many steps Annie takes in one walk, by default 7.
    # polygon: the number of sides of the polygon Annie's in, by default 5.
    repetitions = int(input("How many walks to simulate (default 100000): "))
    number_of_steps = int(input("How many steps does Annie take per walk (default 7): "))
    polygon = int(input("How many sides does Annie's polygon has (default 5): "))

    # This list will record how many times Annie ends up on a vertex.
    # For polygon = 5, for instance, we initialize the list as record = [0,0,0,0,0].
    # Then, record[3] for example, represents the number of times Annie ended up in vertex 3.
    record = []
    for k in range(polygon):
        record.append(0)

    # We simulate "repetitions" random walks and store our results in "record".
    # Recall that annies_walk outputs the vertex Annie ends up at.
    for j in range(repetitions):
        result = annies_walk(number_of_steps, polygon)
        record[result] += 1

    # Finally, we print the output
    print('Annie took ', repetitions, ' walks, each of length ', number_of_steps, ', in a ', polygon, '-sided polygon and the results were:', sep='')
    for s in range(polygon):
        print('- She finished at the vertex', s, 'exactly', record[s], 'times, or', record[s] * 100 / repetitions, '% of the time')


########################################
#
#
# ANTHONY'S CODE BELOW
#
#
########################################


# This function sums the elements of two lists of length 2 and returns a new list
def sum_coordinates(list_1, list_2):
    result = [0, 0]
    for i in range(2):
        result[i] = list_1[i] + list_2[i]
    return result


# This function simulates one of Anthony's walk. It takes an argument which is the maximum number of steps Anthony's going to take before giving up on going back home.
# The function returns either the number of steps it took for Anthony to return to his starting point or, if he didn't make it, it returns -1.


def anthonys_walk(max):
    # In our grid there are two types of intersections:
    # Type 1: You can either go south, north west, or north east.
    # Type 2: You can either go north, south west, or south east.
    # Assume that all hexagons have sidelength 1. Then,
    # For Type 1 intersections:
    # Going south means adding -2*sin(pi/6) to your y-coordinate
    south = [0, -2]
    # Going north east means adding 1*cos(pi/6) to your x-coordinate and adding 1*sin(pi/6) to your y-coordinate
    north_east = [1, 1]
    # Going north west means adding -1*cos(pi/6) to your x-coordinate and adding 1*sin(pi/6) to your y-coordinate
    north_west = [-1, 1]
    # For Type 2 intersections:
    # Going north means adding 2*sin(pi/6) to your y-coordinate
    north = [0, 2]
    # Going south east means adding 1*cos(pi/6) to your x-coordinate and adding -1*sin(pi/6) to your y-coordinate
    south_east = [1, -1]
    # Going south west means adding -1*cos(pi/6) to your x-coordinate and adding -1*sin(pi/6) to your y-coordinate
    south_west = [-1, -1]

    # In general, Anthony's x-coordinate is always going to be a multiple of cos(pi/6), and his y-coordinate a multiple of sin(pi/6).
    # Therefore, it's not necessary to compute the exact coordinates of Anthony, it's enough to know what multiples of cos and sin he has.

    # It will be useful to have all six directions ordered clockwise.
    clockwise_directions = [north, north_east, south_east, south, south_west, north_west]
    # Anthony starts with coordinates (0,0)
    anthonys_position = [0, 0]
    # Let's say Anthony starts in a Type-1 intersection. Then, he can only move south, north west, or north east.
    # These are the elements in clockwise_directions with index 1, 3, and 5
    # available_indices is sort of a "dictionary" that tells you what directions are available if you read it in conjuction with clockwise_directions
    available_indices = [1, 3, 5]
    # Just counts how many steps Anthony has taken
    steps = 0
    # This while loop breaks if Anthony returns to his starting position or if the steps reach max
    while (anthonys_position != [0, 0] or steps == 0) and steps < max:
        # We randomly choose an element from available_indices and we store it on anthonys_choice
        anthonys_choice = random.choice(available_indices)
        # Notice this pattern: if Anthony goes north east (index 1) then in his next step he can go north(index 0) or south east (index 2).
        # In general, if Anthony chooses a direction with index n, then the next available indices must be n-1 and n+1. We need to take remainder modulo 6 though, to ensure we don't go outside the index range.
        available_indices = [(anthonys_choice - 1) % 6, (anthonys_choice + 1) % 6]
        # We add to anthonys_position the corresponding direction vector from clockwise_directions
        anthonys_position = sum_coordinates(anthonys_position, clockwise_directions[anthonys_choice])
        # We took one step
        steps += 1
    # If we reached the maximum before Anthony returns home then we return -1. Otherwise, we return the number of steps Anthony took in his walk.
    if steps == max:
        return -1
    else:
        return steps

# anthonys_simulation() is called whenever the user wants to simulate one of Anthony's walks.


def anthonys_simulation():
    print('WARNING: Default values in Anthony\'s simulation may result in a long compiling time. For testing purposes use smaller inputs.')
    max_steps_per_walk = int(input("What are the maximum number of steps per walk (default 10000): "))
    repetitions = int(input("How many walks to simulate (default 100000): "))

    # This list will record how many steps Anthony took to arrive back home
    # We initialize the list as a list of zeroes, up to the maximum number of steps Anthony can take + 1
    # Then, the value of record[6] for example, represents the number of times Anthony took 6 steps to go back home
    record = []
    for i in range(max_steps_per_walk + 1):
        record.append(0)
    # This variable represents the number of times Anthony didn't return before he walked the maximum number of steps.
    never_returned = 0
    # We simulate "repetitions" random walks and store our results in "record" and "never_returned".
    # Recall anthonys_walk outputs -1 if Anthony didn't return to his starting point or, if he did, then it outputs how many steps he took.
    for j in range(repetitions):
        steps = anthonys_walk(max_steps_per_walk)
        if steps == -1:
            never_returned += 1
        else:
            record[steps] += 1

    # Finally, we print the output
    print('Anthony took ', repetitions, ' walks, each of a maximum length of ', max_steps_per_walk, ' and the results were:', sep='')
    print('He did not return to his starting point', never_returned, 'times, or ', (never_returned * 100) / repetitions, '% of the time.')
    print('WARNING: Displaying further details will print an additional', max_steps_per_walk, 'lines')
    display_record = int(input("If you want to display the details of how many steps Anthony took to return to his starting point then enter 1, otherwise enter 2: "))
    if display_record == 1:
        for i in range(1, len(record)):
            print('Anthony returned to his starting point in', i, 'steps', record[i], 'times')


############################################
#
#
# STARTING SEQUENCE
#
#
###########################################


def start():
    which_simulation = int(input("Enter 1 if you wish to simulate Annie's walks or 2 if you wish to simulate Anthony's walks: "))
    if which_simulation == 1:
        annies_simulation()
    else:
        anthonys_simulation()
    again = int(input('Do you wish to start another simulation? Enter 1 if yes, or 2 if no: '))
    if again == 1:
        start()
    else:
        print('Thank you for using our program.')


start()
