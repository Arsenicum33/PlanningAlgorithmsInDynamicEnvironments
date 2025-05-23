import subprocess
import os
import json
import statistics
import argparse
from pathlib import Path

from input_generators.solver_input_generator import SolverInputGenerator
from input_generators.blender_input_generator import BlenderInputGenerator
from plotTree import plot_tree

def compile_cpp(project_dir: str, build_dir: str, debug: bool=True):
    print("Running CMake...")
    #if debug:
       # subprocess.run(["cmake", "-S", project_dir, "-B", build_dir], check=True)
    #else:
    subprocess.run(["cmake", "-S", project_dir, "-B", build_dir, "-DCMAKE_BUILD_TYPE=Release"], check=True)

    print("Building the project...")
    subprocess.run(["cmake", "--build", build_dir], check=True)


def execute_solver(executable: str, work_dir: str, temfile_path: str):
    arguments = [executable, temfile_path]
    print("Running the C++ executable...")
    result = run_cpp_executable(arguments, work_dir)
    print("STDOUT:", result.stdout)
    return result


def process_execution_time(execution_times: list):
    median = statistics.median(execution_times)
    mean = statistics.mean(execution_times)
    print(f"Median: {median}, Mean: {mean}")


def run_cpp_executable(arguments, work_dir):
    return subprocess.run(arguments, text=True, cwd=work_dir)


def run_blender(blender_executable: str, scene_script: str, inputFilepath: str):
    print("Running Blender executable...")
    blender_command = [
        blender_executable,
        "--python",
        scene_script,
        "--",
        inputFilepath
    ]
    result = subprocess.run(blender_command, capture_output=True, text=True)
    print("STDOUT:", result.stdout)
    return result

def parse_args():
    parser = argparse.ArgumentParser(description="Command-line argument parser")
    parser.add_argument("--env", type=str, help="Filename with env settings")
    args = parser.parse_args()
    return vars(args)

def load_config(filename):
    with open(filename, 'r') as file:
        data = json.load(file)
    return data
    #env_type = data.get('env_type')
    #config_class = config_classes.get(env_type)
    #if not config_class:
    #    raise ValueError(f'Unknown environment type: {env_type}')
    #return config_class(data)

def load_paths():
    with open("paths.json", 'r') as file:
        paths = json.load(file)
    base_dir = Path(__file__).resolve().parents[1]
    paths = {key: str((base_dir / Path(value)).resolve()) for key, value in paths.items()}
    return paths

if __name__ == "__main__":
    args = parse_args()

    envSettingsFilename = args['env']



    config = load_config(envSettingsFilename)
    paths = load_paths()
    input_generator = SolverInputGenerator(config, paths)
    solver_input = input_generator.get_solver_input()
    tempfile_path = input_generator.generate_input_tempfile()

    proj_dir = paths['project_dir']
    build_dir = paths['build_dir']


    cpp_executable_filepath = str(os.path.join(build_dir, "project"))

    compile_cpp(proj_dir, build_dir)

    path_planning_result = execute_solver(cpp_executable_filepath, build_dir, tempfile_path)

    if path_planning_result.returncode != 0:
        print(f"Error running C++ program: {path_planning_result.stderr}")
        exit(1)

    obstacles_filename = config.get('obstacles_name', None)
    obstacles_filepath = None
    if obstacles_filename is not None and obstacles_filename != '':
        obstacles_filepath = str(os.path.join(paths['obstacles_dir'], obstacles_filename))

    target_filename = config.get('target', None)
    target_filepath = None
    if target_filename is not None and target_filename is str and target_filename != '':
        target_filepath = str(os.path.join(paths['animations_dir'], target_filename))
    dynamic_objects = []
    if target_filepath is not None and target_filename.endswith('.fbx'):
        dynamic_objects.append(target_filepath)
    plot_tree(os.path.join(build_dir, "graph.json"), obstacles_filepath, dynamic_objects)

    blender_exec_filepath = paths['blender_executable_filepath']

    scene_script = 'scene_script.py'

    blender_input_generator = BlenderInputGenerator(config, paths, solver_input)
    blender_input = blender_input_generator.get_blender_input()
    blender_tempfile = blender_input_generator.generate_input_tempfile()

    blender_output = run_blender(blender_exec_filepath, scene_script, blender_tempfile)

    if blender_output.returncode != 0:
        print(f"Error running Blender: {blender_output.stderr}")
        exit(1)

    print("Blender animation completed successfully.")

