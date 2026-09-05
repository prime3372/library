import sys
import os
import time
import subprocess

# arguments
gen = sys.argv[1]
sol = sys.argv[2]
case_num = int(sys.argv[3])
include = sys.argv[4]

# variables
timelimit = 5000
timeout = 10000
opts = ["-I", include, "-O2", "-Wall", "-Wextra", "-fdiagnostics-color=always", "-std=c++23"]

# colors
RESET = "\033[0m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"

def main():
    print("compiling...")

    targets = [(gen, "gen.exe"), (sol, "sol.exe")]

    procs = [subprocess.Popen(["g++", src] + opts + ["-o", exe]) for src, exe in targets]

    failed = False
    for p in procs:
        if p.wait() != 0 and not failed:
            failed = True

    if failed:
        return

    print("compilation finished.")
    time.sleep(0.1)

    t_max = 0

    for i in range(1, case_num + 1):
        # run gen.exe
        try:
            with open("in.txt", "w") as f_in:
                subprocess.run(["./gen.exe"], stdout=f_in, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"Test {i} {BLUE}Aborted{RESET} {gen} timed out")
            break
        except subprocess.CalledProcessError:
            print(f"Test {i} {BLUE}Aborted{RESET} {gen} returned a non-zero exit status")
            break

        # run sol.exe
        start = time.perf_counter()
        try:
            with open("in.txt", "r") as f_in, open("out.txt", "w") as f_out:
                subprocess.run(["./sol.exe"], stdin=f_in, stdout=f_out, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"Test {i} {YELLOW}Time Limit Exceeded{RESET} > {timeout} ms")
            break
        except subprocess.CalledProcessError:
            t = int((time.perf_counter() - start) * 1000)
            print(f"Test {i} {MAGENTA}Runtime Error{RESET} {t} ms")
            break

        t = int((time.perf_counter() - start) * 1000)
        t_max = max(t_max, t)

        if t > timelimit:
            print(f"Test {i} {YELLOW}Time Limit Exceeded{RESET} {t} ms")
            break

        print(f"Test {i} {GREEN}Passed{RESET} {t} ms")

        if i != case_num:
            subprocess.run(["cmd", "/c", "del", "in.txt", "out.txt", "ans.txt"])
        else:
            print(f"All tests passed. max {t_max} ms")

if __name__ == "__main__":
    main()
    for f in ["sol.exe", "gen.exe"]:
        if os.path.exists(f):
            os.remove(f)