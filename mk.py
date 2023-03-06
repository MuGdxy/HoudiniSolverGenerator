import sys
import shutil
import os

def copyanything(src, dst):
    shutil.copytree(src, dst)

solver_name=''
if(len(sys.argv) > 1):
    solver_name = sys.argv[1]
else:
    print("usage: python mk.py <solver_name>")

new_place = './'+solver_name+'/'
copyanything('./Template/houdini/', new_place+"/houdini/")
shutil.copyfile('./Template/CMakeLists.txt', new_place+"/CMakeLists.txt")

# traverse new_place
# replace _EXAMPLE_SOLVER_ with solver_name in files
for root, dirs, files in os.walk(new_place):
    for file in files:
        with open(os.path.join(root, file), 'r') as f:
            s = f.read()
            s = s.replace('_EXAMPLE_SOLVER_', solver_name)
        with open(os.path.join(root, file), 'w') as f:
            f.write(s)

# replace _EXAMPLE_SOLVER_ with solver_name in filenames
print("Generator:")
for root, dirs, files in os.walk(new_place):
    for file in files:
        new_file_name = file.replace('_EXAMPLE_SOLVER_', solver_name)
        # rename file
        os.rename(os.path.join(root, file), os.path.join(root, new_file_name))
        print(os.path.join(root, new_file_name))


