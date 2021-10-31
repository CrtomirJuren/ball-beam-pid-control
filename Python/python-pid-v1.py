import os
import random

import matplotlib
import matplotlib.pyplot as plt

PNG_FILENAME = "Steady_PID_Simulation1.png"
OUTGOING_FILES_DIRECTORY = "C:\\Main\\Projects\\Python\\untitled"
OUTPUT_FILE_PATH = os.path.join(OUTGOING_FILES_DIRECTORY, PNG_FILENAME)

DPI = 100
MAX_VALUE = 500
PLOT_COLOR = '#FF4500'

PROPORTIONAL_GAIN_VALUE = 0.82
INTEGRAL_GAIN_VALUE = 0.155
DERIVATIVE_GAIN_VALUE = 0.45


def create_offset(set_point_value):
    """Docstring here (what does the function do)"""
    offset_value = random.randint(-128, 128)
    offset_value_incrementation = float(offset_value / 100)

    return set_point_value - offset_value_incrementation


def pt_controller(process_error_value, p_gain_value):
    """Docstring here (what does the function do)"""
    return process_error_value * p_gain_value


def it_controller(it, process_error_value, i_gain_value):
    """Docstring here (what does the function do)"""
    it = it + process_error_value
    it = it * i_gain_value
    return it


def dt_controller(current_control_output_value, previous_control_output_value, derivative_gain_value):
    """Docstring here (what does the function do)"""
    return (current_control_output_value - previous_control_output_value) * derivative_gain_value


def process_error(set_point_value, current_value):
    """Docstring here (what does the function do)"""
    return set_point_value - current_value


def pid_controller(proportional_value, integral_value, derivative_value):
    """Docstring here (what does the function do)"""
    return derivative_value + (proportional_value + integral_value)


def get_width_and_height(x_value, weight=10, height=5):
    """Docstring here (what does the function do)"""
    return (max(x_value)/200, height) if max(x_value) > MAX_VALUE else (weight, height)


def graph_line_data(x_value, error_value, proportional_value, integral_value, derivative_value, setpoint_value,
                    process_value, PID_value):
    """Docstring here (what does the function do)"""

    width, height = get_width_and_height(x_value)

    plt.figure(figsize=(width, height), dpi=DPI)

    plt.plot(x_value, PID_value, PLOT_COLOR)
    plt.plot(x_value, setpoint_value, 'k--')
    
    #---------------------

    plt.xlabel('Iteration Count')
    plt.ylabel('Output')
    plt.title('PID Controller\n(P={}, I={}, D={})'.format(PROPORTIONAL_GAIN_VALUE,
                                                          INTEGRAL_GAIN_VALUE,
                                                          DERIVATIVE_GAIN_VALUE))

    plt.legend(['PID Controller Output', 'Set point'], loc='upper right')
    plt.savefig(OUTPUT_FILE_PATH)

    print("Finished creating: {}".format(PNG_FILENAME))


def pid_simulator():
    """Docstring here (what does the function do)"""
    set_point_value, controller_output_value, integral_value, derivative_value, number_of_iterations = 0, 0, 0, 1, 200

    x_data, error_value_data, controller_output_data, proportional_value_data = [], [], [], []
    integral_value_data, derivative_value_data, setpoint_value_data, process_value_data = [], [], [], []

    for x_value, _ in enumerate(range(number_of_iterations)):
        process_value = set_point_value
        error_value = process_value - set_point_value

        if x_value == number_of_iterations / 5:
            set_point_value = 100
        if x_value == number_of_iterations / 2:
            set_point_value = -300
        if x_value == 6 * (number_of_iterations / 10):
            set_point_value = -200
        if x_value == 7 * (number_of_iterations / 10):
            set_point_value = -250
        if x_value == (number_of_iterations - (number_of_iterations / 5)):
            set_point_value = 0

        proportional_value = pt_controller(process_value, PROPORTIONAL_GAIN_VALUE)
        integral_value = it_controller(integral_value, process_value, INTEGRAL_GAIN_VALUE)

        previous_controller_output_value = controller_output_value
        controller_output_value = proportional_value + integral_value + derivative_value

        derivative_value = dt_controller(controller_output_value,
                                         previous_controller_output_value,
                                         DERIVATIVE_GAIN_VALUE)

        x_data.append(x_value)
        controller_output_data.append(controller_output_value)
        error_value_data.append(error_value)
        integral_value_data.append(integral_value)
        setpoint_value_data.append(set_point_value)
        process_value_data.append(process_value)
        derivative_value_data.append(derivative_value)
        proportional_value_data.append(proportional_value)

    graph_line_data(x_data, error_value_data, proportional_value_data, integral_value_data, derivative_value_data,
                    setpoint_value_data, process_value_data, controller_output_data)


def main():
    #matplotlib.use('Agg', warn=False)

    pid_simulator()


if __name__ == "__main__":
    main()