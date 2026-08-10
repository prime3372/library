import sys
import os
import time
import subprocess

# arguments
sol = sys.argv[1]
gen = sys.argv[2]
include = sys.argv[3]

# variables
timeout = 10000
case_num = 50
opts = ["-I", include, "-O2", "-Wall", "-Wextra", "-fdiagnostics-color=always", "-std=c++23"]

# colors
BLUE = "\033[34m"
YELLOW = "\033[33m"
MAGENTA = "\033[35m"
GREEN = "\033[32m"
RESET = "\033[0m"

def main():
    print("compiling...")

    targets = [(sol, "sol.exe"), (gen, "gen.exe")]

    procs = [(src, subprocess.Popen(["g++", src] + opts + ["-o", exe])) for src, exe in targets]

    failed = False
    for src, p in procs:
        if p.wait() != 0 and not failed:
            if os.path.exists(src):
                subprocess.run(["code", src], shell=True)
            failed = True

    if failed:
        return

    print("compilation finished.")
    time.sleep(0.1)

    for i in range(1, case_num + 1):
        # run gen.exe
        try:
            with open("in.txt", "w") as f_in:
                subprocess.run(["./gen.exe"], stdout=f_in, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"{BLUE}Test {i} FAIL Timed Out {gen}{RESET}")
            subprocess.run(["code", "in.txt"], shell=True)
            break
        except subprocess.CalledProcessError:
            print(f"{BLUE}Test {i} FAIL Runtime Error {gen}{RESET}")
            subprocess.run(["code", "in.txt"], shell=True)
            break

        # run sol.exe
        start = time.perf_counter()
        try:
            with open("in.txt", "r") as f_in, open("out.txt", "w") as f_out:
                subprocess.run(["./sol.exe"], stdin=f_in, stdout=f_out, timeout=timeout / 1000.0, check=True)
            t = int((time.perf_counter() - start) * 1000)
            print(f"{GREEN}Test {i} Success {t} ms{RESET}")
        except subprocess.TimeoutExpired:
            print(f"{YELLOW}Test {i} Timed Out > {timeout} ms{RESET}")
            subprocess.run(["code", "in.txt", "out.txt"], shell=True)
            break
        except subprocess.CalledProcessError:
            t = int((time.perf_counter() - start) * 1000)
            print(f"{MAGENTA}Test {i} Runtime Error {t} ms{RESET}")
            subprocess.run(["code", "in.txt", "out.txt"], shell=True)
            break

if __name__ == "__main__":
    main()
    for f in ["sol.exe", "gen.exe"]:
        if os.path.exists(f):
            os.remove(f)